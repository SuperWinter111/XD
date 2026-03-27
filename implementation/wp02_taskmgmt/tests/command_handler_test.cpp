#include <cassert>

#include "test_support.h"
#include "wp02_taskmgmt/taskmgmt_command_handler.h"

using namespace wp02_taskmgmt;

int main() {
  CommandNormalizer commandNormalizer;
  TaskDecomposer taskDecomposer;
  ResourceRequestCoordinator resourceRequestCoordinator;
  TaskPackageBuilder taskPackageBuilder;
  TaskReconstructionService taskReconstructionService;
  TaskLifecycleTracker taskLifecycleTracker;
  TaskMgmtCommandMapper commandMapper;
  TaskMgmtResponseMapper responseMapper;

  TaskMgmtApplicationService applicationService(commandNormalizer,
                                                taskDecomposer,
                                                resourceRequestCoordinator,
                                                taskPackageBuilder,
                                                taskReconstructionService,
                                                taskLifecycleTracker);
  TaskMgmtCommandHandler handler(commandMapper, responseMapper, applicationService);

  const auto receiveResponse = handler.handleRequest(test_support::makeMissionCommandRequest());
  assert(receiveResponse.meta.accepted);
  assert(receiveResponse.constraintId == "mission-001:constraint");
  assert(receiveResponse.allocationRequestId == "mission-001:allocation_request");

  const auto commitResponse = handler.handleRequest(test_support::makeAcceptedAllocationDecisionRequest());
  assert(commitResponse.meta.accepted);
  assert(commitResponse.taskPackageCreated);
  assert(commitResponse.taskPackageId == "mission-001:task_package");

  const auto exceptionResponse = handler.handleRequest(test_support::makeBoundaryBreakRequest());
  assert(exceptionResponse.meta.accepted);
  assert(exceptionResponse.requiresReconstruction);
  assert(exceptionResponse.reconstructionReason == "resource_lost_beyond_task_boundary");

  return 0;
}