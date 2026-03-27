#pragma once

#include <optional>

#include "wp05_enhanceunit/message_types.h"

namespace wp05_enhanceunit {

class ExecutionFeedbackBridge {
 public:
  MissionProgress buildMissionProgress(const CommandAck& commandAck,
                                       const std::string& progressState,
                                       std::uint32_t progressPct) const;
  std::optional<PlatformAlert> buildPlatformAlert(const CommandAck& commandAck) const;
};

}  // namespace wp05_enhanceunit