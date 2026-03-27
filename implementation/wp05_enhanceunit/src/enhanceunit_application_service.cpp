#include "wp05_enhanceunit/enhanceunit_application_service.h"

namespace wp05_enhanceunit {

EnhanceUnitApplicationService::EnhanceUnitApplicationService(CommandTranslator& commandTranslator,
                                                             PlatformCommandService& platformCommandService,
                                                             ExecutionFeedbackBridge& executionFeedbackBridge,
                                                             CapabilityReporter& capabilityReporter,
                                                             SimulationBridge& simulationBridge,
                                                             PerceptionBridge& perceptionBridge)
    : commandTranslator_(commandTranslator),
      platformCommandService_(platformCommandService),
      executionFeedbackBridge_(executionFeedbackBridge),
      capabilityReporter_(capabilityReporter),
      simulationBridge_(simulationBridge),
      perceptionBridge_(perceptionBridge) {}

BattlePlanDispatchResult EnhanceUnitApplicationService::dispatchBattlePlan(const BattlePlan& battlePlan) const {
  BattlePlanDispatchResult result;
  result.platformCommand = commandTranslator_.translate(battlePlan);
  result.commandAck = platformCommandService_.dispatch(result.platformCommand, battlePlan.missionId);
  return result;
}

MissionProgress EnhanceUnitApplicationService::buildMissionProgress(const CommandAck& commandAck,
                                                                   const std::string& progressState,
                                                                   std::uint32_t progressPct) const {
  return executionFeedbackBridge_.buildMissionProgress(commandAck, progressState, progressPct);
}

std::optional<PlatformAlert> EnhanceUnitApplicationService::buildPlatformAlert(const CommandAck& commandAck) const {
  return executionFeedbackBridge_.buildPlatformAlert(commandAck);
}

ResourceRegistration EnhanceUnitApplicationService::registerPlatform(const std::string& traceId,
                                                                    const PlatformState& platformState,
                                                                    const PayloadState& payloadState,
                                                                    const WeaponState& weaponState) const {
  return capabilityReporter_.buildRegistration(traceId, platformState, payloadState, weaponState);
}

RawTargetInput EnhanceUnitApplicationService::publishPerception(const std::string& traceId,
                                                               const std::string& platformId,
                                                               const std::string& sensorId,
                                                               const std::string& targetTrackToken,
                                                               std::int64_t reportedAtUtcMs) const {
  return perceptionBridge_.buildRawTargetInput(traceId, platformId, sensorId, targetTrackToken, reportedAtUtcMs);
}

MissionProgress EnhanceUnitApplicationService::buildSimulatedMissionProgress(const ClockTick& clockTick,
                                                                            const SimFlightState& simFlightState) const {
  return simulationBridge_.buildSimulatedMissionProgress(clockTick, simFlightState);
}

}  // namespace wp05_enhanceunit