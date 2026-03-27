#include "wp06_commnet/degradation_policy_engine.h"

namespace wp06_commnet {

std::optional<DegradationAlert> DegradationPolicyEngine::evaluate(const LinkQualitySnapshot& linkQualitySnapshot) const {
  if (linkQualitySnapshot.qualityScore >= 60) {
    return std::nullopt;
  }

  DegradationAlert degradationAlert;
  degradationAlert.traceId = linkQualitySnapshot.traceId;
  degradationAlert.linkId = linkQualitySnapshot.linkId;
  degradationAlert.triggerThreshold = "quality_score<60";
  degradationAlert.impactScope = linkQualitySnapshot.sourceNodeId + "->" + linkQualitySnapshot.targetNodeId;
  degradationAlert.eventAtUtcMs = linkQualitySnapshot.observedAtUtcMs;
  return degradationAlert;
}

}  // namespace wp06_commnet