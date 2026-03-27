#pragma once

#include <optional>

#include "wp04_resmgmt/capability_aggregator.h"
#include "wp04_resmgmt/conflict_arbitration_service.h"
#include "wp04_resmgmt/link_impact_evaluator.h"
#include "wp04_resmgmt/reservation_manager.h"
#include "wp04_resmgmt/resource_registry.h"
#include "wp04_resmgmt/resource_scheduling_service.h"

namespace wp04_resmgmt {

struct AllocationWorkflowResult {
  ResourceDescriptor resourceDescriptor;
  CapabilityProfile capabilityProfile;
  ResourceStateSnapshot resourceStateSnapshot;
  AllocationDecision allocationDecision;
  std::optional<ReservationTicket> reservationTicket;
};

class ResMgmtApplicationService {
 public:
  ResMgmtApplicationService(ResourceRegistry& resourceRegistry,
                            CapabilityAggregator& capabilityAggregator,
                            LinkImpactEvaluator& linkImpactEvaluator,
                            ConflictArbitrationService& conflictArbitrationService,
                            ResourceSchedulingService& resourceSchedulingService,
                            ReservationManager& reservationManager);

  AllocationWorkflowResult process(const ResourceRegistration& resourceRegistration,
                                   const FlightState& flightState,
                                   const SensorState& sensorState,
                                   const WeaponState& weaponState,
                                   const AllocationRequest& allocationRequest,
                                   const LinkQualitySnapshot& linkQualitySnapshot,
                                   const DegradationAlert* degradationAlert) const;

 private:
  ResourceRegistry& resourceRegistry_;
  CapabilityAggregator& capabilityAggregator_;
  LinkImpactEvaluator& linkImpactEvaluator_;
  ConflictArbitrationService& conflictArbitrationService_;
  ResourceSchedulingService& resourceSchedulingService_;
  ReservationManager& reservationManager_;
};

}  // namespace wp04_resmgmt