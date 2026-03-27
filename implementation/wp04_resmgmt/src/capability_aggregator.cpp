#include "wp04_resmgmt/capability_aggregator.h"

namespace wp04_resmgmt {

CapabilityProfile CapabilityAggregator::aggregate(const ResourceDescriptor& resourceDescriptor,
                                                  const SensorState& sensorState,
                                                  const WeaponState& weaponState) const {
  CapabilityProfile capabilityProfile;
  capabilityProfile.traceId = resourceDescriptor.traceId;
  capabilityProfile.platformId = resourceDescriptor.platformId;
  if (sensorState.ready) {
    capabilityProfile.capabilities.push_back(sensorState.sensorType);
  }
  if (weaponState.ready) {
    capabilityProfile.capabilities.push_back("weapon:" + weaponState.weaponId);
  }
  return capabilityProfile;
}

}  // namespace wp04_resmgmt