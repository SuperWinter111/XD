#include "wp07_msgservice/retry_and_dead_letter_service.h"

#include <algorithm>

namespace wp07_msgservice {

namespace {

bool isRetryable(FailureReason failureReason) {
  switch (failureReason) {
    case FailureReason::kTargetEndpointUnreachable:
    case FailureReason::kSerializationError:
    case FailureReason::kTimeout:
      return true;
    case FailureReason::kUnknown:
    case FailureReason::kSchemaMismatch:
    case FailureReason::kUnauthorized:
      return false;
  }

  return false;
}

}  // namespace

RetryAndDeadLetterService::RetryAndDeadLetterService(RetryPolicy retryPolicy)
    : retryPolicy_(retryPolicy) {}

RetryPlan RetryAndDeadLetterService::planRetry(FailureReason failureReason,
                                               std::uint32_t retryCount) const {
  RetryPlan plan;
  plan.failureReason = failureReason;

  if (!isRetryable(failureReason) || retryCount >= retryPolicy_.maxRetryCount) {
    plan.decision = RetryDecision::kDeadLettered;
    plan.nextRetryCount = retryCount;
    plan.nextAttemptDelayMs = 0;
    return plan;
  }

  plan.decision = RetryDecision::kRetryScheduled;
  plan.nextRetryCount = retryCount + 1;

  std::int64_t delayMs = retryPolicy_.initialBackoffMs;
  if (retryPolicy_.exponentialBackoff && retryCount > 0) {
    delayMs *= static_cast<std::int64_t>(1) << (retryCount - 1);
  }

  plan.nextAttemptDelayMs = std::min(delayMs, retryPolicy_.maxBackoffMs);
  return plan;
}

std::optional<DeadLetterRecord> RetryAndDeadLetterService::evaluateFailure(
    const MessageEnvelope& envelope,
    FailureReason failureReason,
    std::uint32_t retryCount,
    std::int64_t lastAttemptUtcMs) const {
  const auto retryPlan = planRetry(failureReason, retryCount);
  if (retryPlan.decision != RetryDecision::kDeadLettered) {
    return std::nullopt;
  }

  DeadLetterRecord record;
  record.deadLetterId = envelope.traceId + ":dead_letter";
  record.originalTopic = envelope.topic;
  record.payloadType = envelope.payloadType;
  record.messageTraceId = envelope.traceId;
  record.failureReason = failureReason;
  record.retryCount = retryCount;
  record.lastAttemptUtcMs = lastAttemptUtcMs;
  return record;
}

}  // namespace wp07_msgservice
