#include <cassert>

#include "wp07_msgservice/delivery_tracker.h"
#include "wp07_msgservice/msgservice_command_handler.h"

using namespace wp07_msgservice;

int main() {
  TopicRegistry topicRegistry;
  SubscriptionRegistry subscriptionRegistry;
  SubscriptionGovernanceService subscriptionGovernanceService;
  DeliveryTracker deliveryTracker;
  RetryAndDeadLetterService retryAndDeadLetterService(RetryPolicy{3, 1000, 8000, true});
  InMemorySubscriptionAuditRepository subscriptionAuditRepository;
  InMemoryRetryScheduleRepository retryScheduleRepository;
  MsgServiceCommandMapper commandMapper;
  MsgServiceResponseMapper responseMapper;

  MsgServiceApplicationService applicationService(topicRegistry,
                                                  subscriptionRegistry,
                                                  subscriptionGovernanceService,
                                                  deliveryTracker,
                                                  retryAndDeadLetterService,
                                                  subscriptionAuditRepository,
                                                  retryScheduleRepository);
  MsgServiceCommandHandler commandHandler(commandMapper, responseMapper, applicationService);

  const auto registerTopicResult = commandHandler.handle(RegisterTopicRequestDto{"bms/core/ops/msg/delivery_receipt",
                                                                                  "msg",
                                                                                  "DeliveryReceipt",
                                                                                  "reliable",
                                                                                  "active",
                                                                                  "team-msgservice",
                                                                                  "proto://bms/schema/message.proto#DeliveryReceipt",
                                                                                  604800000,
                                                                                  "trace-300"});
  assert(registerTopicResult.has_value());
  assert(*registerTopicResult);

  const auto registerSubscriptionResult = commandHandler.handle(RegisterSubscriptionRequestDto{
      "sub-301", "bms/core/ops/msg/delivery_receipt", "monitorlog", "success", "", "trace-301", 1711183000000});
  assert(registerSubscriptionResult.has_value());
  assert(registerSubscriptionResult->registered);

  const auto recordDeliveryResult = commandHandler.handle(RecordDeliveryRequestDto{"trace-302",
                                                                                    "bms/core/ops/msg/delivery_receipt",
                                                                                    "DeliveryReceipt",
                                                                                    "formal08.v1",
                                                                                    "monitorlog",
                                                                                    "succeeded",
                                                                                    "none",
                                                                                    1711183010000});
  assert(recordDeliveryResult.has_value());
  assert(recordDeliveryResult->status == DeliveryStatus::kSucceeded);

  const auto failureResult = commandHandler.handle(HandleDeliveryFailureRequestDto{"trace-303",
                                                                                    "bms/core/ops/msg/delivery_receipt",
                                                                                    "DeliveryReceipt",
                                                                                    "formal08.v1",
                                                                                    "target_endpoint_unreachable",
                                                                                    1,
                                                                                    1711183020000,
                                                                                    1711183020000});
  assert(failureResult.has_value());
  assert(failureResult->retryScheduleEntry.has_value());

  const auto invalidResult = commandHandler.handle(RegisterTopicRequestDto{"bms/core/ops/msg/delivery_receipt",
                                                                           "msg",
                                                                           "DeliveryReceipt",
                                                                           "reliable",
                                                                           "archived",
                                                                           "team-msgservice",
                                                                           "proto://bms/schema/message.proto#DeliveryReceipt",
                                         604800000,
                                         "trace-invalid-300"});
  assert(!invalidResult.has_value());

  const auto registerTopicResponse = commandHandler.handleRequest(RegisterTopicRequestDto{"bms/core/ops/msg/topic_defined",
                                                                                          "msg",
                                                                                          "TopicDefinition",
                                                                                          "reliable",
                                                                                          "active",
                                                                                          "team-msgservice",
                                                                                          "proto://bms/schema/message.proto#TopicDefinition",
                                                604800000,
                                                "trace-307"});
  assert(registerTopicResponse.meta.accepted);
  assert(registerTopicResponse.meta.code == "ok");
  assert(registerTopicResponse.registered);
    assert(registerTopicResponse.traceId == "trace-307");

  const auto invalidTopicResponse = commandHandler.handleRequest(RegisterTopicRequestDto{"bms/core/ops/msg/topic_defined",
                                                                                         "msg",
                                                                                         "TopicDefinition",
                                                                                         "reliable",
                                                                                         "invalid_state",
                                                                                         "team-msgservice",
                                                                                         "proto://bms/schema/message.proto#TopicDefinition",
                                               604800000,
                                               "trace-308"});
  assert(!invalidTopicResponse.meta.accepted);
  assert(invalidTopicResponse.meta.code == "invalid_argument");
    assert(invalidTopicResponse.traceId == "trace-308");

  const auto subscriptionResponse = commandHandler.handleRequest(RegisterSubscriptionRequestDto{
      "sub-302", "bms/core/ops/msg/delivery_receipt", "monitorlog", "success", "", "trace-304", 1711183040000});
  assert(subscriptionResponse.meta.accepted);
  assert(subscriptionResponse.bindingEventPublished);
  assert(subscriptionResponse.auditRecorded);
    assert(subscriptionResponse.traceId == "trace-304");
    assert(subscriptionResponse.subscriptionId == "sub-302");
    assert(subscriptionResponse.bindingEventTopic == "bms/core/ops/msg/subscription_bound");
  assert(subscriptionResponse.subscriptionStatus == "success");

  const auto deliveryResponse = commandHandler.handleRequest(RecordDeliveryRequestDto{"trace-305",
                                                                                       "bms/core/ops/msg/delivery_receipt",
                                                                                       "DeliveryReceipt",
                                                                                       "formal08.v1",
                                                                                       "monitorlog",
                                                                                       "failed",
                                                                                       "timeout",
                                                                                       1711183050000});
  assert(deliveryResponse.meta.accepted);
  assert(deliveryResponse.traceId == "trace-305");
  assert(deliveryResponse.deliveryStatus == "failed");
  assert(deliveryResponse.errorCode == "timeout");

  const auto failureResponse = commandHandler.handleRequest(HandleDeliveryFailureRequestDto{"trace-306",
                                                                                             "bms/core/ops/msg/delivery_receipt",
                                                                                             "DeliveryReceipt",
                                                                                             "formal08.v1",
                                                                                             "target_endpoint_unreachable",
                                                                                             1,
                                                                                             1711183060000,
                                                                                             1711183060000});
  assert(failureResponse.meta.accepted);
  assert(failureResponse.traceId == "trace-306");
  assert(failureResponse.retryScheduled);
  assert(!failureResponse.deadLettered);
  assert(failureResponse.retryDecision == "retry_scheduled");

  return 0;
}