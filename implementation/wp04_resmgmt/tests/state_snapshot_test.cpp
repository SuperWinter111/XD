#include <cassert>

#include "test_support.h"
#include "wp04_resmgmt/resmgmt_application_service.h"

using namespace wp04_resmgmt;

int main() {
  ResourceRegistry resourceRegistry;
  CapabilityAggregator capabilityAggregator;
  LinkImpactEvaluator linkImpactEvaluator;
  ConflictArbitrationService conflictArbitrationService;
  ResourceSchedulingService resourceSchedulingService;
  ReservationManager reservationManager;
  ResMgmtApplicationService applicationService(resourceRegistry,
                                               capabilityAggregator,
                                               linkImpactEvaluator,
                                               conflictArbitrationService,
                                               resourceSchedulingService,
                                               reservationManager);

  const auto result = applicationService.process(test_support::makeRegistration(),
                                                 test_support::makeFlightState(),
                                                 test_support::makeSensorState(),
                                                 test_support::makeWeaponState(),
                                                 test_support::makeAllocationRequest(),
                                                 test_support::makeHealthyLink(),
                                                 nullptr);
  assert(result.resourceStateSnapshot.available);
  assert(result.capabilityProfile.capabilities.size() == 2);
  return 0;
}