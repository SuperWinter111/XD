#include <cassert>

#include "test_support.h"
#include "wp01_battlectrl/battlectrl_application_service.h"

using namespace wp01_battlectrl;

int main() {
  TaskIntentAdapter taskIntentAdapter;
  BattlePlanGenerator battlePlanGenerator;
  ConstraintGuard constraintGuard;
  PlanAdjustmentService planAdjustmentService;
  EffectAssessmentService effectAssessmentService;
  RuleAssistGateway ruleAssistGateway;
  BattleCtrlApplicationService applicationService(taskIntentAdapter,
                                                  battlePlanGenerator,
                                                  constraintGuard,
                                                  planAdjustmentService,
                                                  effectAssessmentService,
                                                  ruleAssistGateway);

  const auto result = applicationService.createPlan(test_support::makeTaskConstraint(),
                                                    test_support::makeTaskPackage(),
                                                    test_support::makeAllocationDecision(),
                                                    test_support::makeThreatAssessment());
  assert(result.battlePlan.planId == "task-001:plan");
  assert(result.battlePlan.platformId == "uav-001");
  assert(result.inferenceRequest.requestId == "task-001:inference");
  return 0;
}