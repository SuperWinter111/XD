#include "wp05_enhanceunit/command_translator.h"

namespace wp05_enhanceunit {

PlatformCommand CommandTranslator::translate(const BattlePlan& battlePlan) const {
  PlatformCommand platformCommand;
  platformCommand.traceId = battlePlan.traceId;
  platformCommand.commandId = battlePlan.battlePlanId + ":platform_command";
  platformCommand.battlePlanId = battlePlan.battlePlanId;
  platformCommand.platformId = battlePlan.platformId;
  platformCommand.commandType = battlePlan.commandMode.empty() ? "flight_plan_upload" : battlePlan.commandMode;
  for (const auto& segment : battlePlan.routeSegments) {
    platformCommand.parameters.push_back(segment.waypoint + ":" + segment.action);
  }
  return platformCommand;
}

}  // namespace wp05_enhanceunit