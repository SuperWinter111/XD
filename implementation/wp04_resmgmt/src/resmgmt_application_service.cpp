#include "wp04_resmgmt/resmgmt_application_service.h"

namespace wp04_resmgmt {

ResMgmtApplicationService::ResMgmtApplicationService(ResourceRegistry& resourceRegistry,
                                                     CapabilityAggregator& capabilityAggregator,
                                                     LinkImpactEvaluator& linkImpactEvaluator,
                                                     ConflictArbitrationService& conflictArbitrationService,
                                                     ResourceSchedulingService& resourceSchedulingService,
                                                     ReservationManager& reservationManager)
    : resourceRegistry_(resourceRegistry),
      capabilityAggregator_(capabilityAggregator),
      linkImpactEvaluator_(linkImpactEvaluator),
      conflictArbitrationService_(conflictArbitrationService),
      resourceSchedulingService_(resourceSchedulingService),
      reservationManager_(reservationManager) {}

AllocationWorkflowResult ResMgmtApplicationService::process(const ResourceRegistration& resourceRegistration,
                                                            const FlightState& flightState,
                                                            const SensorState& sensorState,
                                                            const WeaponState& weaponState,
                                                            const AllocationRequest& allocationRequest,
                                                            const LinkQualitySnapshot& linkQualitySnapshot,
                                                            const DegradationAlert* degradationAlert) const {
  AllocationWorkflowResult result;
  result.resourceDescriptor = resourceRegistry_.registerResource(resourceRegistration, flightState);
  result.capabilityProfile = capabilityAggregator_.aggregate(result.resourceDescriptor, sensorState, weaponState);
  const auto availabilityImpact = linkImpactEvaluator_.evaluate(linkQualitySnapshot, degradationAlert);
  result.resourceStateSnapshot = resourceRegistry_.buildStateSnapshot(result.resourceDescriptor, availabilityImpact);
  const auto arbitrationReason = conflictArbitrationService_.explain(
      allocationRequest.requestedUnitCount, result.resourceStateSnapshot.available ? 1U : 0U, allocationRequest.reserveOnly);
  result.allocationDecision = resourceSchedulingService_.schedule(
      allocationRequest, result.resourceDescriptor, result.capabilityProfile, availabilityImpact, arbitrationReason);
  result.reservationTicket = reservationManager_.build(result.allocationDecision);
  return result;
}

}  // namespace wp04_resmgmt