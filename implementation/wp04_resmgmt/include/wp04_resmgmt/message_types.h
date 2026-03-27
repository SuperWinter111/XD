#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace wp04_resmgmt {

struct ResourceRegistration {
  std::string traceId;
  std::string platformId;
  std::string platformType;
  std::string capabilitySource;
};

struct FlightState {
  std::string platformId;
  bool online{false};
  std::string flightPhase;
};

struct SensorState {
  std::string platformId;
  std::string sensorId;
  std::string sensorType;
  bool ready{false};
};

struct WeaponState {
  std::string platformId;
  std::string weaponId;
  bool ready{false};
};

struct LinkQualitySnapshot {
  std::string traceId;
  std::string linkId;
  std::string sourceNodeId;
  std::string targetNodeId;
  std::uint32_t qualityScore{0};
};

struct DegradationAlert {
  std::string traceId;
  std::string linkId;
  std::string triggerThreshold;
  std::string impactScope;
  std::int64_t eventAtUtcMs{0};
};

struct ResourceDescriptor {
  std::string traceId;
  std::string platformId;
  std::string platformType;
  bool online{false};
  std::string flightPhase;
};

struct CapabilityProfile {
  std::string traceId;
  std::string platformId;
  std::vector<std::string> capabilities;
};

struct ResourceStateSnapshot {
  std::string traceId;
  std::string platformId;
  bool available{false};
  std::string availabilityReason;
};

struct AllocationRequest {
  std::string traceId;
  std::string requestId;
  std::string missionId;
  std::uint32_t requestedUnitCount{0};
  bool reserveOnly{false};
};

struct AllocationDecision {
  std::string traceId;
  std::string requestId;
  std::string missionId;
  bool accepted{false};
  bool partiallySatisfied{false};
  bool reserveOnly{false};
  std::vector<std::string> allocatedResourceIds;
  std::vector<std::string> reservedResourceIds;
  std::string reason;
};

struct ReservationTicket {
  std::string traceId;
  std::string ticketId;
  std::string requestId;
  std::vector<std::string> reservedResourceIds;
  std::int64_t validUntilUtcMs{0};
};

struct AvailabilityImpact {
  bool linkAvailable{true};
  std::string reason;
};

}  // namespace wp04_resmgmt