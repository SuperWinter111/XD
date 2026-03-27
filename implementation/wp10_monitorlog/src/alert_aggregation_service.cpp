#include "wp10_monitorlog/alert_aggregation_service.h"
namespace wp10_monitorlog {
MonitorAlert AlertAggregationService::build(const DeadLetterRecord* deadLetterRecord,
                                            const DegradationAlert* degradationAlert,
                                            const SecurityEvent* securityEvent,
                                            const ReleaseEvent* releaseEvent) const {
  if (deadLetterRecord != nullptr) return MonitorAlert{deadLetterRecord->traceId, "dead_letter_detected", "high", deadLetterRecord->reason};
  if (securityEvent != nullptr) return MonitorAlert{securityEvent->traceId, "security_event_detected", securityEvent->severity, securityEvent->sourceNodeId};
  if (releaseEvent != nullptr && releaseEvent->result != "success") return MonitorAlert{releaseEvent->traceId, "release_failed", "high", releaseEvent->result};
  if (degradationAlert != nullptr) return MonitorAlert{degradationAlert->traceId, "link_degraded", "warning", degradationAlert->impactScope};
  return MonitorAlert{"trace-none", "monitor_ok", "info", "none"};
}
}