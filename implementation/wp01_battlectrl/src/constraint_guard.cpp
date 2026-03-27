#include "wp01_battlectrl/constraint_guard.h"

namespace wp01_battlectrl {

PlanAdjustmentDecision ConstraintGuard::evaluate(const TaskConstraint& taskConstraint,
                                                 const AllocationDecision& allocationDecision,
                                                 const MissionProgress& missionProgress,
                                                 const PlatformAlert* platformAlert,
                                                 const DegradationAlert* degradationAlert) const {
  PlanAdjustmentDecision decision;
  decision.withinConstraint = allocationDecision.accepted && taskConstraint.boundary != "broken";
  if (!decision.withinConstraint) {
    decision.shouldFallbackTaskMgmt = true;
    decision.reason = "constraint_broken";
    return decision;
  }

  if (platformAlert != nullptr || degradationAlert != nullptr || missionProgress.progressState == "DEVIATED") {
    decision.shouldUpdatePlan = true;
    decision.reason = platformAlert != nullptr ? platformAlert->alertCode : "link_or_progress_adjustment";
    return decision;
  }

  decision.reason = "plan_stable";
  return decision;
}

}  // namespace wp01_battlectrl