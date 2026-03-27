#include <cassert>

#include "test_support.h"
#include "wp07_msgservice/subscription_governance_service.h"
#include "wp07_msgservice/subscription_registry.h"

using namespace wp07_msgservice;

int main() {
  SubscriptionRegistry subscriptionRegistry;
  SubscriptionGovernanceService governanceService;

  assert(subscriptionRegistry.registerSubscription(test_support::makeSuccessBinding()));
  assert(subscriptionRegistry.registerSubscription(test_support::makeRejectedBinding()));

  const auto allBindings = subscriptionRegistry.findAllByTopic("bms/core/ops/msg/delivery_receipt");
  assert(allBindings.size() == 2);
  assert(governanceService.isRouteEligible(allBindings.front()));
  assert(!governanceService.isRouteEligible(allBindings.back()));

  const auto bindingEvent =
      governanceService.buildBindingEventEnvelope(allBindings.back(), "trace-subscription-002");
  assert(bindingEvent.has_value());
  assert(bindingEvent->topic == "bms/core/ops/msg/subscription_bound");

  return 0;
}