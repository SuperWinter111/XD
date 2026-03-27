#pragma once

#include "wp01_battlectrl/message_types.h"

namespace wp01_battlectrl::test_support {

inline TaskConstraint makeTaskConstraint() {
  return TaskConstraint{"trace-battle-001", "task-001", "strike_target", "constraint-zone-a"};
}

inline TaskPackage makeTaskPackage() {
  return TaskPackage{"trace-battle-001", "task-001", "mission-001", "engage"};
}

inline AllocationDecision makeAllocationDecision() {
  return AllocationDecision{"trace-battle-001", "request-001", "mission-001", true, {"uav-001"}, "fully_satisfied"};
}

inline ThreatAssessment makeThreatAssessment() {
  return ThreatAssessment{"trace-battle-001", "fused:track-001", "high", {"reason-1"}};
}

inline MissionProgress makeMissionProgress() {
  return MissionProgress{"trace-battle-001", "mission-001", "uav-001", "IN_PROGRESS", 60};
}

inline MissionProgress makeCompletedMissionProgress() {
  return MissionProgress{"trace-battle-001", "mission-001", "uav-001", "COMPLETED", 100};
}

inline PlatformAlert makePlatformAlert() {
  return PlatformAlert{"trace-battle-001", "mission-001", "uav-001", "payload_fault"};
}

inline DegradationAlert makeDegradationAlert() {
  return DegradationAlert{"trace-battle-001", "link-001", "uav-001->cmd-001"};
}

inline AllocationDecision makeRejectedAllocationDecision() {
  return AllocationDecision{"trace-battle-001", "request-002", "mission-001", false, {}, "resource_unavailable"};
}

}  // namespace wp01_battlectrl::test_support