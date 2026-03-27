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

  const auto targetTruth = test_support::makeTargetTruth();
  const auto recommendationItem = test_support::makeRecommendationItem();
  const auto result = applicationService.process(test_support::makeRawTargetInput(),
                                                 nullptr,
                                                 &targetTruth,
                                                 &recommendationItem);
  assert(result.standardizedObservation.sources.back() == "simulation_truth_ref");
  assert(result.threatAssessment.reasons.back() == "recommendation_ref=rule-001");
  return 0;
}