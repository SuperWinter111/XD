#pragma once

#include "wp01_battlectrl/battle_plan_generator.h"
#include "wp01_battlectrl/constraint_guard.h"
#include "wp01_battlectrl/effect_assessment_service.h"
#include "wp01_battlectrl/plan_adjustment_service.h"
#include "wp01_battlectrl/rule_assist_gateway.h"
#include "wp01_battlectrl/task_intent_adapter.h"

namespace wp01_battlectrl {

struct BattlePlanningResult {
  EngagementInput engagementInput;
  BattlePlan battlePlan;
  InferenceRequest inferenceRequest;
};

struct BattleAdjustmentResult {
  PlanAdjustmentDecision planAdjustmentDecision;
  BattlePlan battlePlan;
};

class BattleCtrlApplicationService {
 public:
  BattleCtrlApplicationService(TaskIntentAdapter& taskIntentAdapter,
                               BattlePlanGenerator& battlePlanGenerator,
                               ConstraintGuard& constraintGuard,
                               PlanAdjustmentService& planAdjustmentService,
                               EffectAssessmentService& effectAssessmentService,
                               RuleAssistGateway& ruleAssistGateway);

  BattlePlanningResult createPlan(const TaskConstraint& taskConstraint,
                                  const TaskPackage& taskPackage,
                                  const AllocationDecision& allocationDecision,
                                  const ThreatAssessment& threatAssessment) const;
  BattleAdjustmentResult adjustPlan(const TaskConstraint& taskConstraint,
                                    const AllocationDecision& allocationDecision,
                                    const MissionProgress& missionProgress,
                                    const PlatformAlert* platformAlert,
                                    const DegradationAlert* degradationAlert,
                                    const BattlePlan& currentBattlePlan) const;
  EngagementEffectReport buildEffectReport(const TaskPackage& taskPackage,
                                           const BattlePlan& battlePlan,
                                           const MissionProgress& missionProgress,
                                           const ThreatAssessment& threatAssessment) const;

 private:
  TaskIntentAdapter& taskIntentAdapter_;
  BattlePlanGenerator& battlePlanGenerator_;
  ConstraintGuard& constraintGuard_;
  PlanAdjustmentService& planAdjustmentService_;
  EffectAssessmentService& effectAssessmentService_;
  RuleAssistGateway& ruleAssistGateway_;
};

}  // namespace wp01_battlectrl