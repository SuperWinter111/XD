#include "wp03_sitmgmt/situation_summary_service.h"

namespace wp03_sitmgmt {

SituationOutputs SituationSummaryService::build(const FusedTrack& fusedTrack,
                                                const ThreatAssessment& threatAssessment) const {
  SituationOutputs outputs;
  outputs.situationSnapshot.traceId = fusedTrack.traceId;
  outputs.situationSnapshot.activeTrackIds = {fusedTrack.trackId};
  outputs.situationSnapshot.summary = threatAssessment.threatLevel + " threat observed";

  outputs.situationSummaryReport.traceId = fusedTrack.traceId;
  outputs.situationSummaryReport.reportId = fusedTrack.trackId + ":summary";
  outputs.situationSummaryReport.summary = outputs.situationSnapshot.summary;

  outputs.criticalAlert.traceId = fusedTrack.traceId;
  outputs.criticalAlert.alertCode = threatAssessment.threatLevel == "high" ? "critical_track_detected" : "situation_watch";
  outputs.criticalAlert.severity = threatAssessment.threatLevel == "high" ? "critical" : "warning";
  return outputs;
}

}  // namespace wp03_sitmgmt