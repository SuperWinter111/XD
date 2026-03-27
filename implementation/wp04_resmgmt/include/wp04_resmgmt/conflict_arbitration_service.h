#pragma once

#include "wp04_resmgmt/message_types.h"

namespace wp04_resmgmt {

class ConflictArbitrationService {
 public:
  std::string explain(std::uint32_t requestedUnitCount, std::uint32_t availableUnitCount, bool reserveOnly) const;
};

}  // namespace wp04_resmgmt