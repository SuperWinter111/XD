#pragma once

#include "wp04_resmgmt/message_types.h"

namespace wp04_resmgmt {

class CapabilityAggregator {
 public:
  CapabilityProfile aggregate(const ResourceDescriptor& resourceDescriptor,
                              const SensorState& sensorState,
                              const WeaponState& weaponState) const;
};

}  // namespace wp04_resmgmt