#pragma once

#include <optional>
#include <string>
#include <unordered_map>

#include "wp02_taskmgmt/command_normalizer.h"
#include "wp02_taskmgmt/resource_request_coordinator.h"
#include "wp02_taskmgmt/task_decomposer.h"
#include "wp02_taskmgmt/task_lifecycle_tracker.h"
#include "wp02_taskmgmt/task_package_builder.h"
#include "wp02_taskmgmt/task_reconstruction_service.h"
#include "wp02_taskmgmt/taskmgmt_use_cases.h"

namespace wp02_taskmgmt {

struct ReceiveMissionCommandResult {
  bool accepted{false};
  MissionCommand missionCommand;
  TaskConstraint taskConstraint;
  AllocationRequest allocationRequest;
};

struct CommitAllocationDecisionResult {
  bool taskPackageCreated{false};
  AllocationDecision allocationDecision;
  std::optional<TaskPackage> taskPackage;
};

struct HandleExecutionExceptionResult {
  TaskReconstructionDecision reconstructionDecision;
};

class TaskMgmtApplicationService {
 public:
  TaskMgmtApplicationService(CommandNormalizer& commandNormalizer,
                             TaskDecomposer& taskDecomposer,
                             ResourceRequestCoordinator& resourceRequestCoordinator,
                             TaskPackageBuilder& taskPackageBuilder,
                             TaskReconstructionService& taskReconstructionService,
                             TaskLifecycleTracker& taskLifecycleTracker);

  ReceiveMissionCommandResult receiveMissionCommand(const ReceiveMissionCommandCommand& command);
  CommitAllocationDecisionResult commitAllocationDecision(const CommitAllocationDecisionCommand& command);
  HandleExecutionExceptionResult handleExecutionException(const HandleExecutionExceptionCommand& command);
  void recordCommandAck(const CommandAck& commandAck);
  void recordMissionProgress(const MissionProgress& missionProgress);
  void recordEffectReport(const EngagementEffectReport& effectReport);

  std::optional<TaskPackage> findTaskPackage(const std::string& missionId) const;

  const TaskLifecycleTracker& lifecycleTracker() const;

 private:
  CommandNormalizer& commandNormalizer_;
  TaskDecomposer& taskDecomposer_;
  ResourceRequestCoordinator& resourceRequestCoordinator_;
  TaskPackageBuilder& taskPackageBuilder_;
  TaskReconstructionService& taskReconstructionService_;
  TaskLifecycleTracker& taskLifecycleTracker_;
  std::unordered_map<std::string, MissionCommand> missionCommandsByMissionId_;
  std::unordered_map<std::string, TaskConstraint> taskConstraintsByMissionId_;
  std::unordered_map<std::string, AllocationRequest> allocationRequestsByRequestId_;
  std::unordered_map<std::string, TaskPackage> taskPackagesByMissionId_;
};

}  // namespace wp02_taskmgmt