#pragma once

#include "wp01_battlectrl/message_types.h"

namespace wp01_battlectrl {

class EffectAssessmentService {
 public:
  EngagementEffectReport assess(const TaskPackage& taskPackage,
                                const BattlePlan& battlePlan,
                                const MissionProgress& missionProgress,
                                const ThreatAssessment& threatAssessment) const;
};

}  // namespace wp01_battlectrl