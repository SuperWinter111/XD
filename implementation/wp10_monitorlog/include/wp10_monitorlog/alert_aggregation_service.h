#pragma once
#include "wp10_monitorlog/message_types.h"
namespace wp10_monitorlog {
class AlertAggregationService {
 public:
  MonitorAlert build(const DeadLetterRecord* deadLetterRecord,
                     const DegradationAlert* degradationAlert,
                     const SecurityEvent* securityEvent,
                     const ReleaseEvent* releaseEvent) const;
};
}