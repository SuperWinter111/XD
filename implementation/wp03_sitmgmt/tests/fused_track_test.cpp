#include <cassert>

#include "test_support.h"
#include "wp03_sitmgmt/sitmgmt_application_service.h"

using namespace wp03_sitmgmt;

int main() {
  PerceptionIngestService perceptionIngestService;
  TrackAssociationService trackAssociationService;
  AttributeFusionService attributeFusionService;
  ThreatAssessmentService threatAssessmentService;
  SituationSummaryService situationSummaryService;
  SitMgmtApplicationService applicationService(perceptionIngestService,
                                               trackAssociationService,
                                               attributeFusionService,
                                               threatAssessmentService,
                                               situationSummaryService);

  const auto externalObservation = test_support::makeExternalObservation();
  const auto result = applicationService.process(test_support::makeRawTargetInput(),
                                                 &externalObservation,
                                                 nullptr,
                                                 nullptr);
  assert(result.fusedTrack.trackId == "fused:track-001");
  assert(result.fusedTrack.confidence > 0.8);
  return 0;
}