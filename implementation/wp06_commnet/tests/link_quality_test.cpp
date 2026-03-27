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

  const auto result = applicationService.evaluateLink(test_support::makeHealthyLinkTelemetry());
  assert(result.linkQualitySnapshot.linkId == "link-001");
  assert(result.linkQualitySnapshot.qualityScore > 60);
  assert(!result.degradationAlert.has_value());
  return 0;
}