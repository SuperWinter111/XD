#pragma once

#include "wp05_enhanceunit/message_types.h"

namespace wp05_enhanceunit::test_support {

inline BattlePlan makeBattlePlan() {
  return BattlePlan{"trace-enhance-001",
                    "battle-plan-001",
                    "mission-001",
                    "uav-001",
                    "flight_plan_upload",
                    {{"seg-001", "wp-alpha", "TURN"}, {"seg-002", "wp-bravo", "FLYOVER"}}};
}

inline PlatformState makePlatformState() {
  return PlatformState{"uav-001", "uav", true};
}

inline PayloadState makePayloadState() {
  return PayloadState{"uav-001", "sensor-eo-001", "eo_sensor", true};
}

inline WeaponState makeWeaponState() {
  return WeaponState{"uav-001", "weapon-agt-001", true};
}

inline ClockTick makeClockTick() {
  return ClockTick{"trace-sim-001", "tick-001", 1711182000000};
}

inline SimFlightState makeSimFlightState() {
  return SimFlightState{"trace-sim-001", "uav-sim-001", "mission-sim-001", "SIM_IN_PROGRESS"};
}

}  // namespace wp05_enhanceunit::test_support