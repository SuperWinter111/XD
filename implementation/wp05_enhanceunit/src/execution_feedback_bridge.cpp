#include "wp05_enhanceunit/execution_feedback_bridge.h"

namespace wp05_enhanceunit {

MissionProgress ExecutionFeedbackBridge::buildMissionProgress(const CommandAck& commandAck,
                                                            const std::string& progressState,
                                                            std::uint32_t progressPct) const {
  MissionProgress missionProgress;
  missionProgress.traceId = commandAck.traceId;
  missionProgress.missionId = commandAck.missionId;
  missionProgress.platformId = commandAck.platformId;
  missionProgress.progressState = progressState;
  missionProgress.progressPct = progressPct;
  return missionProgress;
}

std::optional<PlatformAlert> ExecutionFeedbackBridge::buildPlatformAlert(const CommandAck& commandAck) const {
  if (commandAck.accepted) {
    return std::nullopt;
  }

  PlatformAlert platformAlert;
  platformAlert.traceId = commandAck.traceId;
  platformAlert.missionId = commandAck.missionId;
  platformAlert.platformId = commandAck.platformId;
  platformAlert.alertCode = "command_rejected";
  platformAlert.severity = "warning";
  return platformAlert;
}

}  // namespace wp05_enhanceunit