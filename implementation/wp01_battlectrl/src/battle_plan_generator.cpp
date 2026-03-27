#include "wp01_battlectrl/battle_plan_generator.h"

namespace wp01_battlectrl {

BattlePlan BattlePlanGenerator::generate(const EngagementInput& engagementInput,
                                         const AllocationDecision& allocationDecision,
                                         const ThreatAssessment& threatAssessment) const {
  BattlePlan battlePlan;
  battlePlan.traceId = engagementInput.traceId;
  battlePlan.planId = engagementInput.taskId + ":plan";
  battlePlan.taskId = engagementInput.taskId;
  battlePlan.missionId = engagementInput.missionId;
  battlePlan.platformId = allocationDecision.allocatedResourceIds.empty() ? "" : allocationDecision.allocatedResourceIds.front();
  battlePlan.targetTrackId = threatAssessment.trackId;
  battlePlan.action = engagementInput.requestedAction;
  battlePlan.constraintRef = engagementInput.boundary;
  return battlePlan;
}

}  // namespace wp01_battlectrl