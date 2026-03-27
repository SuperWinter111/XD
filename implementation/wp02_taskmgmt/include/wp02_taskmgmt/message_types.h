#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace wp02_taskmgmt {

enum class MissionPriority {
  kRoutine,
  kHigh,
};

enum class TaskLifecycleStage {
  kCommandReceived,
  kDecomposed,
  kAllocationRequested,
  kAllocationResolved,
  kPlanCreated,
  kCommandAcknowledged,
  kMissionProgressUpdated,
  kEffectReported,
  kReconstructionRequired,
};

enum class ExecutionState {
  kPending,
  kInProgress,
  kCompleted,
  kBlocked,
};

enum class ReconstructionReason {
  kNone,
  kResourceLostBeyondTaskBoundary,
  kAllocationRejected,
  kExecutionBoundaryBroken,
};

inline const char* toString(MissionPriority priority) {
  switch (priority) {
    case MissionPriority::kRoutine:
      return "routine";
    case MissionPriority::kHigh:
      return "high";
  }

  return "unknown";
}

inline const char* toString(TaskLifecycleStage stage) {
  switch (stage) {
    case TaskLifecycleStage::kCommandReceived:
      return "command_received";
    case TaskLifecycleStage::kDecomposed:
      return "decomposed";
    case TaskLifecycleStage::kAllocationRequested:
      return "allocation_requested";
    case TaskLifecycleStage::kAllocationResolved:
      return "allocation_resolved";
    case TaskLifecycleStage::kPlanCreated:
      return "plan_created";
    case TaskLifecycleStage::kCommandAcknowledged:
      return "command_acknowledged";
    case TaskLifecycleStage::kMissionProgressUpdated:
      return "mission_progress_updated";
    case TaskLifecycleStage::kEffectReported:
      return "effect_reported";
    case TaskLifecycleStage::kReconstructionRequired:
      return "reconstruction_required";
  }

  return "unknown";
}

inline const char* toString(ExecutionState state) {
  switch (state) {
    case ExecutionState::kPending:
      return "pending";
    case ExecutionState::kInProgress:
      return "in_progress";
    case ExecutionState::kCompleted:
      return "completed";
    case ExecutionState::kBlocked:
      return "blocked";
  }

  return "unknown";
}

inline const char* toString(ReconstructionReason reason) {
  switch (reason) {
    case ReconstructionReason::kNone:
      return "none";
    case ReconstructionReason::kResourceLostBeyondTaskBoundary:
      return "resource_lost_beyond_task_boundary";
    case ReconstructionReason::kAllocationRejected:
      return "allocation_rejected";
    case ReconstructionReason::kExecutionBoundaryBroken:
      return "execution_boundary_broken";
  }

  return "unknown";
}

struct MissionCommand {
  std::string traceId;
  std::string missionId;
  std::string sourceId;
  std::string objective;
  std::string targetArea;
  std::int64_t startUtcMs{0};
  std::int64_t endUtcMs{0};
  MissionPriority priority{MissionPriority::kRoutine};
  std::vector<std::string> requestedResourceKinds;
};

struct TaskConstraint {
  std::string traceId;
  std::string missionId;
  std::string constraintId;
  std::string objective;
  std::string targetArea;
  std::int64_t earliestStartUtcMs{0};
  std::int64_t latestEndUtcMs{0};
  MissionPriority priority{MissionPriority::kRoutine};
  std::vector<std::string> requiredResourceKinds;
  std::string reconstructionBoundaryRule;
};

struct TaskPackage {
  std::string traceId;
  std::string missionId;
  std::string taskPackageId;
  std::string constraintId;
  std::string objective;
  std::string targetArea;
  std::vector<std::string> requestedResourceKinds;
  std::vector<std::string> allocatedResourceIds;
  ExecutionState executionState{ExecutionState::kPending};
};

struct AllocationRequest {
  std::string traceId;
  std::string requestId;
  std::string missionId;
  std::string taskPackageId;
  std::vector<std::string> requestedResourceKinds;
  bool reserveOnly{false};
};

struct AllocationDecision {
  std::string traceId;
  std::string requestId;
  std::string missionId;
  bool accepted{false};
  std::vector<std::string> allocatedResourceIds;
  std::vector<std::string> reservedResourceIds;
};

struct MissionProgress {
  std::string traceId;
  std::string missionId;
  std::string progressState;
};

struct CommandAck {
  std::string traceId;
  std::string missionId;
  bool accepted{false};
  std::string detail;
};

struct EngagementEffectReport {
  std::string traceId;
  std::string missionId;
  std::string effectStatus;
};

struct RecommendationItem {
  std::string traceId;
  std::string recommendationId;
  std::string summary;
};

struct TaskReconstructionDecision {
  std::string traceId;
  std::string missionId;
  std::string taskPackageId;
  ReconstructionReason reason{ReconstructionReason::kNone};
  bool requiresReconstruction{false};
  std::string expectedAction;
  std::int64_t decidedAtUtcMs{0};
};

struct TaskLifecycleRecord {
  std::string traceId;
  std::string missionId;
  TaskLifecycleStage stage{TaskLifecycleStage::kCommandReceived};
  std::string detail;
};

}  // namespace wp02_taskmgmt