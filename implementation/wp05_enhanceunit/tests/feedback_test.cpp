#include <cassert>

#include "test_support.h"
#include "wp05_enhanceunit/enhanceunit_application_service.h"

using namespace wp05_enhanceunit;

int main() {
  CommandTranslator commandTranslator;
  PlatformCommandService platformCommandService;
  ExecutionFeedbackBridge executionFeedbackBridge;
  CapabilityReporter capabilityReporter;
  SimulationBridge simulationBridge;
  PerceptionBridge perceptionBridge;

  EnhanceUnitApplicationService applicationService(commandTranslator,
                                                   platformCommandService,
                                                   executionFeedbackBridge,
                                                   capabilityReporter,
                                                   simulationBridge,
                                                   perceptionBridge);

  const auto dispatchResult = applicationService.dispatchBattlePlan(test_support::makeBattlePlan());
  const auto missionProgress = applicationService.buildMissionProgress(dispatchResult.commandAck, "IN_PROGRESS", 40);
  assert(missionProgress.progressState == "IN_PROGRESS");
  assert(missionProgress.progressPct == 40);

  const auto rejectedAck = CommandAck{"trace-enhance-002", "cmd-002", "mission-002", "", false, "platform_command_invalid"};
  const auto platformAlert = applicationService.buildPlatformAlert(rejectedAck);
  assert(platformAlert.has_value());
  assert(platformAlert->alertCode == "command_rejected");
  return 0;
}