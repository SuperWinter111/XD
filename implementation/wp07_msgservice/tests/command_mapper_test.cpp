#include <cassert>

#include "wp07_msgservice/msgservice_command_mapper.h"

using namespace wp07_msgservice;

int main() {
  MsgServiceCommandMapper mapper;

  const auto topicCommand = mapper.map(RegisterTopicRequestDto{"bms/core/ops/msg/delivery_receipt",
                                                               "msg",
                                                               "DeliveryReceipt",
                                                               "reliable",
                                                               "active",
                                                               "team-msgservice",
                                                               "proto://bms/schema/message.proto#DeliveryReceipt",
                                                               604800000,
                                                               "trace-topic-201"});
  assert(topicCommand.has_value());
  assert(topicCommand->topicDefinition.topicState == TopicState::kActive);

  const auto invalidTopicCommand = mapper.map(RegisterTopicRequestDto{"bms/core/ops/msg/delivery_receipt",
                                                                      "msg",
                                                                      "DeliveryReceipt",
                                                                      "reliable",
                                                                      "archived",
                                                                      "team-msgservice",
                                                                      "proto://bms/schema/message.proto#DeliveryReceipt",
                                                                      604800000,
                                                                      "trace-topic-202"});
  assert(!invalidTopicCommand.has_value());

  const auto subscriptionCommand = mapper.map(RegisterSubscriptionRequestDto{
      "sub-001", "bms/core/ops/msg/delivery_receipt", "monitorlog", "success", "", "trace-201", 1711182000000});
  assert(subscriptionCommand.has_value());
  assert(subscriptionCommand->binding.status == SubscriptionBindingStatus::kSuccess);

  const auto deliveryCommand = mapper.map(RecordDeliveryRequestDto{"trace-202",
                                                                   "bms/core/ops/msg/delivery_receipt",
                                                                   "DeliveryReceipt",
                                                                   "formal08.v1",
                                                                   "monitorlog",
                                                                   "failed",
                                                                   "timeout",
                                                                   1711182010000});
  assert(deliveryCommand.has_value());
  assert(deliveryCommand->status == DeliveryStatus::kFailed);
  assert(deliveryCommand->errorCode == DeliveryErrorCode::kTimeout);

  const auto failureCommand = mapper.map(HandleDeliveryFailureRequestDto{"trace-203",
                                                                         "bms/core/ops/msg/delivery_receipt",
                                                                         "DeliveryReceipt",
                                                                         "formal08.v1",
                                                                         "target_endpoint_unreachable",
                                                                         2,
                                                                         1711182020000,
                                                                         1711182020000});
  assert(failureCommand.has_value());
  assert(failureCommand->failureReason == FailureReason::kTargetEndpointUnreachable);

  const auto invalidFailureCommand = mapper.map(HandleDeliveryFailureRequestDto{"trace-204",
                                                                                "bms/core/ops/msg/delivery_receipt",
                                                                                "DeliveryReceipt",
                                                                                "formal08.v1",
                                                                                "network_jitter",
                                                                                2,
                                                                                1711182030000,
                                                                                1711182030000});
  assert(!invalidFailureCommand.has_value());

  return 0;
}