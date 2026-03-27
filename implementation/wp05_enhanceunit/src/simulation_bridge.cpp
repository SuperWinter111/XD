#include "wp05_enhanceunit/simulation_bridge.h"

namespace wp05_enhanceunit {

MissionProgress SimulationBridge::buildSimulatedMissionProgress(const ClockTick& clockTick,
                                                               const SimFlightState& simFlightState) const {
  MissionProgress missionProgress;
  missionProgress.traceId = clockTick.traceId.empty() ? simFlightState.traceId : clockTick.traceId;
  missionProgress.missionId = simFlightState.missionId;
  missionProgress.platformId = simFlightState.platformId;
  missionProgress.progressState = simFlightState.phase;
  missionProgress.progressPct = 50;
  return missionProgress;
}

}  // namespace wp05_enhanceunit