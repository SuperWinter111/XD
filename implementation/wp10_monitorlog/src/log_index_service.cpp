#include "wp10_monitorlog/log_index_service.h"
namespace wp10_monitorlog {
LogDigest LogIndexService::build(const DeliveryReceipt& deliveryReceipt, const SecurityEvent& securityEvent) const {
  return LogDigest{deliveryReceipt.traceId, "msg+sec", deliveryReceipt.topic + "+" + securityEvent.sourceNodeId};
}
}