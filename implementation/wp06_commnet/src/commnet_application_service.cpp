#include "wp06_commnet/commnet_application_service.h"

namespace wp06_commnet {

CommNetApplicationService::CommNetApplicationService(LinkTelemetryCollector& linkTelemetryCollector,
                                                     QualityScoringService& qualityScoringService,
                                                     DegradationPolicyEngine& degradationPolicyEngine,
                                                     SecurityEventBridge& securityEventBridge,
                                                     TopologyViewService& topologyViewService)
    : linkTelemetryCollector_(linkTelemetryCollector),
      qualityScoringService_(qualityScoringService),
      degradationPolicyEngine_(degradationPolicyEngine),
      securityEventBridge_(securityEventBridge),
      topologyViewService_(topologyViewService) {}

LinkEvaluationResult CommNetApplicationService::evaluateLink(const RawLinkTelemetry& rawLinkTelemetry) const {
  LinkEvaluationResult result;
  result.linkObservation = linkTelemetryCollector_.collect(rawLinkTelemetry);
  result.linkQualitySnapshot = qualityScoringService_.score(result.linkObservation);
  result.degradationAlert = degradationPolicyEngine_.evaluate(result.linkQualitySnapshot);
  return result;
}

SecurityEvent CommNetApplicationService::buildSecurityEvent(const RawSecuritySignal& rawSecuritySignal) const {
  return securityEventBridge_.build(rawSecuritySignal);
}

CommTopologySnapshot CommNetApplicationService::refreshTopology(const ResourceRegistration& resourceRegistration,
                                                               const RawLinkTelemetry& rawLinkTelemetry) const {
  const auto observation = linkTelemetryCollector_.collect(rawLinkTelemetry);
  return topologyViewService_.refresh(resourceRegistration, observation);
}

}  // namespace wp06_commnet