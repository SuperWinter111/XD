#include "wp04_resmgmt/conflict_arbitration_service.h"

namespace wp04_resmgmt {

std::string ConflictArbitrationService::explain(std::uint32_t requestedUnitCount,
                                                std::uint32_t availableUnitCount,
                                                bool reserveOnly) const {
  if (reserveOnly) {
    return "reserve_only";
  }
  if (availableUnitCount == 0) {
    return "resource_unavailable";
  }
  if (availableUnitCount < requestedUnitCount) {
    return "partial_capacity";
  }
  return "fully_satisfied";
}

}  // namespace wp04_resmgmt