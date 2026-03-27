#pragma once

#include "wp02_taskmgmt/message_types.h"

namespace wp02_taskmgmt {

class ResourceRequestCoordinator {
 public:
  AllocationRequest buildAllocationRequest(const TaskConstraint& taskConstraint) const;
};

}  // namespace wp02_taskmgmt