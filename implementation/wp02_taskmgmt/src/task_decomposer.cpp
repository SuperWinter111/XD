#include "wp02_taskmgmt/task_decomposer.h"

namespace wp02_taskmgmt {

TaskConstraint TaskDecomposer::decompose(const MissionCommand& missionCommand) const {
  TaskConstraint constraint;
  constraint.traceId = missionCommand.traceId;
  constraint.missionId = missionCommand.missionId;
  constraint.constraintId = missionCommand.missionId + ":constraint";
  constraint.objective = missionCommand.objective;
  constraint.targetArea = missionCommand.targetArea;
  constraint.earliestStartUtcMs = missionCommand.startUtcMs;
  constraint.latestEndUtcMs = missionCommand.endUtcMs;
  constraint.priority = missionCommand.priority;
  constraint.requiredResourceKinds = missionCommand.requestedResourceKinds;
  constraint.reconstructionBoundaryRule = "task_reconstruction_on_boundary_break";
  return constraint;
}

}  // namespace wp02_taskmgmt