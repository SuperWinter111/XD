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

  const auto receiveResult = applicationService.receiveMissionCommand(
      ReceiveMissionCommandCommand{MissionCommand{"trace-task-001",
                                                  "mission-001",
                                                  "ext.command.console",
                                                  "strike_target_cluster",
                                                  "sector-alpha",
                                                  1711180000000,
                                                  1711183600000,
                                                  MissionPriority::kHigh,
                                                  {"uav", "sensor", "weapon"}}});
  assert(receiveResult.accepted);
  assert(receiveResult.taskConstraint.constraintId == "mission-001:constraint");
  assert(receiveResult.allocationRequest.requestId == "mission-001:allocation_request");

  const auto commitResult = applicationService.commitAllocationDecision(
      CommitAllocationDecisionCommand{AllocationDecision{"trace-task-001",
                                                         "mission-001:allocation_request",
                                                         "mission-001",
                                                         true,
                                                         {"uav-001", "sensor-eo-001", "weapon-agt-001"},
                                                         {}}});
  assert(commitResult.taskPackageCreated);
  assert(commitResult.taskPackage.has_value());
  assert(commitResult.taskPackage->taskPackageId == "mission-001:task_package");
  assert(commitResult.taskPackage->allocatedResourceIds.size() == 3);

  return 0;
}