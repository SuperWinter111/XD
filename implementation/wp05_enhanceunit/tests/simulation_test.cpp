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

  const auto missionProgress = applicationService.buildSimulatedMissionProgress(
      test_support::makeClockTick(), test_support::makeSimFlightState());
  assert(missionProgress.traceId == "trace-sim-001");
  assert(missionProgress.platformId == "uav-sim-001");
  assert(missionProgress.progressState == "SIM_IN_PROGRESS");
  return 0;
}