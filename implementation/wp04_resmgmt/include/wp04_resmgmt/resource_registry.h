#pragma once

#include "wp04_resmgmt/message_types.h"

namespace wp04_resmgmt {

class ResourceRegistry {
 public:
  ResourceDescriptor registerResource(const ResourceRegistration& resourceRegistration,
                                      const FlightState& flightState) const;
  ResourceStateSnapshot buildStateSnapshot(const ResourceDescriptor& resourceDescriptor,
                                           const AvailabilityImpact& availabilityImpact) const;
};

}  // namespace wp04_resmgmt