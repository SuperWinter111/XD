#include <cassert>

#include "test_support.h"
#include "wp07_msgservice/delivery_tracker.h"
#include "wp07_msgservice/msgservice_application_service.h"

using namespace wp07_msgservice;

int main() {
  TopicRegistry topicRegistry;
  SubscriptionRegistry subscriptionRegistry;
  SubscriptionGovernanceService subscriptionGovernanceService;
  DeliveryTracker deliveryTracker;
  RetryAndDeadLetterService retryAndDeadLetterService(RetryPolicy{3, 1000, 8000, true});
  InMemorySubscriptionAuditRepository subscriptionAuditRepository;
  InMemoryRetryScheduleRepository retryScheduleRepository;

  MsgServiceApplicationService applicationService(topicRegistry,
                                                  subscriptionRegistry,
                                                  subscriptionGovernanceService,
                                                  deliveryTracker,
                                                  retryAndDeadLetterService,
                                                  subscriptionAuditRepository,
                                                  retryScheduleRepository);

  assert(applicationService.registerTopic(RegisterTopicCommand{test_support::makeDeliveryReceiptTopic()}));

  const auto registerResult = applicationService.registerSubscription(RegisterSubscriptionCommand{
      test_support::makeRejectedBinding(), "trace-subscription-002", 1711180700000});
  assert(registerResult.registered);
  assert(registerResult.bindingEvent.has_value());
  assert(registerResult.auditRecord.has_value());

  const auto acceptedResult = applicationService.registerSubscription(RegisterSubscriptionCommand{
      test_support::makeSuccessBinding(), "trace-subscription-001", 1711180701000});
  assert(acceptedResult.registered);

  const auto routedSubscribers = applicationService.routeEnvelope(test_support::makeDeliveryEnvelope("trace-010"));
  assert(routedSubscribers.size() == 1);
  assert(routedSubscribers.front().subscriberEndpointId == "monitorlog");

  const auto deliveryReceipt = applicationService.recordDelivery(RecordDeliveryCommand{
      test_support::makeDeliveryEnvelope("trace-010"),
      routedSubscribers.front(),
      DeliveryStatus::kSucceeded,
      DeliveryErrorCode::kNone,
      1711180900000});
  assert(deliveryReceipt.status == DeliveryStatus::kSucceeded);

  const auto failureResult = applicationService.handleDeliveryFailure(HandleDeliveryFailureCommand{
      test_support::makeDeliveryEnvelope("trace-011"),
      FailureReason::kTargetEndpointUnreachable,
      1,
      1711180910000,
      1711180910000});
  assert(failureResult.retryPlan.decision == RetryDecision::kRetryScheduled);
  assert(failureResult.retryScheduleEntry.has_value());
  assert(!failureResult.deadLetterRecord.has_value());

  const auto exhaustedFailureResult = applicationService.handleDeliveryFailure(HandleDeliveryFailureCommand{
      test_support::makeDeliveryEnvelope("trace-012"),
      FailureReason::kTargetEndpointUnreachable,
      3,
      1711180920000,
      1711180920000});
  assert(exhaustedFailureResult.deadLetterRecord.has_value());

  return 0;
}