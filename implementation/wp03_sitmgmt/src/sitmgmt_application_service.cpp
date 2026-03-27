#include "wp03_sitmgmt/sitmgmt_application_service.h"

namespace wp03_sitmgmt {

SitMgmtApplicationService::SitMgmtApplicationService(PerceptionIngestService& perceptionIngestService,
                                                     TrackAssociationService& trackAssociationService,
                                                     AttributeFusionService& attributeFusionService,
                                                     ThreatAssessmentService& threatAssessmentService,
                                                     SituationSummaryService& situationSummaryService)
    : perceptionIngestService_(perceptionIngestService),
      trackAssociationService_(trackAssociationService),
      attributeFusionService_(attributeFusionService),
      threatAssessmentService_(threatAssessmentService),
      situationSummaryService_(situationSummaryService) {}

SituationWorkflowResult SitMgmtApplicationService::process(const RawTargetInput& rawTargetInput,
                                                           const ExternalObservation* externalObservation,
                                                           const TargetTruth* targetTruth,
                                                           const RecommendationItem* recommendationItem) const {
  SituationWorkflowResult result;
  result.standardizedObservation = perceptionIngestService_.ingest(rawTargetInput, externalObservation, targetTruth);
  result.trackCandidate = trackAssociationService_.associate(result.standardizedObservation);
  result.fusedTrack = attributeFusionService_.fuse(result.trackCandidate);
  result.threatAssessment = threatAssessmentService_.assess(result.fusedTrack, recommendationItem);
  result.situationOutputs = situationSummaryService_.build(result.fusedTrack, result.threatAssessment);
  return result;
}

}  // namespace wp03_sitmgmt