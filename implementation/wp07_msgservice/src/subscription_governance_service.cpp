#include "wp07_msgservice/subscription_governance_service.h"

namespace wp07_msgservice {

bool SubscriptionGovernanceService::shouldPublishBindingEvent(const SubscriptionBinding& binding) const {
  return !binding.subscriptionId.empty() && !binding.topic.empty() && !binding.subscriberEndpointId.empty();
}

bool SubscriptionGovernanceService::isRouteEligible(const SubscriptionBinding& binding) const {
  return binding.status == SubscriptionBindingStatus::kSuccess;
}

std::optional<MessageEnvelope> SubscriptionGovernanceService::buildBindingEventEnvelope(
    const SubscriptionBinding& binding,
    const std::string& traceId) const {
  if (!shouldPublishBindingEvent(binding) || traceId.empty()) {
    return std::nullopt;
  }

  MessageEnvelope envelope;
  envelope.traceId = traceId;
  envelope.topic = kSubscriptionBoundTopic;
  envelope.payloadType = "SubscriptionBinding";
  envelope.schemaVersion = "formal08.v1";
  return envelope;
}

}  // namespace wp07_msgservice