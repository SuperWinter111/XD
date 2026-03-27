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

  const auto registration = applicationService.registerPlatform(
      "trace-enhance-003", test_support::makePlatformState(), test_support::makePayloadState(), test_support::makeWeaponState());
  assert(registration.platformId == "uav-001");
  assert(registration.capabilitySource == "eo_sensor+weapon:weapon-agt-001");

  const auto rawTargetInput = applicationService.publishPerception(
      "trace-enhance-004", "uav-001", "sensor-eo-001", "track-001", 1711182100000);
  assert(rawTargetInput.sensorId == "sensor-eo-001");
  assert(rawTargetInput.targetTrackToken == "track-001");
  return 0;
}