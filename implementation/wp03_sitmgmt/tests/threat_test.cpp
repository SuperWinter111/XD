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

  const auto recommendationItem = test_support::makeRecommendationItem();
  const auto result = applicationService.process(test_support::makeRawTargetInput(),
                                                 nullptr,
                                                 nullptr,
                                                 &recommendationItem);
  assert(result.threatAssessment.trackId == "fused:track-001");
  assert(result.threatAssessment.reasons.size() == 2);
  return 0;
}