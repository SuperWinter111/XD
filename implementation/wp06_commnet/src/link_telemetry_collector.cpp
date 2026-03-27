#include "wp06_commnet/link_telemetry_collector.h"

namespace wp06_commnet {

LinkObservation LinkTelemetryCollector::collect(const RawLinkTelemetry& rawLinkTelemetry) const {
  LinkObservation linkObservation;
  linkObservation.traceId = rawLinkTelemetry.traceId;
  linkObservation.linkId = rawLinkTelemetry.linkId;
  linkObservation.sourceNodeId = rawLinkTelemetry.sourceNodeId;
  linkObservation.targetNodeId = rawLinkTelemetry.targetNodeId;
  linkObservation.latencyMs = rawLinkTelemetry.latencyMs;
  linkObservation.packetLossPct = rawLinkTelemetry.packetLossPct;
  linkObservation.signalStrengthDbm = rawLinkTelemetry.signalStrengthDbm;
  linkObservation.scoringSource = "telemetry_normalized";
  linkObservation.observedAtUtcMs = rawLinkTelemetry.observedAtUtcMs;
  return linkObservation;
}

}  // namespace wp06_commnet