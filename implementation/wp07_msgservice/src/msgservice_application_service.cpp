#include "wp07_msgservice/msgservice_application_service.h"

namespace wp07_msgservice {

MsgServiceApplicationService::MsgServiceApplicationService(
    TopicRegistry& topicRegistry,
    SubscriptionRegistry& subscriptionRegistry,
    SubscriptionGovernanceService& subscriptionGovernanceService,
    DeliveryTracker& deliveryTracker,
    RetryAndDeadLetterService& retryAndDeadLetterService,
    SubscriptionAuditRepository& subscriptionAuditRepository,
    RetryScheduleRepository& retryScheduleRepository)
    : topicRegistry_(topicRegistry),
      subscriptionRegistry_(subscriptionRegistry),
      subscriptionGovernanceService_(subscriptionGovernanceService),
      deliveryTracker_(deliveryTracker),
      retryAndDeadLetterService_(retryAndDeadLetterService),
      subscriptionAuditRepository_(subscriptionAuditRepository),
      retryScheduleRepository_(retryScheduleRepository) {}

bool MsgServiceApplicationService::registerTopic(const RegisterTopicCommand& command) const {
  return registerTopic(command.topicDefinition);
}

bool MsgServiceApplicationService::registerTopic(const TopicDefinition& topicDefinition) const {
  return topicRegistry_.registerTopic(topicDefinition);
}

RegisterSubscriptionResult MsgServiceApplicationService::registerSubscription(
    const RegisterSubscriptionCommand& command) const {
  return registerSubscription(command.binding, command.traceId, command.recordedAtUtcMs);
}

RegisterSubscriptionResult MsgServiceApplicationService::registerSubscription(
    const SubscriptionBinding& binding,
    const std::string& traceId,
    std::int64_t recordedAtUtcMs) const {
  RegisterSubscriptionResult result;
  result.registered = subscriptionRegistry_.registerSubscription(binding);
  if (!result.registered) {
    return result;
  }

  if (subscriptionGovernanceService_.shouldPublishBindingEvent(binding)) {
    result.bindingEvent = subscriptionGovernanceService_.buildBindingEventEnvelope(binding, traceId);
    result.auditRecord = subscriptionAuditRepository_.saveBindingDecision(binding, traceId, recordedAtUtcMs);
  }

  return result;
}

std::vector<SubscriptionBinding> MsgServiceApplicationService::routeEnvelope(
    const MessageEnvelope& envelope) const {
  EnvelopeRouter router(topicRegistry_, subscriptionRegistry_);
  return router.route(envelope);
}

DeliveryReceipt MsgServiceApplicationService::recordDelivery(const RecordDeliveryCommand& command) const {
  return recordDelivery(command.envelope,
                        command.subscriber,
                        command.status,
                        command.errorCode,
                        command.deliveredAtUtcMs);
}

DeliveryReceipt MsgServiceApplicationService::recordDelivery(const MessageEnvelope& envelope,
                                                            const SubscriptionBinding& subscriber,
                                                            DeliveryStatus status,
                                                            DeliveryErrorCode errorCode,
                                                            std::int64_t deliveredAtUtcMs) const {
  return deliveryTracker_.recordDelivery(envelope, subscriber, status, errorCode, deliveredAtUtcMs);
}

DeliveryFailureHandlingResult MsgServiceApplicationService::handleDeliveryFailure(
    const HandleDeliveryFailureCommand& command) const {
  return handleDeliveryFailure(command.envelope,
                               command.failureReason,
                               command.retryCount,
                               command.scheduledAtUtcMs,
                               command.lastAttemptUtcMs);
}

DeliveryFailureHandlingResult MsgServiceApplicationService::handleDeliveryFailure(
    const MessageEnvelope& envelope,
    FailureReason failureReason,
    std::uint32_t retryCount,
    std::int64_t scheduledAtUtcMs,
    std::int64_t lastAttemptUtcMs) const {
  DeliveryFailureHandlingResult result;
  result.retryPlan = retryAndDeadLetterService_.planRetry(failureReason, retryCount);
  result.retryScheduleEntry =
      retryScheduleRepository_.saveRetrySchedule(envelope, result.retryPlan, scheduledAtUtcMs);
  result.deadLetterRecord = retryAndDeadLetterService_.evaluateFailure(
      envelope, failureReason, retryCount, lastAttemptUtcMs);
  return result;
}

}  // namespace wp07_msgservice