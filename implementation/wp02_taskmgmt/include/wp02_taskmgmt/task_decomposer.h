#pragma once

#include "wp02_taskmgmt/message_types.h"

namespace wp02_taskmgmt {

class TaskDecomposer {
 public:
  TaskConstraint decompose(const MissionCommand& missionCommand) const;
};

}  // namespace wp02_taskmgmt