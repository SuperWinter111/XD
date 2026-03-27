#pragma once

#include <cstdint>

#include "wp07_msgservice/message_types.h"

namespace wp07_msgservice {

struct RegisterTopicCommand {
  TopicDefinition topicDefinition;
};

struct RegisterSubscriptionCommand {
  SubscriptionBinding binding;
  std::string traceId;
  std::int64_t recordedAtUtcMs{0};
};

struct RecordDeliveryCommand {
  MessageEnvelope envelope;
  SubscriptionBinding subscriber;
  DeliveryStatus status{DeliveryStatus::kFailed};
  DeliveryErrorCode errorCode{DeliveryErrorCode::kNone};
  std::int64_t deliveredAtUtcMs{0};
};

struct HandleDeliveryFailureCommand {
  MessageEnvelope envelope;
  FailureReason failureReason{FailureReason::kUnknown};
  std::uint32_t retryCount{0};
  std::int64_t scheduledAtUtcMs{0};
  std::int64_t lastAttemptUtcMs{0};
};

}  // namespace wp07_msgservice