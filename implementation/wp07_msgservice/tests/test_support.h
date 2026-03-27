#pragma once

#include "wp07_msgservice/message_types.h"

namespace wp07_msgservice::test_support {

inline TopicDefinition makeDeliveryReceiptTopic() {
  return TopicDefinition{"bms/core/ops/msg/delivery_receipt",
                         "msg",
                         "DeliveryReceipt",
                         "reliable",
                         TopicState::kActive,
                         "team-msgservice",
                         "proto://bms/schema/message.proto#DeliveryReceipt",
                         604800000};
}

inline SubscriptionBinding makeSuccessBinding() {
  return SubscriptionBinding{"sub-001",
                             "bms/core/ops/msg/delivery_receipt",
                             "monitorlog",
                             SubscriptionBindingStatus::kSuccess,
                             ""};
}

inline SubscriptionBinding makeRejectedBinding() {
  return SubscriptionBinding{"sub-002",
                             "bms/core/ops/msg/delivery_receipt",
                             "legacy-monitor",
                             SubscriptionBindingStatus::kRejected,
                             "schema_version_not_allowed"};
}

inline MessageEnvelope makeDeliveryEnvelope(const std::string& traceId) {
  return MessageEnvelope{traceId,
                         "bms/core/ops/msg/delivery_receipt",
                         "DeliveryReceipt",
                         "formal08.v1"};
}

}  // namespace wp07_msgservice::test_support