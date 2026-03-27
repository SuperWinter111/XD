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
  const auto platformAlert = test_support::makePlatformAlert();
  const auto updated = applicationService.adjustPlan(test_support::makeTaskConstraint(),
                                                     test_support::makeAllocationDecision(),
                                                     test_support::makeMissionProgress(),
                                                     &platformAlert,
                                                     nullptr,
                                                     created.battlePlan);
  assert(updated.planAdjustmentDecision.shouldUpdatePlan);
  assert(updated.battlePlan.planId == "task-001:plan:updated");
  return 0;
}