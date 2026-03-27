#include <cassert>

#include "test_support.h"
#include "wp02_taskmgmt/taskmgmt_command_mapper.h"

using namespace wp02_taskmgmt;

int main() {
  TaskMgmtCommandMapper mapper;

  const auto missionCommand = mapper.map(test_support::makeMissionCommandRequest());
  assert(missionCommand.has_value());
  assert(missionCommand->missionCommand.priority == MissionPriority::kHigh);

  auto invalidMissionCommand = test_support::makeMissionCommandRequest();
  invalidMissionCommand.targetArea.clear();
  assert(!mapper.map(invalidMissionCommand).has_value());

  const auto allocationDecision = mapper.map(test_support::makeAcceptedAllocationDecisionRequest());
  assert(allocationDecision.has_value());
  assert(allocationDecision->allocationDecision.accepted);

  const auto exceptionCommand = mapper.map(test_support::makeBoundaryBreakRequest());
  assert(exceptionCommand.has_value());
  assert(exceptionCommand->reason == ReconstructionReason::kResourceLostBeyondTaskBoundary);

  return 0;
}