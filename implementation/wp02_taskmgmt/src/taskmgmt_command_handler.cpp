#include "wp02_taskmgmt/taskmgmt_command_handler.h"

namespace wp02_taskmgmt {

TaskMgmtCommandHandler::TaskMgmtCommandHandler(TaskMgmtCommandMapper& commandMapper,
                                               TaskMgmtResponseMapper& responseMapper,
                                               TaskMgmtApplicationService& applicationService)
    : commandMapper_(commandMapper), responseMapper_(responseMapper), applicationService_(applicationService) {}

std::optional<ReceiveMissionCommandResult> TaskMgmtCommandHandler::handle(const ReceiveMissionCommandRequestDto& dto) const {
  const auto command = commandMapper_.map(dto);
  if (!command.has_value()) {
    return std::nullopt;
  }
  return applicationService_.receiveMissionCommand(*command);
}

std::optional<CommitAllocationDecisionResult> TaskMgmtCommandHandler::handle(
    const CommitAllocationDecisionRequestDto& dto) const {
  const auto command = commandMapper_.map(dto);
  if (!command.has_value()) {
    return std::nullopt;
  }
  return applicationService_.commitAllocationDecision(*command);
}

std::optional<HandleExecutionExceptionResult> TaskMgmtCommandHandler::handle(
    const HandleExecutionExceptionRequestDto& dto) const {
  const auto command = commandMapper_.map(dto);
  if (!command.has_value()) {
    return std::nullopt;
  }
  return applicationService_.handleExecutionException(*command);
}

ReceiveMissionCommandResponseDto TaskMgmtCommandHandler::handleRequest(const ReceiveMissionCommandRequestDto& dto) const {
  const auto result = handle(dto);
  if (!result.has_value()) {
    return responseMapper_.invalidReceiveMissionCommand(dto);
  }
  return responseMapper_.mapReceiveMissionCommand(dto, *result);
}

CommitAllocationDecisionResponseDto TaskMgmtCommandHandler::handleRequest(
    const CommitAllocationDecisionRequestDto& dto) const {
  const auto result = handle(dto);
  if (!result.has_value()) {
    return responseMapper_.invalidCommitAllocationDecision(dto);
  }
  return responseMapper_.mapCommitAllocationDecision(dto, *result);
}

HandleExecutionExceptionResponseDto TaskMgmtCommandHandler::handleRequest(
    const HandleExecutionExceptionRequestDto& dto) const {
  const auto result = handle(dto);
  if (!result.has_value()) {
    return responseMapper_.invalidHandleExecutionException(dto);
  }
  return responseMapper_.mapHandleExecutionException(dto, *result);
}

}  // namespace wp02_taskmgmt