#include "wp02_taskmgmt/command_normalizer.h"

namespace wp02_taskmgmt {

std::optional<MissionCommand> CommandNormalizer::normalize(const MissionCommand& input) const {
  if (input.traceId.empty() || input.missionId.empty() || input.sourceId.empty() || input.objective.empty() ||
      input.targetArea.empty() || input.requestedResourceKinds.empty()) {
    return std::nullopt;
  }

  if (input.startUtcMs <= 0 || input.endUtcMs <= input.startUtcMs) {
    return std::nullopt;
  }

  return input;
}

}  // namespace wp02_taskmgmt