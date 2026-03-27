#include <cassert>
#include <string>

#include "test_support.h"
#include "wp07_msgservice/delivery_tracker.h"
#include "wp07_msgservice/retry_and_dead_letter_service.h"
#include "wp07_msgservice/retry_schedule_repository.h"

using namespace wp07_msgservice;

int main() {
  DeliveryTracker tracker;
  RetryAndDeadLetterService deadLetterService(RetryPolicy{3, 1000, 8000, true});
  InMemoryRetryScheduleRepository retryScheduleRepository;

  const auto receipt = tracker.recordDelivery(test_support::makeDeliveryEnvelope("trace-001"),
                                              test_support::makeSuccessBinding(),
                                              DeliveryStatus::kSucceeded,
                                              DeliveryErrorCode::kNone,
                                              1711180800000);
  assert(receipt.status == DeliveryStatus::kSucceeded);
  assert(receipt.errorCode == DeliveryErrorCode::kNone);

  const auto failedReceipt = tracker.recordDelivery(test_support::makeDeliveryEnvelope("trace-003"),
                                                    test_support::makeSuccessBinding(),
                                                    DeliveryStatus::kFailed,
                                                    DeliveryErrorCode::kTimeout,
                                                    1711180830000);
  assert(failedReceipt.status == DeliveryStatus::kFailed);
  assert(std::string(toString(failedReceipt.errorCode)) == "timeout");

  const auto retryPlan = deadLetterService.planRetry(FailureReason::kTargetEndpointUnreachable, 1);
  assert(retryPlan.decision == RetryDecision::kRetryScheduled);

  const auto retrySchedule = retryScheduleRepository.saveRetrySchedule(
      test_support::makeDeliveryEnvelope("trace-004"), retryPlan, 1711180840000);
  assert(retrySchedule.has_value());
  assert(retrySchedule->nextAttemptAtUtcMs == 1711180841000);

  const auto deadLetter = deadLetterService.evaluateFailure(
      MessageEnvelope{"trace-002", "bms/core/ops/msg/mission_progress", "MissionProgress", "formal08.v1"},
      FailureReason::kTargetEndpointUnreachable,
      3,
      1711180860000);
  assert(deadLetter.has_value());
  assert(deadLetter->retryCount == 3);

  return 0;
}