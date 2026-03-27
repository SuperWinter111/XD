#pragma once

#include <cstdint>
#include <string>

#include "wp07_msgservice/message_types.h"

namespace wp07_msgservice {

class DeliveryTracker {
 public:
  DeliveryReceipt recordDelivery(const MessageEnvelope& envelope,
                                 const SubscriptionBinding& subscriber,
                                 DeliveryStatus status,
                                 DeliveryErrorCode errorCode,
                                 std::int64_t deliveredAtUtcMs) const;
};

}  // namespace wp07_msgservice
