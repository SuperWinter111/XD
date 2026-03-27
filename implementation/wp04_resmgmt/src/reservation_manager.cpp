#include "wp04_resmgmt/reservation_manager.h"

namespace wp04_resmgmt {

std::optional<ReservationTicket> ReservationManager::build(const AllocationDecision& allocationDecision) const {
  if (allocationDecision.reservedResourceIds.empty()) {
    return std::nullopt;
  }

  ReservationTicket ticket;
  ticket.traceId = allocationDecision.traceId;
  ticket.ticketId = allocationDecision.requestId + ":reservation";
  ticket.requestId = allocationDecision.requestId;
  ticket.reservedResourceIds = allocationDecision.reservedResourceIds;
  ticket.validUntilUtcMs = 1711185000000;
  return ticket;
}

}  // namespace wp04_resmgmt