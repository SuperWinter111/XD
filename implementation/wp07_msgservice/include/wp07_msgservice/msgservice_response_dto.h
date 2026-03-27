#pragma once

#include <string>

namespace wp07_msgservice {

struct ResponseMetaDto {
  bool accepted{false};
  std::string code;
  std::string message;
};

struct RegisterTopicResponseDto {
  ResponseMetaDto meta;
  bool registered{false};
  std::string traceId;
  std::string topic;
};

struct RegisterSubscriptionResponseDto {
  ResponseMetaDto meta;
  bool registered{false};
  bool bindingEventPublished{false};
  bool auditRecorded{false};
  std::string traceId;
  std::string subscriptionId;
  std::string auditRecordId;
  std::string bindingEventTopic;
  std::string subscriptionStatus;
};

struct RecordDeliveryResponseDto {
  ResponseMetaDto meta;
  std::string traceId;
  std::string receiptId;
  std::string topic;
  std::string subscriberEndpointId;
  std::string deliveryStatus;
  std::string errorCode;
};

struct HandleDeliveryFailureResponseDto {
  ResponseMetaDto meta;
  std::string traceId;
  std::string scheduleId;
  std::string deadLetterId;
  std::string retryDecision;
  bool retryScheduled{false};
  bool deadLettered{false};
  std::string failureReason;
};

}  // namespace wp07_msgservice