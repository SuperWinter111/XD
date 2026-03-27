#pragma once

#include "wp02_taskmgmt/message_types.h"

namespace wp02_taskmgmt {

class TaskReconstructionService {
 public:
  TaskReconstructionDecision evaluate(const std::string& traceId,
                                      const std::string& missionId,
                                      const std::string& taskPackageId,
                                      ReconstructionReason reason,
                                      bool exceedsTaskBoundary,
                                      std::int64_t decidedAtUtcMs) const;
};

}  // namespace wp02_taskmgmt