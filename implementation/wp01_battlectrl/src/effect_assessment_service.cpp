#include "wp01_battlectrl/effect_assessment_service.h"

namespace wp01_battlectrl {

EngagementEffectReport EffectAssessmentService::assess(const TaskPackage& taskPackage,
                                                       const BattlePlan& battlePlan,
                                                       const MissionProgress& missionProgress,
                                                       const ThreatAssessment& threatAssessment) const {
  EngagementEffectReport report;
  report.traceId = battlePlan.traceId;
  report.taskId = taskPackage.taskId;
  report.planId = battlePlan.planId;
  report.effectConclusion = missionProgress.progressPct >= 100 ? "objective_completed" : threatAssessment.threatLevel + "_threat_monitored";
  return report;
}

}  // namespace wp01_battlectrl