#pragma once

#include "wp05_enhanceunit/message_types.h"

namespace wp05_enhanceunit {

class PerceptionBridge {
 public:
  RawTargetInput buildRawTargetInput(const std::string& traceId,
                                     const std::string& platformId,
                                     const std::string& sensorId,
                                     const std::string& targetTrackToken,
                                     std::int64_t reportedAtUtcMs) const;
};

}  // namespace wp05_enhanceunit