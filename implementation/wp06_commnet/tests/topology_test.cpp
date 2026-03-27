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

  const auto topologySnapshot = applicationService.refreshTopology(
      test_support::makeResourceRegistration(), test_support::makeHealthyLinkTelemetry());
  assert(topologySnapshot.linkIds.size() == 1);
  assert(topologySnapshot.nodeIds.size() == 3);
  assert(topologySnapshot.changeReason == "platform_registered_or_link_updated");
  return 0;
}