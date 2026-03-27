#include "wp07_msgservice/subscription_registry.h"

namespace wp07_msgservice {

bool SubscriptionRegistry::registerSubscription(const SubscriptionBinding& binding) {
  if (binding.subscriptionId.empty() || binding.topic.empty() || binding.subscriberEndpointId.empty()) {
    return false;
  }

  subscriptionsByTopic_[binding.topic].push_back(binding);
  return true;
}

std::vector<SubscriptionBinding> SubscriptionRegistry::findByTopic(const std::string& topic) const {
  const auto allBindings = findAllByTopic(topic);
  std::vector<SubscriptionBinding> activeBindings;
  activeBindings.reserve(allBindings.size());
  for (const auto& binding : allBindings) {
    if (binding.status == SubscriptionBindingStatus::kSuccess) {
      activeBindings.push_back(binding);
    }
  }

  return activeBindings;
}

std::vector<SubscriptionBinding> SubscriptionRegistry::findAllByTopic(const std::string& topic) const {
  const auto it = subscriptionsByTopic_.find(topic);
  if (it == subscriptionsByTopic_.end()) {
    return {};
  }

  return it->second;
}

}  // namespace wp07_msgservice
