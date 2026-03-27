#include "wp07_msgservice/delivery_tracker.h"

namespace wp07_msgservice {

DeliveryReceipt DeliveryTracker::recordDelivery(const MessageEnvelope& envelope,
                                                const SubscriptionBinding& subscriber,
                                                DeliveryStatus status,
                                                DeliveryErrorCode errorCode,
                                                std::int64_t deliveredAtUtcMs) const {
  DeliveryReceipt receipt;
  receipt.receiptId = envelope.traceId + ":" + subscriber.subscriberEndpointId;
  receipt.topic = envelope.topic;
  receipt.messageTraceId = envelope.traceId;
  receipt.subscriberEndpointId = subscriber.subscriberEndpointId;
  receipt.status = status;
  receipt.errorCode = errorCode;
  receipt.deliveredAtUtcMs = deliveredAtUtcMs;
  return receipt;
}

}  // namespace wp07_msgservice
