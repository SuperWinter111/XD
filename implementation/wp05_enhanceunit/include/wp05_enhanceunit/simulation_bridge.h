#pragma once

#include "wp05_enhanceunit/message_types.h"

namespace wp05_enhanceunit {

class SimulationBridge {
 public:
  MissionProgress buildSimulatedMissionProgress(const ClockTick& clockTick,
                                                const SimFlightState& simFlightState) const;
};

}  // namespace wp05_enhanceunit