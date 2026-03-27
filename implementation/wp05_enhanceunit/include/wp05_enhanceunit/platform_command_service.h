#pragma once

#include "wp05_enhanceunit/message_types.h"

namespace wp05_enhanceunit {

class PlatformCommandService {
 public:
  CommandAck dispatch(const PlatformCommand& platformCommand, const std::string& missionId) const;
};

}  // namespace wp05_enhanceunit