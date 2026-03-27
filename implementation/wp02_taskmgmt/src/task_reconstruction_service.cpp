#include "wp02_taskmgmt/task_reconstruction_service.h"

namespace wp02_taskmgmt {

TaskReconstructionDecision TaskReconstructionService::evaluate(const std::string& traceId,
                                                              const std::string& missionId,
                                                              const std::string& taskPackageId,
                                                              ReconstructionReason reason,
                                                              bool exceedsTaskBoundary,
                                                              std::int64_t decidedAtUtcMs) const {
  TaskReconstructionDecision decision;
  decision.traceId = traceId;
  decision.missionId = missionId;
  decision.taskPackageId = taskPackageId;
  decision.reason = exceedsTaskBoundary ? reason : ReconstructionReason::kNone;
  decision.requiresReconstruction = exceedsTaskBoundary;
  decision.expectedAction = exceedsTaskBoundary ? "task_reconstruction" : "continue_plan_level_adjustment";
  decision.decidedAtUtcMs = decidedAtUtcMs;
  return decision;
}

}  // namespace wp02_taskmgmt