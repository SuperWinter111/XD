#include "wp01_battlectrl/plan_adjustment_service.h"

namespace wp01_battlectrl {

BattlePlan PlanAdjustmentService::update(const BattlePlan& battlePlan,
                                         const PlanAdjustmentDecision& planAdjustmentDecision) const {
  BattlePlan updatedPlan = battlePlan;
  updatedPlan.planId = battlePlan.planId + ":updated";
  updatedPlan.action = battlePlan.action + ":adjusted";
  updatedPlan.constraintRef = planAdjustmentDecision.reason;
  return updatedPlan;
}

}  // namespace wp01_battlectrl