#include "wp07_msgservice/envelope_router.h"

namespace wp07_msgservice {

EnvelopeRouter::EnvelopeRouter(const TopicRegistry& topicRegistry,
                               const SubscriptionRegistry& subscriptionRegistry)
    : topicRegistry_(topicRegistry), subscriptionRegistry_(subscriptionRegistry) {}

std::vector<SubscriptionBinding> EnvelopeRouter::route(const MessageEnvelope& envelope) const {
  if (!topicRegistry_.findTopic(envelope.topic).has_value()) {
    return {};
  }

  return subscriptionRegistry_.findByTopic(envelope.topic);
}

}  // namespace wp07_msgservice
