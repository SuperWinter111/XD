#pragma once

#include <string>
#include <vector>

namespace wp10_monitorlog {

struct DeliveryReceipt { std::string traceId; std::string topic; bool success{false}; };
struct DeadLetterRecord { std::string traceId; std::string topic; std::string reason; };
struct LinkQualitySnapshot { std::string traceId; std::string linkId; unsigned qualityScore{0}; };
struct DegradationAlert { std::string traceId; std::string linkId; std::string impactScope; };
struct SecurityEvent { std::string traceId; std::string sourceNodeId; std::string severity; };
struct AuditEvent { std::string traceId; std::string eventType; };
struct ReleaseEvent { std::string traceId; std::string releaseId; std::string result; };

struct MonitorMetric { std::string traceId; std::string metricName; double metricValue{0.0}; std::string sourceDomain; };
struct MonitorAlert { std::string traceId; std::string alertCode; std::string severity; std::string trigger; };
struct LogDigest { std::string traceId; std::string sourceDomain; std::string summary; };
struct TraceCorrelationRecord { std::string traceId; std::vector<std::string> correlatedNodes; };

}  // namespace wp10_monitorlog