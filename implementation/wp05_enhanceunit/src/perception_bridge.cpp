#include "wp05_enhanceunit/perception_bridge.h"

namespace wp05_enhanceunit {

RawTargetInput PerceptionBridge::buildRawTargetInput(const std::string& traceId,
                                                     const std::string& platformId,
                                                     const std::string& sensorId,
                                                     const std::string& targetTrackToken,
                                                     std::int64_t reportedAtUtcMs) const {
  RawTargetInput input;
  input.traceId = traceId;
  input.platformId = platformId;
  input.sensorId = sensorId;
  input.targetTrackToken = targetTrackToken;
  input.reportedAtUtcMs = reportedAtUtcMs;
  return input;
}

}  // namespace wp05_enhanceunit