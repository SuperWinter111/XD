#pragma once

#include <optional>

#include "wp06_commnet/degradation_policy_engine.h"
#include "wp06_commnet/link_telemetry_collector.h"
#include "wp06_commnet/quality_scoring_service.h"
#include "wp06_commnet/security_event_bridge.h"
#include "wp06_commnet/topology_view_service.h"

namespace wp06_commnet {

struct LinkEvaluationResult {
  LinkObservation linkObservation;
  LinkQualitySnapshot linkQualitySnapshot;
  std::optional<DegradationAlert> degradationAlert;
};

class CommNetApplicationService {
 public:
  CommNetApplicationService(LinkTelemetryCollector& linkTelemetryCollector,
                            QualityScoringService& qualityScoringService,
                            DegradationPolicyEngine& degradationPolicyEngine,
                            SecurityEventBridge& securityEventBridge,
                            TopologyViewService& topologyViewService);

  LinkEvaluationResult evaluateLink(const RawLinkTelemetry& rawLinkTelemetry) const;
  SecurityEvent buildSecurityEvent(const RawSecuritySignal& rawSecuritySignal) const;
  CommTopologySnapshot refreshTopology(const ResourceRegistration& resourceRegistration,
                                       const RawLinkTelemetry& rawLinkTelemetry) const;

 private:
  LinkTelemetryCollector& linkTelemetryCollector_;
  QualityScoringService& qualityScoringService_;
  DegradationPolicyEngine& degradationPolicyEngine_;
  SecurityEventBridge& securityEventBridge_;
  TopologyViewService& topologyViewService_;
};

}  // namespace wp06_commnet