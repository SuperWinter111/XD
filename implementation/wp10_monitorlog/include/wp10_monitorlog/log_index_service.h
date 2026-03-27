#pragma once
#include "wp10_monitorlog/message_types.h"
namespace wp10_monitorlog {
class LogIndexService {
 public:
  LogDigest build(const DeliveryReceipt& deliveryReceipt, const SecurityEvent& securityEvent) const;
};
}