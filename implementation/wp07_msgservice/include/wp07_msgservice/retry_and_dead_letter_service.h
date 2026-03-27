#pragma once

#include <optional>
#include <string>

#include "wp07_msgservice/message_types.h"

namespace wp07_msgservice {

class RetryAndDeadLetterService {
 public:
  explicit RetryAndDeadLetterService(RetryPolicy retryPolicy);

  RetryPlan planRetry(FailureReason failureReason, std::uint32_t retryCount) const;

  std::optional<DeadLetterRecord> evaluateFailure(const MessageEnvelope& envelope,
                                                  FailureReason failureReason,
                                                  std::uint32_t retryCount,
                                                  std::int64_t lastAttemptUtcMs) const;

 private:
  RetryPolicy retryPolicy_;
};

}  // namespace wp07_msgservice
