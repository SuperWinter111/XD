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

  const auto created = applicationService.createPlan(test_support::makeTaskConstraint(),
                                                     test_support::makeTaskPackage(),
                                                     test_support::makeAllocationDecision(),
                                                     test_support::makeThreatAssessment());
  const auto degraded = test_support::makeDegradationAlert();
  const auto fallback = applicationService.adjustPlan(test_support::makeTaskConstraint(),
                                                      test_support::makeRejectedAllocationDecision(),
                                                      test_support::makeMissionProgress(),
                                                      nullptr,
                                                      &degraded,
                                                      created.battlePlan);
  assert(fallback.planAdjustmentDecision.shouldFallbackTaskMgmt);
  assert(!fallback.planAdjustmentDecision.shouldUpdatePlan);
  assert(fallback.battlePlan.planId == "task-001:plan");
  return 0;
}