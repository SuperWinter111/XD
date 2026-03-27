#pragma once

#include "wp03_sitmgmt/message_types.h"

namespace wp03_sitmgmt {

class ThreatAssessmentService {
 public:
  ThreatAssessment assess(const FusedTrack& fusedTrack, const RecommendationItem* recommendationItem) const;
};

}  // namespace wp03_sitmgmt