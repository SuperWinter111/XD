#include "wp06_commnet/quality_scoring_service.h"

namespace wp06_commnet {

LinkQualitySnapshot QualityScoringService::score(const LinkObservation& linkObservation) const {
  double score = 100.0;
  score -= static_cast<double>(linkObservation.latencyMs) / 2.0;
  score -= linkObservation.packetLossPct * 3.0;
  if (linkObservation.signalStrengthDbm < -85.0) {
    score -= 15.0;
  }
  if (score < 0.0) {
    score = 0.0;
  }

  LinkQualitySnapshot linkQualitySnapshot;
  linkQualitySnapshot.traceId = linkObservation.traceId;
  linkQualitySnapshot.linkId = linkObservation.linkId;
  linkQualitySnapshot.sourceNodeId = linkObservation.sourceNodeId;
  linkQualitySnapshot.targetNodeId = linkObservation.targetNodeId;
  linkQualitySnapshot.qualityScore = static_cast<std::uint32_t>(score);
  linkQualitySnapshot.scoringSource = linkObservation.scoringSource;
  linkQualitySnapshot.observedAtUtcMs = linkObservation.observedAtUtcMs;
  return linkQualitySnapshot;
}

}  // namespace wp06_commnet