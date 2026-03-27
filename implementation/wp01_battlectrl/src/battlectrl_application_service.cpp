#include "wp01_battlectrl/battlectrl_application_service.h"

namespace wp01_battlectrl {

BattleCtrlApplicationService::BattleCtrlApplicationService(TaskIntentAdapter& taskIntentAdapter,
                                                           BattlePlanGenerator& battlePlanGenerator,
                                                           ConstraintGuard& constraintGuard,
                                                           PlanAdjustmentService& planAdjustmentService,
                                                           EffectAssessmentService& effectAssessmentService,
                                                           RuleAssistGateway& ruleAssistGateway)
    : taskIntentAdapter_(taskIntentAdapter),
      battlePlanGenerator_(battlePlanGenerator),
      constraintGuard_(constraintGuard),
      planAdjustmentService_(planAdjustmentService),
      effectAssessmentService_(effectAssessmentService),
      ruleAssistGateway_(ruleAssistGateway) {}

BattlePlanningResult BattleCtrlApplicationService::createPlan(const TaskConstraint& taskConstraint,
                                                              const TaskPackage& taskPackage,
                                                              const AllocationDecision& allocationDecision,
                                                              const ThreatAssessment& threatAssessment) const {
  BattlePlanningResult result;
  result.engagementInput = taskIntentAdapter_.adapt(taskConstraint, taskPackage);
  result.battlePlan = battlePlanGenerator_.generate(result.engagementInput, allocationDecision, threatAssessment);
  result.inferenceRequest = ruleAssistGateway_.build(threatAssessment, result.engagementInput);
  return result;
}

BattleAdjustmentResult BattleCtrlApplicationService::adjustPlan(const TaskConstraint& taskConstraint,
                                                                const AllocationDecision& allocationDecision,
                                                                const MissionProgress& missionProgress,
                                                                const PlatformAlert* platformAlert,
                                                                const DegradationAlert* degradationAlert,
                                                                const BattlePlan& currentBattlePlan) const {
  BattleAdjustmentResult result;
  result.planAdjustmentDecision = constraintGuard_.evaluate(
      taskConstraint, allocationDecision, missionProgress, platformAlert, degradationAlert);
  result.battlePlan = result.planAdjustmentDecision.shouldUpdatePlan
                          ? planAdjustmentService_.update(currentBattlePlan, result.planAdjustmentDecision)
                          : currentBattlePlan;
  return result;
}

EngagementEffectReport BattleCtrlApplicationService::buildEffectReport(const TaskPackage& taskPackage,
                                                                       const BattlePlan& battlePlan,
                                                                       const MissionProgress& missionProgress,
                                                                       const ThreatAssessment& threatAssessment) const {
  return effectAssessmentService_.assess(taskPackage, battlePlan, missionProgress, threatAssessment);
}

}  // namespace wp01_battlectrl