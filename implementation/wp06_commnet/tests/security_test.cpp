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

  const auto securityEvent = applicationService.buildSecurityEvent(test_support::makeRawSecuritySignal());
  assert(securityEvent.sourceNodeId == "node-b");
  assert(securityEvent.eventType == "intrusion_detected");
  assert(securityEvent.auditCorrelationId == "trace-comm-003:audit");
  return 0;
}