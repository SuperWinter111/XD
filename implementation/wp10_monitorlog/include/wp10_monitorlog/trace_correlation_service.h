#pragma once
#include "wp10_monitorlog/message_types.h"
namespace wp10_monitorlog {
class TraceCorrelationService {
 public:
  TraceCorrelationRecord correlate(const DeliveryReceipt& deliveryReceipt,
                                   const SecurityEvent& securityEvent,
                                   const ReleaseEvent& releaseEvent) const;
};
}