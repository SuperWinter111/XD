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

  (void)handler.handleRequest(test_support::makeMissionCommandRequest());
  (void)handler.handleRequest(test_support::makeRejectedAllocationDecisionRequest());
  (void)handler.handleRequest(test_support::makeBoundaryBreakRequest());

  const auto& records = applicationService.lifecycleTracker().records();
  assert(records.size() >= 5);
  assert(records.front().stage == TaskLifecycleStage::kCommandReceived);
  assert(records[1].stage == TaskLifecycleStage::kDecomposed);
  assert(records[2].stage == TaskLifecycleStage::kAllocationRequested);
  assert(records[3].stage == TaskLifecycleStage::kAllocationResolved);
  assert(records.back().stage == TaskLifecycleStage::kReconstructionRequired);

  return 0;
}