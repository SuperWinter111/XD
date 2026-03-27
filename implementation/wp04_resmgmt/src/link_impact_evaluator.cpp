#include "wp04_resmgmt/link_impact_evaluator.h"

namespace wp04_resmgmt {

AvailabilityImpact LinkImpactEvaluator::evaluate(const LinkQualitySnapshot& linkQualitySnapshot,
                                                 const DegradationAlert* degradationAlert) const {
  AvailabilityImpact impact;
  impact.linkAvailable = linkQualitySnapshot.qualityScore >= 40 && degradationAlert == nullptr;
  impact.reason = impact.linkAvailable ? "link_ok" : "link_degraded";
  return impact;
}

}  // namespace wp04_resmgmt