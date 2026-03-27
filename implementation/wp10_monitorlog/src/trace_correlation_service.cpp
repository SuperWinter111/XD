#include "wp10_monitorlog/trace_correlation_service.h"
namespace wp10_monitorlog {
TraceCorrelationRecord TraceCorrelationService::correlate(const DeliveryReceipt& deliveryReceipt,
                                                          const SecurityEvent& securityEvent,
                                                          const ReleaseEvent& releaseEvent) const {
  return TraceCorrelationRecord{deliveryReceipt.traceId, {deliveryReceipt.topic, securityEvent.sourceNodeId, releaseEvent.releaseId}};
}
}