#pragma once

#include <optional>
#include <string>

#include "wp07_msgservice/message_types.h"

namespace wp07_msgservice {

class SubscriptionGovernanceService {
 public:
  static constexpr const char* kSubscriptionBoundTopic = "bms/core/ops/msg/subscription_bound";

  bool shouldPublishBindingEvent(const SubscriptionBinding& binding) const;
  bool isRouteEligible(const SubscriptionBinding& binding) const;
  std::optional<MessageEnvelope> buildBindingEventEnvelope(const SubscriptionBinding& binding,
                                                           const std::string& traceId) const;
};

}  // namespace wp07_msgservice