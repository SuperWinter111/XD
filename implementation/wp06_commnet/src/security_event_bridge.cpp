#include "wp06_commnet/security_event_bridge.h"

namespace wp06_commnet {

SecurityEvent SecurityEventBridge::build(const RawSecuritySignal& rawSecuritySignal) const {
  SecurityEvent securityEvent;
  securityEvent.traceId = rawSecuritySignal.traceId;
  securityEvent.sourceNodeId = rawSecuritySignal.sourceNodeId;
  securityEvent.eventType = rawSecuritySignal.eventType;
  securityEvent.severity = rawSecuritySignal.severity;
  securityEvent.auditCorrelationId = rawSecuritySignal.traceId + ":audit";
  securityEvent.eventAtUtcMs = rawSecuritySignal.observedAtUtcMs;
  return securityEvent;
}

}  // namespace wp06_commnet