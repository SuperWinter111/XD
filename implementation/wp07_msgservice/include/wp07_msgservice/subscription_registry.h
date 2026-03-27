#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "wp07_msgservice/message_types.h"

namespace wp07_msgservice {

class SubscriptionRegistry {
 public:
  bool registerSubscription(const SubscriptionBinding& binding);
  std::vector<SubscriptionBinding> findByTopic(const std::string& topic) const;
  std::vector<SubscriptionBinding> findAllByTopic(const std::string& topic) const;

 private:
  std::unordered_map<std::string, std::vector<SubscriptionBinding>> subscriptionsByTopic_;
};

}  // namespace wp07_msgservice
