#pragma once

#include <optional>

#include "wp04_resmgmt/message_types.h"

namespace wp04_resmgmt {

class ReservationManager {
 public:
  std::optional<ReservationTicket> build(const AllocationDecision& allocationDecision) const;
};

}  // namespace wp04_resmgmt