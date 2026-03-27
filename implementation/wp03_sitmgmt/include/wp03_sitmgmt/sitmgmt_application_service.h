#pragma once

#include "wp03_sitmgmt/attribute_fusion_service.h"
#include "wp03_sitmgmt/perception_ingest_service.h"
#include "wp03_sitmgmt/situation_summary_service.h"
#include "wp03_sitmgmt/threat_assessment_service.h"
#include "wp03_sitmgmt/track_association_service.h"

namespace wp03_sitmgmt {

struct SituationWorkflowResult {
  StandardizedObservation standardizedObservation;
  TrackCandidate trackCandidate;
  FusedTrack fusedTrack;
  ThreatAssessment threatAssessment;
  SituationOutputs situationOutputs;
};

class SitMgmtApplicationService {
 public:
  SitMgmtApplicationService(PerceptionIngestService& perceptionIngestService,
                            TrackAssociationService& trackAssociationService,
                            AttributeFusionService& attributeFusionService,
                            ThreatAssessmentService& threatAssessmentService,
                            SituationSummaryService& situationSummaryService);

  SituationWorkflowResult process(const RawTargetInput& rawTargetInput,
                                  const ExternalObservation* externalObservation,
                                  const TargetTruth* targetTruth,
                                  const RecommendationItem* recommendationItem) const;

 private:
  PerceptionIngestService& perceptionIngestService_;
  TrackAssociationService& trackAssociationService_;
  AttributeFusionService& attributeFusionService_;
  ThreatAssessmentService& threatAssessmentService_;
  SituationSummaryService& situationSummaryService_;
};

}  // namespace wp03_sitmgmt