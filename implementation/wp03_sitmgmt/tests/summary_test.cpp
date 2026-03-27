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
  const auto recommendationItem = test_support::makeRecommendationItem();
  const auto result = applicationService.process(test_support::makeRawTargetInput(),
                                                 &externalObservation,
                                                 nullptr,
                                                 &recommendationItem);
  assert(result.situationOutputs.situationSnapshot.activeTrackIds.size() == 1);
  assert(result.situationOutputs.situationSummaryReport.reportId == "fused:track-001:summary");
  assert(result.situationOutputs.criticalAlert.severity == "critical");
  return 0;
}