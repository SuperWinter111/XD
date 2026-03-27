#pragma once

#include <cstdint>
#include <optional>
#include <vector>

#include "wp07_msgservice/delivery_tracker.h"
#include "wp07_msgservice/envelope_router.h"
#include "wp07_msgservice/msgservice_use_cases.h"
#include "wp07_msgservice/retry_and_dead_letter_service.h"
#include "wp07_msgservice/retry_schedule_repository.h"
#include "wp07_msgservice/subscription_audit_repository.h"
#include "wp07_msgservice/subscription_governance_service.h"
#include "wp07_msgservice/subscription_registry.h"
#include "wp07_msgservice/topic_registry.h"

namespace wp07_msgservice {

struct RegisterSubscriptionResult {
  bool registered{false};
  std::optional<MessageEnvelope> bindingEvent;
  std::optional<SubscriptionBindingAuditRecord> auditRecord;
};

struct DeliveryFailureHandlingResult {
  RetryPlan retryPlan;
  std::optional<RetryScheduleEntry> retryScheduleEntry;
  std::optional<DeadLetterRecord> deadLetterRecord;
};

class MsgServiceApplicationService {
 public:
  MsgServiceApplicationService(TopicRegistry& topicRegistry,
                               SubscriptionRegistry& subscriptionRegistry,
                               SubscriptionGovernanceService& subscriptionGovernanceService,
                               DeliveryTracker& deliveryTracker,
                               RetryAndDeadLetterService& retryAndDeadLetterService,
                               SubscriptionAuditRepository& subscriptionAuditRepository,
                               RetryScheduleRepository& retryScheduleRepository);

  bool registerTopic(const RegisterTopicCommand& command) const;
  bool registerTopic(const TopicDefinition& topicDefinition) const;

  RegisterSubscriptionResult registerSubscription(const RegisterSubscriptionCommand& command) const;
  RegisterSubscriptionResult registerSubscription(const SubscriptionBinding& binding,
                                                  const std::string& traceId,
                                                  std::int64_t recordedAtUtcMs) const;

  std::vector<SubscriptionBinding> routeEnvelope(const MessageEnvelope& envelope) const;

  DeliveryReceipt recordDelivery(const RecordDeliveryCommand& command) const;
  DeliveryReceipt recordDelivery(const MessageEnvelope& envelope,
                                 const SubscriptionBinding& subscriber,
                                 DeliveryStatus status,
                                 DeliveryErrorCode errorCode,
                                 std::int64_t deliveredAtUtcMs) const;

  DeliveryFailureHandlingResult handleDeliveryFailure(const HandleDeliveryFailureCommand& command) const;
  DeliveryFailureHandlingResult handleDeliveryFailure(const MessageEnvelope& envelope,
                                                      FailureReason failureReason,
                                                      std::uint32_t retryCount,
                                                      std::int64_t scheduledAtUtcMs,
                                                      std::int64_t lastAttemptUtcMs) const;

 private:
  TopicRegistry& topicRegistry_;
  SubscriptionRegistry& subscriptionRegistry_;
  SubscriptionGovernanceService& subscriptionGovernanceService_;
  DeliveryTracker& deliveryTracker_;
  RetryAndDeadLetterService& retryAndDeadLetterService_;
  SubscriptionAuditRepository& subscriptionAuditRepository_;
  RetryScheduleRepository& retryScheduleRepository_;
};

}  // namespace wp07_msgservice