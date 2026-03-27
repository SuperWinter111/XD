#pragma once

#include <optional>

#include "wp05_enhanceunit/capability_reporter.h"
#include "wp05_enhanceunit/command_translator.h"
#include "wp05_enhanceunit/execution_feedback_bridge.h"
#include "wp05_enhanceunit/perception_bridge.h"
#include "wp05_enhanceunit/platform_command_service.h"
#include "wp05_enhanceunit/simulation_bridge.h"

namespace wp05_enhanceunit {

struct BattlePlanDispatchResult {
  PlatformCommand platformCommand;
  CommandAck commandAck;
};

class EnhanceUnitApplicationService {
 public:
  EnhanceUnitApplicationService(CommandTranslator& commandTranslator,
                                PlatformCommandService& platformCommandService,
                                ExecutionFeedbackBridge& executionFeedbackBridge,
                                CapabilityReporter& capabilityReporter,
                                SimulationBridge& simulationBridge,
                                PerceptionBridge& perceptionBridge);

  BattlePlanDispatchResult dispatchBattlePlan(const BattlePlan& battlePlan) const;
  MissionProgress buildMissionProgress(const CommandAck& commandAck,
                                       const std::string& progressState,
                                       std::uint32_t progressPct) const;
  std::optional<PlatformAlert> buildPlatformAlert(const CommandAck& commandAck) const;
  ResourceRegistration registerPlatform(const std::string& traceId,
                                        const PlatformState& platformState,
                                        const PayloadState& payloadState,
                                        const WeaponState& weaponState) const;
  RawTargetInput publishPerception(const std::string& traceId,
                                   const std::string& platformId,
                                   const std::string& sensorId,
                                   const std::string& targetTrackToken,
                                   std::int64_t reportedAtUtcMs) const;
  MissionProgress buildSimulatedMissionProgress(const ClockTick& clockTick,
                                                const SimFlightState& simFlightState) const;

 private:
  CommandTranslator& commandTranslator_;
  PlatformCommandService& platformCommandService_;
  ExecutionFeedbackBridge& executionFeedbackBridge_;
  CapabilityReporter& capabilityReporter_;
  SimulationBridge& simulationBridge_;
  PerceptionBridge& perceptionBridge_;
};

}  // namespace wp05_enhanceunit