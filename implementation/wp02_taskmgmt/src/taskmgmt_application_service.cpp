#include "wp02_taskmgmt/taskmgmt_application_service.h"

namespace wp02_taskmgmt {

TaskMgmtApplicationService::TaskMgmtApplicationService(CommandNormalizer& commandNormalizer,
                                                       TaskDecomposer& taskDecomposer,
                                                       ResourceRequestCoordinator& resourceRequestCoordinator,
                                                       TaskPackageBuilder& taskPackageBuilder,
                                                       TaskReconstructionService& taskReconstructionService,
                                                       TaskLifecycleTracker& taskLifecycleTracker)
    : commandNormalizer_(commandNormalizer),
      taskDecomposer_(taskDecomposer),
      resourceRequestCoordinator_(resourceRequestCoordinator),
      taskPackageBuilder_(taskPackageBuilder),
      taskReconstructionService_(taskReconstructionService),
      taskLifecycleTracker_(taskLifecycleTracker) {}

ReceiveMissionCommandResult TaskMgmtApplicationService::receiveMissionCommand(const ReceiveMissionCommandCommand& command) {
  ReceiveMissionCommandResult result;
  const auto normalized = commandNormalizer_.normalize(command.missionCommand);
  if (!normalized.has_value()) {
    return result;
  }

  result.accepted = true;
  result.missionCommand = *normalized;
  result.taskConstraint = taskDecomposer_.decompose(*normalized);
  result.allocationRequest = resourceRequestCoordinator_.buildAllocationRequest(result.taskConstraint);

  missionCommandsByMissionId_[result.missionCommand.missionId] = result.missionCommand;
  taskConstraintsByMissionId_[result.taskConstraint.missionId] = result.taskConstraint;
  allocationRequestsByRequestId_[result.allocationRequest.requestId] = result.allocationRequest;

  taskLifecycleTracker_.record(result.missionCommand.traceId,
                               result.missionCommand.missionId,
                               TaskLifecycleStage::kCommandReceived,
                               "mission command normalized");
  taskLifecycleTracker_.record(result.taskConstraint.traceId,
                               result.taskConstraint.missionId,
                               TaskLifecycleStage::kDecomposed,
                               result.taskConstraint.constraintId);
  taskLifecycleTracker_.record(result.allocationRequest.traceId,
                               result.allocationRequest.missionId,
                               TaskLifecycleStage::kAllocationRequested,
                               result.allocationRequest.requestId);
  return result;
}

CommitAllocationDecisionResult TaskMgmtApplicationService::commitAllocationDecision(
    const CommitAllocationDecisionCommand& command) {
  CommitAllocationDecisionResult result;
  result.allocationDecision = command.allocationDecision;

  taskLifecycleTracker_.record(result.allocationDecision.traceId,
                               result.allocationDecision.missionId,
                               TaskLifecycleStage::kAllocationResolved,
                               result.allocationDecision.requestId);

  if (!result.allocationDecision.accepted) {
    return result;
  }

  const auto requestIt = allocationRequestsByRequestId_.find(result.allocationDecision.requestId);
  if (requestIt == allocationRequestsByRequestId_.end()) {
    return result;
  }

  const auto constraintIt = taskConstraintsByMissionId_.find(result.allocationDecision.missionId);
  if (constraintIt == taskConstraintsByMissionId_.end()) {
    return result;
  }

  result.taskPackage = taskPackageBuilder_.buildTaskPackage(constraintIt->second, result.allocationDecision);
  taskPackagesByMissionId_[result.taskPackage->missionId] = *result.taskPackage;
  result.taskPackageCreated = true;

  taskLifecycleTracker_.record(result.taskPackage->traceId,
                               result.taskPackage->missionId,
                               TaskLifecycleStage::kPlanCreated,
                               result.taskPackage->taskPackageId);
  return result;
}

HandleExecutionExceptionResult TaskMgmtApplicationService::handleExecutionException(
    const HandleExecutionExceptionCommand& command) {
  HandleExecutionExceptionResult result;
  result.reconstructionDecision = taskReconstructionService_.evaluate(command.traceId,
                                                                     command.missionId,
                                                                     command.taskPackageId,
                                                                     command.reason,
                                                                     command.exceedsTaskBoundary,
                                                                     command.decidedAtUtcMs);
  if (result.reconstructionDecision.requiresReconstruction) {
    taskLifecycleTracker_.record(command.traceId,
                                 command.missionId,
                                 TaskLifecycleStage::kReconstructionRequired,
                                 result.reconstructionDecision.expectedAction);
  }

  return result;
}

const TaskLifecycleTracker& TaskMgmtApplicationService::lifecycleTracker() const {
  return taskLifecycleTracker_;
}

void TaskMgmtApplicationService::recordCommandAck(const CommandAck& commandAck) {
  taskLifecycleTracker_.record(commandAck.traceId,
                               commandAck.missionId,
                               TaskLifecycleStage::kCommandAcknowledged,
                               commandAck.accepted ? "accepted" : commandAck.detail);

  const auto taskPackageIt = taskPackagesByMissionId_.find(commandAck.missionId);
  if (taskPackageIt == taskPackagesByMissionId_.end()) {
    return;
  }

  taskPackageIt->second.executionState = commandAck.accepted ? ExecutionState::kInProgress : ExecutionState::kBlocked;
}

void TaskMgmtApplicationService::recordMissionProgress(const MissionProgress& missionProgress) {
  taskLifecycleTracker_.record(missionProgress.traceId,
                               missionProgress.missionId,
                               TaskLifecycleStage::kMissionProgressUpdated,
                               missionProgress.progressState);

  const auto taskPackageIt = taskPackagesByMissionId_.find(missionProgress.missionId);
  if (taskPackageIt == taskPackagesByMissionId_.end()) {
    return;
  }

  taskPackageIt->second.executionState = missionProgress.progressState == "COMPLETED" ? ExecutionState::kCompleted
                                                                                        : ExecutionState::kInProgress;
}

void TaskMgmtApplicationService::recordEffectReport(const EngagementEffectReport& effectReport) {
  taskLifecycleTracker_.record(effectReport.traceId,
                               effectReport.missionId,
                               TaskLifecycleStage::kEffectReported,
                               effectReport.effectStatus);

  const auto taskPackageIt = taskPackagesByMissionId_.find(effectReport.missionId);
  if (taskPackageIt == taskPackagesByMissionId_.end()) {
    return;
  }

  taskPackageIt->second.executionState = effectReport.effectStatus == "SUCCESS" ? ExecutionState::kCompleted
                                                                                  : taskPackageIt->second.executionState;
}

std::optional<TaskPackage> TaskMgmtApplicationService::findTaskPackage(const std::string& missionId) const {
  const auto taskPackageIt = taskPackagesByMissionId_.find(missionId);
  if (taskPackageIt == taskPackagesByMissionId_.end()) {
    return std::nullopt;
  }

  return taskPackageIt->second;
}

}  // namespace wp02_taskmgmt