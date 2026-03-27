#pragma once

#include <vector>

#include "wp07_msgservice/message_types.h"
#include "wp07_msgservice/subscription_registry.h"
#include "wp07_msgservice/topic_registry.h"

namespace wp07_msgservice {

class EnvelopeRouter {
 public:
  EnvelopeRouter(const TopicRegistry& topicRegistry,
                 const SubscriptionRegistry& subscriptionRegistry);

  std::vector<SubscriptionBinding> route(const MessageEnvelope& envelope) const;

 private:
  const TopicRegistry& topicRegistry_;
  const SubscriptionRegistry& subscriptionRegistry_;
};

}  // namespace wp07_msgservice
