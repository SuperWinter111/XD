#pragma once

#include "wp02_taskmgmt/taskmgmt_application_service.h"
#include "wp02_taskmgmt/taskmgmt_entrypoint_dto.h"
#include "wp02_taskmgmt/taskmgmt_response_dto.h"

namespace wp02_taskmgmt {

class TaskMgmtResponseMapper {
 public:
  ReceiveMissionCommandResponseDto invalidReceiveMissionCommand(const ReceiveMissionCommandRequestDto& dto) const;
  CommitAllocationDecisionResponseDto invalidCommitAllocationDecision(const CommitAllocationDecisionRequestDto& dto) const;
  HandleExecutionExceptionResponseDto invalidHandleExecutionException(const HandleExecutionExceptionRequestDto& dto) const;

  ReceiveMissionCommandResponseDto mapReceiveMissionCommand(const ReceiveMissionCommandRequestDto& dto,
                                                           const ReceiveMissionCommandResult& result) const;
  CommitAllocationDecisionResponseDto mapCommitAllocationDecision(const CommitAllocationDecisionRequestDto& dto,
                                                                 const CommitAllocationDecisionResult& result) const;
  HandleExecutionExceptionResponseDto mapHandleExecutionException(const HandleExecutionExceptionRequestDto& dto,
                                                                 const HandleExecutionExceptionResult& result) const;
};

}  // namespace wp02_taskmgmt