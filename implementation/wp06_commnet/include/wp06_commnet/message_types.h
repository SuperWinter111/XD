#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace wp06_commnet {

struct RawLinkTelemetry {
  std::string traceId;
  std::string linkId;
  std::string sourceNodeId;
  std::string targetNodeId;
  std::uint32_t latencyMs{0};
  double packetLossPct{0.0};
  double signalStrengthDbm{0.0};
  std::int64_t observedAtUtcMs{0};
};

struct RawSecuritySignal {
  std::string traceId;
  std::string sourceNodeId;
  std::string eventType;
  std::string severity;
  std::string detail;
  std::int64_t observedAtUtcMs{0};
};

struct ResourceRegistration {
  std::string traceId;
  std::string platformId;
  std::string platformType;
  std::string capabilitySource;
};

struct LinkObservation {
  std::string traceId;
  std::string linkId;
  std::string sourceNodeId;
  std::string targetNodeId;
  std::uint32_t latencyMs{0};
  double packetLossPct{0.0};
  double signalStrengthDbm{0.0};
  std::string scoringSource;
  std::int64_t observedAtUtcMs{0};
};

struct LinkQualitySnapshot {
  std::string traceId;
  std::string linkId;
  std::string sourceNodeId;
  std::string targetNodeId;
  std::uint32_t qualityScore{0};
  std::string scoringSource;
  std::int64_t observedAtUtcMs{0};
};

struct DegradationAlert {
  std::string traceId;
  std::string linkId;
  std::string triggerThreshold;
  std::string impactScope;
  std::int64_t eventAtUtcMs{0};
};

struct SecurityEvent {
  std::string traceId;
  std::string sourceNodeId;
  std::string eventType;
  std::string severity;
  std::string auditCorrelationId;
  std::int64_t eventAtUtcMs{0};
};

struct CommTopologySnapshot {
  std::string traceId;
  std::vector<std::string> nodeIds;
  std::vector<std::string> linkIds;
  std::string changeReason;
};

}  // namespace wp06_commnet