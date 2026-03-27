#include "wp03_sitmgmt/threat_assessment_service.h"

namespace wp03_sitmgmt {

ThreatAssessment ThreatAssessmentService::assess(const FusedTrack& fusedTrack,
                                                 const RecommendationItem* recommendationItem) const {
  ThreatAssessment threatAssessment;
  threatAssessment.traceId = fusedTrack.traceId;
  threatAssessment.trackId = fusedTrack.trackId;
  threatAssessment.threatLevel = fusedTrack.confidence >= 0.8 ? "high" : "medium";
  threatAssessment.reasons.push_back("fused_confidence=" + std::to_string(fusedTrack.confidence));
  if (recommendationItem != nullptr) {
    threatAssessment.reasons.push_back("recommendation_ref=" + recommendationItem->ruleId);
  }
  return threatAssessment;
}

}  // namespace wp03_sitmgmt