#pragma once

#include <cstdint>
#include <string>

namespace wp07_msgservice {

enum class TopicState {
  kActive,
  kDeprecated,
};

enum class SubscriptionBindingStatus {
  kSuccess,
  kRejected,
};

enum class DeliveryStatus {
  kSucceeded,
  kFailed,
};

enum class DeliveryErrorCode {
  kNone,
  kTargetEndpointUnreachable,
  kSerializationError,
  kSchemaMismatch,
  kTimeout,
  kUnauthorized,
};

enum class FailureReason {
  kUnknown,
  kTargetEndpointUnreachable,
  kSerializationError,
  kSchemaMismatch,
  kTimeout,
  kUnauthorized,
};

inline const char* toString(TopicState state) {
  switch (state) {
    case TopicState::kActive:
      return "active";
    case TopicState::kDeprecated:
      return "deprecated";
  }

  return "unknown";
}

inline const char* toString(SubscriptionBindingStatus status) {
  switch (status) {
    case SubscriptionBindingStatus::kSuccess:
      return "success";
    case SubscriptionBindingStatus::kRejected:
      return "rejected";
  }

  return "unknown";
}

inline const char* toString(DeliveryStatus status) {
  switch (status) {
    case DeliveryStatus::kSucceeded:
      return "succeeded";
    case DeliveryStatus::kFailed:
      return "failed";
  }

  return "unknown";
}

inline const char* toString(DeliveryErrorCode errorCode) {
  switch (errorCode) {
    case DeliveryErrorCode::kNone:
      return "none";
    case DeliveryErrorCode::kTargetEndpointUnreachable:
      return "target_endpoint_unreachable";
    case DeliveryErrorCode::kSerializationError:
      return "serialization_error";
    case DeliveryErrorCode::kSchemaMismatch:
      return "schema_mismatch";
    case DeliveryErrorCode::kTimeout:
      return "timeout";
    case DeliveryErrorCode::kUnauthorized:
      return "unauthorized";
  }

  return "unknown";
}

inline const char* toString(FailureReason reason) {
  switch (reason) {
    case FailureReason::kUnknown:
      return "unknown";
    case FailureReason::kTargetEndpointUnreachable:
      return "target_endpoint_unreachable";
    case FailureReason::kSerializationError:
      return "serialization_error";
    case FailureReason::kSchemaMismatch:
      return "schema_mismatch";
    case FailureReason::kTimeout:
      return "timeout";
    case FailureReason::kUnauthorized:
      return "unauthorized";
  }

  return "unknown";
}

struct TopicDefinition {
  std::string topic;
  std::string domain;
  std::string payloadType;
  std::string qosProfile;
  TopicState topicState{TopicState::kActive};
  std::string ownerTeam;
  std::string schemaUri;
  std::int64_t retentionMs{0};
};

struct SubscriptionBinding {
  std::string subscriptionId;
  std::string topic;
  std::string subscriberEndpointId;
  SubscriptionBindingStatus status{SubscriptionBindingStatus::kSuccess};
  std::string statusReason;
};

struct MessageEnvelope {
  std::string traceId;
  std::string topic;
  std::string payloadType;
  std::string schemaVersion;
};

struct DeliveryReceipt {
  std::string receiptId;
  std::string topic;
  std::string messageTraceId;
  std::string subscriberEndpointId;
  DeliveryStatus status{DeliveryStatus::kFailed};
  DeliveryErrorCode errorCode{DeliveryErrorCode::kNone};
  std::int64_t deliveredAtUtcMs{0};
};

struct DeadLetterRecord {
  std::string deadLetterId;
  std::string originalTopic;
  std::string payloadType;
  std::string messageTraceId;
  FailureReason failureReason{FailureReason::kUnknown};
  std::uint32_t retryCount{0};
  std::int64_t lastAttemptUtcMs{0};
};

struct RetryPolicy {
  std::uint32_t maxRetryCount{3};
  std::int64_t initialBackoffMs{1000};
  std::int64_t maxBackoffMs{30000};
  bool exponentialBackoff{true};
};

enum class RetryDecision {
  kRetryScheduled,
  kDeadLettered,
};

struct RetryPlan {
  RetryDecision decision{RetryDecision::kRetryScheduled};
  std::uint32_t nextRetryCount{0};
  std::int64_t nextAttemptDelayMs{0};
  FailureReason failureReason{FailureReason::kUnknown};
};

struct SubscriptionBindingAuditRecord {
  std::string auditRecordId;
  std::string traceId;
  std::string subscriptionId;
  std::string topic;
  std::string subscriberEndpointId;
  SubscriptionBindingStatus status{SubscriptionBindingStatus::kSuccess};
  std::string statusReason;
  std::int64_t recordedAtUtcMs{0};
};

struct RetryScheduleEntry {
  std::string scheduleId;
  std::string traceId;
  std::string topic;
  std::string payloadType;
  FailureReason failureReason{FailureReason::kUnknown};
  std::uint32_t retryCount{0};
  std::int64_t scheduledAtUtcMs{0};
  std::int64_t nextAttemptAtUtcMs{0};
};

}  // namespace wp07_msgservice
