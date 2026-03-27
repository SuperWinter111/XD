#include <cassert>

#include "test_support.h"
#include "wp06_commnet/commnet_application_service.h"

using namespace wp06_commnet;

int main() {
  LinkTelemetryCollector linkTelemetryCollector;
  QualityScoringService qualityScoringService;
  DegradationPolicyEngine degradationPolicyEngine;
  SecurityEventBridge securityEventBridge;
  TopologyViewService topologyViewService;
  CommNetApplicationService applicationService(linkTelemetryCollector,
                                               qualityScoringService,
                                               degradationPolicyEngine,
                                               securityEventBridge,
                                               topologyViewService);

  const auto result = applicationService.evaluateLink(test_support::makeDegradedLinkTelemetry());
  assert(result.linkQualitySnapshot.qualityScore < 60);
  assert(result.degradationAlert.has_value());
  assert(result.degradationAlert->triggerThreshold == "quality_score<60");
  return 0;
}