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

  const auto result = applicationService.dispatchBattlePlan(test_support::makeBattlePlan());
  assert(result.platformCommand.commandId == "battle-plan-001:platform_command");
  assert(result.platformCommand.parameters.size() == 2);
  assert(result.commandAck.accepted);
  assert(result.commandAck.commandId == result.platformCommand.commandId);
  return 0;
}