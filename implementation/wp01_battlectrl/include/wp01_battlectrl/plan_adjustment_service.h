#pragma once

#include "wp01_battlectrl/message_types.h"

namespace wp01_battlectrl {

class PlanAdjustmentService {
 public:
  BattlePlan update(const BattlePlan& battlePlan, const PlanAdjustmentDecision& planAdjustmentDecision) const;
};

}  // namespace wp01_battlectrl