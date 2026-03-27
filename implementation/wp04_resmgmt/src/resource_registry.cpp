#include "wp04_resmgmt/resource_registry.h"

namespace wp04_resmgmt {

ResourceDescriptor ResourceRegistry::registerResource(const ResourceRegistration& resourceRegistration,
                                                      const FlightState& flightState) const {
  ResourceDescriptor descriptor;
  descriptor.traceId = resourceRegistration.traceId;
  descriptor.platformId = resourceRegistration.platformId;
  descriptor.platformType = resourceRegistration.platformType;
  descriptor.online = flightState.online;
  descriptor.flightPhase = flightState.flightPhase;
  return descriptor;
}

ResourceStateSnapshot ResourceRegistry::buildStateSnapshot(const ResourceDescriptor& resourceDescriptor,
                                                           const AvailabilityImpact& availabilityImpact) const {
  ResourceStateSnapshot snapshot;
  snapshot.traceId = resourceDescriptor.traceId;
  snapshot.platformId = resourceDescriptor.platformId;
  snapshot.available = resourceDescriptor.online && availabilityImpact.linkAvailable;
  snapshot.availabilityReason = snapshot.available ? "resource_ready" : availabilityImpact.reason;
  return snapshot;
}

}  // namespace wp04_resmgmt