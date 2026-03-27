#pragma once

#include <cstdint>

#include "wp02_taskmgmt/message_types.h"

namespace wp02_taskmgmt {

struct ReceiveMissionCommandCommand {
  MissionCommand missionCommand;
};

struct CommitAllocationDecisionCommand {
  AllocationDecision allocationDecision;
};

struct HandleExecutionExceptionCommand {
  std::string traceId;
  std::string missionId;
  std::string taskPackageId;
  ReconstructionReason reason{ReconstructionReason::kNone};
  bool exceedsTaskBoundary{false};
  std::int64_t decidedAtUtcMs{0};
};

}  // namespace wp02_taskmgmt