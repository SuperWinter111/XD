#include "wp02_taskmgmt/task_package_builder.h"

namespace wp02_taskmgmt {

TaskPackage TaskPackageBuilder::buildTaskPackage(const TaskConstraint& taskConstraint,
                                                const AllocationDecision& allocationDecision) const {
  TaskPackage taskPackage;
  taskPackage.traceId = taskConstraint.traceId;
  taskPackage.missionId = taskConstraint.missionId;
  taskPackage.taskPackageId = taskConstraint.missionId + ":task_package";
  taskPackage.constraintId = taskConstraint.constraintId;
  taskPackage.objective = taskConstraint.objective;
  taskPackage.targetArea = taskConstraint.targetArea;
  taskPackage.requestedResourceKinds = taskConstraint.requiredResourceKinds;
  taskPackage.allocatedResourceIds = allocationDecision.allocatedResourceIds;
  taskPackage.executionState = ExecutionState::kPending;
  return taskPackage;
}

}  // namespace wp02_taskmgmt