#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace wp05_enhanceunit {

struct RouteSegment {
  std::string segmentId;
  std::string waypoint;
  std::string action;
};

struct BattlePlan {
  std::string traceId;
  std::string battlePlanId;
  std::string missionId;
  std::string platformId;
  std::string commandMode;
  std::vector<RouteSegment> routeSegments;
};

struct PlatformCommand {
  std::string traceId;
  std::string commandId;
  std::string battlePlanId;
  std::string platformId;
  std::string commandType;
  std::vector<std::string> parameters;
};

struct CommandAck {
  std::string traceId;
  std::string commandId;
  std::string missionId;
  std::string platformId;
  bool accepted{false};
  std::string rejectionReason;
};

struct MissionProgress {
  std::string traceId;
  std::string missionId;
  std::string platformId;
  std::string progressState;
  std::uint32_t progressPct{0};
};

struct PlatformAlert {
  std::string traceId;
  std::string missionId;
  std::string platformId;
  std::string alertCode;
  std::string severity;
};

struct PlatformState {
  std::string platformId;
  std::string platformType;
  bool online{false};
};

struct PayloadState {
  std::string platformId;
  std::string payloadId;
  std::string payloadType;
  bool ready{false};
};

struct WeaponState {
  std::string platformId;
  std::string weaponId;
  bool ready{false};
};

struct ResourceRegistration {
  std::string traceId;
  std::string platformId;
  std::string platformType;
  std::string capabilitySource;
};

struct RawTargetInput {
  std::string traceId;
  std::string platformId;
  std::string sensorId;
  std::string targetTrackToken;
  std::int64_t reportedAtUtcMs{0};
};

struct ClockTick {
  std::string traceId;
  std::string tickId;
  std::int64_t utcMs{0};
};

struct SimFlightState {
  std::string traceId;
  std::string platformId;
  std::string missionId;
  std::string phase;
};

}  // namespace wp05_enhanceunit