#include <cassert>

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

  const auto boundaryBreak = applicationService.handleExecutionException(
      HandleExecutionExceptionCommand{"trace-task-001",
                                      "mission-001",
                                      "mission-001:task_package",
                                      ReconstructionReason::kResourceLostBeyondTaskBoundary,
                                      true,
                                      1711181000000});
  assert(boundaryBreak.reconstructionDecision.requiresReconstruction);
  assert(boundaryBreak.reconstructionDecision.expectedAction == "task_reconstruction");

  const auto planLevel = applicationService.handleExecutionException(
      HandleExecutionExceptionCommand{"trace-task-001",
                                      "mission-001",
                                      "mission-001:task_package",
                                      ReconstructionReason::kExecutionBoundaryBroken,
                                      false,
                                      1711181001000});
  assert(!planLevel.reconstructionDecision.requiresReconstruction);
  assert(planLevel.reconstructionDecision.expectedAction == "continue_plan_level_adjustment");

  return 0;
}