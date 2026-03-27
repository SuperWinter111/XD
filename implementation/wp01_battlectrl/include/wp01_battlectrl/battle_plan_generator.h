#pragma once

#include "wp01_battlectrl/message_types.h"

namespace wp01_battlectrl {

class BattlePlanGenerator {
 public:
  BattlePlan generate(const EngagementInput& engagementInput,
                      const AllocationDecision& allocationDecision,
                      const ThreatAssessment& threatAssessment) const;
};

}  // namespace wp01_battlectrl