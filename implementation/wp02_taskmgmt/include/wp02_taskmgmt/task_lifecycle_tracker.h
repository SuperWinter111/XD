#pragma once

#include <vector>

#include "wp02_taskmgmt/message_types.h"

namespace wp02_taskmgmt {

class TaskLifecycleTracker {
 public:
  void record(const std::string& traceId,
              const std::string& missionId,
              TaskLifecycleStage stage,
              const std::string& detail);

  const std::vector<TaskLifecycleRecord>& records() const;

 private:
  std::vector<TaskLifecycleRecord> records_;
};

}  // namespace wp02_taskmgmt