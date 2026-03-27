#include <cassert>

#include "test_support.h"
#include "wp07_msgservice/topic_registry.h"

using namespace wp07_msgservice;

int main() {
  TopicRegistry topicRegistry;

  const bool registered = topicRegistry.registerTopic(test_support::makeDeliveryReceiptTopic());
  assert(registered);
  assert(topicRegistry.size() == 1);

  const auto found = topicRegistry.findTopic("bms/core/ops/msg/delivery_receipt");
  assert(found.has_value());
  assert(found->ownerTeam == "team-msgservice");
  assert(found->retentionMs == 604800000);

  return 0;
}