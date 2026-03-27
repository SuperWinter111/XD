#pragma once

#include "wp01_battlectrl/message_types.h"

namespace wp01_battlectrl {

class TaskIntentAdapter {
 public:
  EngagementInput adapt(const TaskConstraint& taskConstraint, const TaskPackage& taskPackage) const;
};

}  // namespace wp01_battlectrl