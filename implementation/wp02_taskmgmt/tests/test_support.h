#pragma once

#include "wp02_taskmgmt/taskmgmt_entrypoint_dto.h"

namespace wp02_taskmgmt::test_support {

inline ReceiveMissionCommandRequestDto makeMissionCommandRequest() {
  return ReceiveMissionCommandRequestDto{"trace-task-001",
                                         "mission-001",
                                         "ext.command.console",
                                         "strike_target_cluster",
                                         "sector-alpha",
                                         1711180000000,
                                         1711183600000,
                                         "high",
                                         {"uav", "sensor", "weapon"}};
}

inline CommitAllocationDecisionRequestDto makeAcceptedAllocationDecisionRequest() {
  return CommitAllocationDecisionRequestDto{"trace-task-001",
                                            "mission-001:allocation_request",
                                            "mission-001",
                                            true,
                                            {"uav-001", "sensor-eo-001", "weapon-agt-001"},
                                            {}};
}

inline CommitAllocationDecisionRequestDto makeRejectedAllocationDecisionRequest() {
  return CommitAllocationDecisionRequestDto{"trace-task-001",
                                            "mission-001:allocation_request",
                                            "mission-001",
                                            false,
                                            {},
                                            {"uav-001"}};
}

inline HandleExecutionExceptionRequestDto makeBoundaryBreakRequest() {
  return HandleExecutionExceptionRequestDto{"trace-task-001",
                                            "mission-001",
                                            "mission-001:task_package",
                                            "resource_lost_beyond_task_boundary",
                                            true,
                                            1711181000000};
}

inline HandleExecutionExceptionRequestDto makePlanLevelExceptionRequest() {
  return HandleExecutionExceptionRequestDto{"trace-task-001",
                                            "mission-001",
                                            "mission-001:task_package",
                                            "execution_boundary_broken",
                                            false,
                                            1711181001000};
}

}  // namespace wp02_taskmgmt::test_support