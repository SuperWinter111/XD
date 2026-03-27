#pragma once

#include "wp06_commnet/message_types.h"

namespace wp06_commnet::test_support {

inline RawLinkTelemetry makeHealthyLinkTelemetry() {
  return RawLinkTelemetry{"trace-comm-001", "link-001", "node-a", "node-b", 18, 0.5, -62.0, 1711183000000};
}

inline RawLinkTelemetry makeDegradedLinkTelemetry() {
  return RawLinkTelemetry{"trace-comm-002", "link-002", "node-a", "node-c", 120, 12.0, -92.0, 1711183100000};
}

inline RawSecuritySignal makeRawSecuritySignal() {
  return RawSecuritySignal{"trace-comm-003", "node-b", "intrusion_detected", "critical", "unexpected_peer", 1711183200000};
}

inline ResourceRegistration makeResourceRegistration() {
  return ResourceRegistration{"trace-comm-004", "node-a", "uav", "eo_sensor+weapon:agt-01"};
}

}  // namespace wp06_commnet::test_support