#pragma once

#include <optional>

#include "wp02_taskmgmt/taskmgmt_application_service.h"
#include "wp02_taskmgmt/taskmgmt_command_mapper.h"
#include "wp02_taskmgmt/taskmgmt_response_mapper.h"

namespace wp02_taskmgmt {

class TaskMgmtCommandHandler {
 public:
  TaskMgmtCommandHandler(TaskMgmtCommandMapper& commandMapper,
                         TaskMgmtResponseMapper& responseMapper,
                         TaskMgmtApplicationService& applicationService);

  std::optional<ReceiveMissionCommandResult> handle(const ReceiveMissionCommandRequestDto& dto) const;
  std::optional<CommitAllocationDecisionResult> handle(const CommitAllocationDecisionRequestDto& dto) const;
  std::optional<HandleExecutionExceptionResult> handle(const HandleExecutionExceptionRequestDto& dto) const;

  ReceiveMissionCommandResponseDto handleRequest(const ReceiveMissionCommandRequestDto& dto) const;
  CommitAllocationDecisionResponseDto handleRequest(const CommitAllocationDecisionRequestDto& dto) const;
  HandleExecutionExceptionResponseDto handleRequest(const HandleExecutionExceptionRequestDto& dto) const;

 private:
  TaskMgmtCommandMapper& commandMapper_;
  TaskMgmtResponseMapper& responseMapper_;
  TaskMgmtApplicationService& applicationService_;
};

}  // namespace wp02_taskmgmt