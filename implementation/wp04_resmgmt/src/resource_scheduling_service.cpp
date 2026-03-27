#include "wp04_resmgmt/resource_scheduling_service.h"

namespace wp04_resmgmt {

AllocationDecision ResourceSchedulingService::schedule(const AllocationRequest& allocationRequest,
                                                       const ResourceDescriptor& resourceDescriptor,
                                                       const CapabilityProfile& capabilityProfile,
                                                       const AvailabilityImpact& availabilityImpact,
                                                       const std::string& arbitrationReason) const {
  AllocationDecision decision;
  decision.traceId = allocationRequest.traceId;
  decision.requestId = allocationRequest.requestId;
  decision.missionId = allocationRequest.missionId;
  decision.reserveOnly = allocationRequest.reserveOnly;
  decision.reason = arbitrationReason;

  const bool hasCapability = !capabilityProfile.capabilities.empty();
  if (!resourceDescriptor.online || !availabilityImpact.linkAvailable || !hasCapability) {
    decision.accepted = false;
    decision.reason = !availabilityImpact.linkAvailable ? availabilityImpact.reason : "capability_missing";
    return decision;
  }

  decision.accepted = true;
  if (allocationRequest.reserveOnly) {
    decision.reservedResourceIds.push_back(resourceDescriptor.platformId);
    return decision;
  }

  if (allocationRequest.requestedUnitCount > 1) {
    decision.partiallySatisfied = true;
  }
  decision.allocatedResourceIds.push_back(resourceDescriptor.platformId);
  return decision;
}

}  // namespace wp04_resmgmt