#include "wp02_taskmgmt/taskmgmt_command_mapper.h"

namespace wp02_taskmgmt {

namespace {

MissionPriority parsePriority(const std::string& value) {
  return value == "high" ? MissionPriority::kHigh : MissionPriority::kRoutine;
}

ReconstructionReason parseReason(const std::string& value) {
  if (value == "resource_lost_beyond_task_boundary") {
    return ReconstructionReason::kResourceLostBeyondTaskBoundary;
  }
  if (value == "allocation_rejected") {
    return ReconstructionReason::kAllocationRejected;
  }
  if (value == "execution_boundary_broken") {
    return ReconstructionReason::kExecutionBoundaryBroken;
  }
  return ReconstructionReason::kNone;
}

}

std::optional<ReceiveMissionCommandCommand> TaskMgmtCommandMapper::map(
    const ReceiveMissionCommandRequestDto& dto) const {
  if (dto.traceId.empty() || dto.missionId.empty() || dto.sourceId.empty() || dto.objective.empty() ||
      dto.targetArea.empty() || dto.requestedResourceKinds.empty()) {
    return std::nullopt;
  }

  ReceiveMissionCommandCommand command;
  command.missionCommand = MissionCommand{dto.traceId,
                                          dto.missionId,
                                          dto.sourceId,
                                          dto.objective,
                                          dto.targetArea,
                                          dto.startUtcMs,
                                          dto.endUtcMs,
                                          parsePriority(dto.priority),
                                          dto.requestedResourceKinds};
  return command;
}

std::optional<CommitAllocationDecisionCommand> TaskMgmtCommandMapper::map(
    const CommitAllocationDecisionRequestDto& dto) const {
  if (dto.traceId.empty() || dto.requestId.empty() || dto.missionId.empty()) {
    return std::nullopt;
  }

  CommitAllocationDecisionCommand command;
  command.allocationDecision = AllocationDecision{
      dto.traceId, dto.requestId, dto.missionId, dto.accepted, dto.allocatedResourceIds, dto.reservedResourceIds};
  return command;
}

std::optional<HandleExecutionExceptionCommand> TaskMgmtCommandMapper::map(
    const HandleExecutionExceptionRequestDto& dto) const {
  if (dto.traceId.empty() || dto.missionId.empty() || dto.taskPackageId.empty()) {
    return std::nullopt;
  }

  return HandleExecutionExceptionCommand{
      dto.traceId, dto.missionId, dto.taskPackageId, parseReason(dto.reason), dto.exceedsTaskBoundary, dto.decidedAtUtcMs};
}

}  // namespace wp02_taskmgmt