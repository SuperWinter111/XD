#pragma once

#include "wp04_resmgmt/message_types.h"

namespace wp04_resmgmt {

class ResourceSchedulingService {
 public:
  AllocationDecision schedule(const AllocationRequest& allocationRequest,
                              const ResourceDescriptor& resourceDescriptor,
                              const CapabilityProfile& capabilityProfile,
                              const AvailabilityImpact& availabilityImpact,
                              const std::string& arbitrationReason) const;
};

}  // namespace wp04_resmgmt