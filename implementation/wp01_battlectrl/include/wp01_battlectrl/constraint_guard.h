#pragma once

#include "wp01_battlectrl/message_types.h"

namespace wp01_battlectrl {

class ConstraintGuard {
 public:
  PlanAdjustmentDecision evaluate(const TaskConstraint& taskConstraint,
                                  const AllocationDecision& allocationDecision,
                                  const MissionProgress& missionProgress,
                                  const PlatformAlert* platformAlert,
                                  const DegradationAlert* degradationAlert) const;
};

}  // namespace wp01_battlectrl