#pragma once

#include <optional>

#include "wp02_taskmgmt/taskmgmt_entrypoint_dto.h"
#include "wp02_taskmgmt/taskmgmt_use_cases.h"

namespace wp02_taskmgmt {

class TaskMgmtCommandMapper {
 public:
  std::optional<ReceiveMissionCommandCommand> map(const ReceiveMissionCommandRequestDto& dto) const;
  std::optional<CommitAllocationDecisionCommand> map(const CommitAllocationDecisionRequestDto& dto) const;
  std::optional<HandleExecutionExceptionCommand> map(const HandleExecutionExceptionRequestDto& dto) const;
};

}  // namespace wp02_taskmgmt