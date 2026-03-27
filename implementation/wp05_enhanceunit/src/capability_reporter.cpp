#include "wp05_enhanceunit/capability_reporter.h"

namespace wp05_enhanceunit {

ResourceRegistration CapabilityReporter::buildRegistration(const std::string& traceId,
                                                          const PlatformState& platformState,
                                                          const PayloadState& payloadState,
                                                          const WeaponState& weaponState) const {
  ResourceRegistration registration;
  registration.traceId = traceId;
  registration.platformId = platformState.platformId;
  registration.platformType = platformState.platformType;
  registration.capabilitySource = payloadState.payloadType + "+weapon:" + weaponState.weaponId;
  return registration;
}

}  // namespace wp05_enhanceunit