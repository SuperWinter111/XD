#include "wp01_battlectrl/task_intent_adapter.h"

namespace wp01_battlectrl {

EngagementInput TaskIntentAdapter::adapt(const TaskConstraint& taskConstraint, const TaskPackage& taskPackage) const {
  EngagementInput engagementInput;
  engagementInput.traceId = taskConstraint.traceId;
  engagementInput.taskId = taskConstraint.taskId;
  engagementInput.missionId = taskPackage.missionId;
  engagementInput.requestedAction = taskPackage.requestedAction;
  engagementInput.boundary = taskConstraint.boundary;
  return engagementInput;
}

}  // namespace wp01_battlectrl