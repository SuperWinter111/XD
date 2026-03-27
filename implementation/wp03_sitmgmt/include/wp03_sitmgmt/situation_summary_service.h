#pragma once

#include "wp03_sitmgmt/message_types.h"

namespace wp03_sitmgmt {

struct SituationOutputs {
  SituationSnapshot situationSnapshot;
  SituationSummaryReport situationSummaryReport;
  CriticalAlert criticalAlert;
};

class SituationSummaryService {
 public:
  SituationOutputs build(const FusedTrack& fusedTrack, const ThreatAssessment& threatAssessment) const;
};

}  // namespace wp03_sitmgmt