#include "wp02_taskmgmt/resource_request_coordinator.h"

namespace wp02_taskmgmt {

AllocationRequest ResourceRequestCoordinator::buildAllocationRequest(const TaskConstraint& taskConstraint) const {
  AllocationRequest request;
  request.traceId = taskConstraint.traceId;
  request.requestId = taskConstraint.missionId + ":allocation_request";
  request.missionId = taskConstraint.missionId;
  request.taskPackageId = taskConstraint.missionId + ":task_package";
  request.requestedResourceKinds = taskConstraint.requiredResourceKinds;
  request.reserveOnly = false;
  return request;
}

}  // namespace wp02_taskmgmt