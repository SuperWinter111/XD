#include <cassert>

#include "test_support.h"
#include "wp02_taskmgmt/taskmgmt_application_service.h"

using namespace wp02_taskmgmt;

int main() {
  CommandNormalizer commandNormalizer;
  TaskDecomposer taskDecomposer;
  ResourceRequestCoordinator resourceRequestCoordinator;
  TaskPackageBuilder taskPackageBuilder;
  TaskReconstructionService taskReconstructionService;
  TaskLifecycleTracker taskLifecycleTracker;

  TaskMgmtApplicationService applicationService(commandNormalizer,
                                                taskDecomposer,
                                                resourceRequestCoordinator,
                                                taskPackageBuilder,
                                                taskReconstructionService,
                                                taskLifecycleTracker);

  (void)applicationService.receiveMissionCommand(
      ReceiveMissionCommandCommand{MissionCommand{"trace-task-001",
                                                  "mission-001",
                                                  "ext.command.console",
                                                  "strike_target_cluster",
                                                  "sector-alpha",
                                                  1711180000000,
                                                  1711183600000,
                                                  MissionPriority::kHigh,
                                                  {"uav", "sensor", "weapon"}}});
  (void)applicationService.commitAllocationDecision(
      CommitAllocationDecisionCommand{AllocationDecision{"trace-task-001",
                                                         "mission-001:allocation_request",
                                                         "mission-001",
                                                         true,
                                                         {"uav-001", "sensor-eo-001", "weapon-agt-001"},
                                                         {}}});

  applicationService.recordCommandAck(CommandAck{"trace-task-001", "mission-001", true, "accepted"});
  applicationService.recordMissionProgress(MissionProgress{"trace-task-001", "mission-001", "IN_PROGRESS"});
  applicationService.recordEffectReport(EngagementEffectReport{"trace-task-001", "mission-001", "SUCCESS"});

  const auto taskPackage = applicationService.findTaskPackage("mission-001");
  assert(taskPackage.has_value());
  assert(taskPackage->executionState == ExecutionState::kCompleted);

  const auto& records = applicationService.lifecycleTracker().records();
  assert(records[4].stage == TaskLifecycleStage::kPlanCreated);
  assert(records[5].stage == TaskLifecycleStage::kCommandAcknowledged);
  assert(records[6].stage == TaskLifecycleStage::kMissionProgressUpdated);
  assert(records[7].stage == TaskLifecycleStage::kEffectReported);

  return 0;
}