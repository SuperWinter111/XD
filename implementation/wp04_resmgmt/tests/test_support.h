#pragma once

#include "wp04_resmgmt/message_types.h"

namespace wp04_resmgmt::test_support {

inline ResourceRegistration makeRegistration() {
  return ResourceRegistration{"trace-res-001", "uav-001", "uav", "eo_sensor+weapon:agt-01"};
}

inline FlightState makeFlightState() {
  return FlightState{"uav-001", true, "ON_STATION"};
}

inline SensorState makeSensorState() {
  return SensorState{"uav-001", "sensor-001", "eo_sensor", true};
}

inline WeaponState makeWeaponState() {
  return WeaponState{"uav-001", "weapon-001", true};
}

inline LinkQualitySnapshot makeHealthyLink() {
  return LinkQualitySnapshot{"trace-res-001", "link-001", "uav-001", "cmd-001", 88};
}

inline DegradationAlert makeDegradationAlert() {
  return DegradationAlert{"trace-res-001", "link-001", "quality_score<60", "uav-001->cmd-001", 1711184000000};
}

inline AllocationRequest makeAllocationRequest() {
  return AllocationRequest{"trace-res-001", "request-001", "mission-001", 1, false};
}

inline AllocationRequest makePartialRequest() {
  return AllocationRequest{"trace-res-002", "request-002", "mission-002", 2, false};
}

inline AllocationRequest makeReserveOnlyRequest() {
  return AllocationRequest{"trace-res-003", "request-003", "mission-003", 1, true};
}

}  // namespace wp04_resmgmt::test_support