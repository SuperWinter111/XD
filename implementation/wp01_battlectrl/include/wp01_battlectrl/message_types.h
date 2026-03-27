#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace wp01_battlectrl {

struct TaskConstraint {
  std::string traceId;
  std::string taskId;
  std::string objective;
  std::string boundary;
};

struct TaskPackage {
  std::string traceId;
  std::string taskId;
  std::string missionId;
  std::string requestedAction;
};

struct AllocationDecision {
  std::string traceId;
  std::string requestId;
  std::string missionId;
  bool accepted{false};
  std::vector<std::string> allocatedResourceIds;
  std::string reason;
};

struct ResourceStateSnapshot {
  std::string traceId;
  std::string platformId;
  bool available{false};
  std::string availabilityReason;
};

struct FusedTrack {
  std::string traceId;
  std::string trackId;
  double confidence{0.0};
  std::string locationToken;
};

struct ThreatAssessment {
  std::string traceId;
  std::string trackId;
  std::string threatLevel;
  std::vector<std::string> reasons;
};

struct MissionProgress {
  std::string traceId;
  std::string missionId;
  std::string platformId;
  std::string progressState;
  std::uint32_t progressPct{0};
};

struct CommandAck {
  std::string traceId;
  std::string commandId;
  std::string missionId;
  std::string platformId;
  bool accepted{false};
};

struct PlatformAlert {
  std::string traceId;
  std::string missionId;
  std::string platformId;
  std::string alertCode;
};

struct DegradationAlert {
  std::string traceId;
  std::string linkId;
  std::string impactScope;
};

struct EngagementInput {
  std::string traceId;
  std::string taskId;
  std::string missionId;
  std::string requestedAction;
  std::string boundary;
};

struct BattlePlan {
  std::string traceId;
  std::string planId;
  std::string taskId;
  std::string missionId;
  std::string platformId;
  std::string targetTrackId;
  std::string action;
  std::string constraintRef;
};

struct PlanAdjustmentDecision {
  bool withinConstraint{false};
  bool shouldUpdatePlan{false};
  bool shouldFallbackTaskMgmt{false};
  std::string reason;
};

struct EngagementEffectReport {
  std::string traceId;
  std::string taskId;
  std::string planId;
  std::string effectConclusion;
};

struct InferenceRequest {
  std::string traceId;
  std::string requestId;
  std::string trackId;
  std::string problemStatement;
};

}  // namespace wp01_battlectrl