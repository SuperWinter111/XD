#include "wp02_taskmgmt/task_lifecycle_tracker.h"

namespace wp02_taskmgmt {

void TaskLifecycleTracker::record(const std::string& traceId,
                                 const std::string& missionId,
                                 TaskLifecycleStage stage,
                                 const std::string& detail) {
  records_.push_back(TaskLifecycleRecord{traceId, missionId, stage, detail});
}

const std::vector<TaskLifecycleRecord>& TaskLifecycleTracker::records() const {
  return records_;
}

}  // namespace wp02_taskmgmt