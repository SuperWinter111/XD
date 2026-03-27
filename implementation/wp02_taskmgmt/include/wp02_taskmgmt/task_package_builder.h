#pragma once

#include "wp02_taskmgmt/message_types.h"

namespace wp02_taskmgmt {

class TaskPackageBuilder {
 public:
  TaskPackage buildTaskPackage(const TaskConstraint& taskConstraint,
                               const AllocationDecision& allocationDecision) const;
};

}  // namespace wp02_taskmgmt