#pragma once

#include "wp05_enhanceunit/message_types.h"

namespace wp05_enhanceunit {

class CapabilityReporter {
 public:
  ResourceRegistration buildRegistration(const std::string& traceId,
                                         const PlatformState& platformState,
                                         const PayloadState& payloadState,
                                         const WeaponState& weaponState) const;
};

}  // namespace wp05_enhanceunit