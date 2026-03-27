#include "wp05_enhanceunit/platform_command_service.h"

namespace wp05_enhanceunit {

CommandAck PlatformCommandService::dispatch(const PlatformCommand& platformCommand, const std::string& missionId) const {
  CommandAck commandAck;
  commandAck.traceId = platformCommand.traceId;
  commandAck.commandId = platformCommand.commandId;
  commandAck.missionId = missionId;
  commandAck.platformId = platformCommand.platformId;
  commandAck.accepted = !platformCommand.platformId.empty() && !platformCommand.parameters.empty();
  commandAck.rejectionReason = commandAck.accepted ? "" : "platform_command_invalid";
  return commandAck;
}

}  // namespace wp05_enhanceunit