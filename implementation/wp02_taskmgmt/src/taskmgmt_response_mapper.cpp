#include "wp02_taskmgmt/taskmgmt_response_mapper.h"

namespace wp02_taskmgmt {

ReceiveMissionCommandResponseDto TaskMgmtResponseMapper::invalidReceiveMissionCommand(
    const ReceiveMissionCommandRequestDto& dto) const {
  return {ResponseMetaDto{false, "invalid_argument", "invalid mission command request"},
          false,
          dto.traceId,
          dto.missionId,
          "",
          ""};
}

CommitAllocationDecisionResponseDto TaskMgmtResponseMapper::invalidCommitAllocationDecision(
    const CommitAllocationDecisionRequestDto& dto) const {
  return {ResponseMetaDto{false, "invalid_argument", "invalid allocation decision request"},
          false,
          dto.traceId,
          dto.missionId,
          dto.requestId,
          ""};
}

HandleExecutionExceptionResponseDto TaskMgmtResponseMapper::invalidHandleExecutionException(
    const HandleExecutionExceptionRequestDto& dto) const {
  return {ResponseMetaDto{false, "invalid_argument", "invalid execution exception request"},
          dto.traceId,
          dto.missionId,
          dto.taskPackageId,
          false,
          "",
          ""};
}

ReceiveMissionCommandResponseDto TaskMgmtResponseMapper::mapReceiveMissionCommand(
    const ReceiveMissionCommandRequestDto& dto,
    const ReceiveMissionCommandResult& result) const {
  return {ResponseMetaDto{result.accepted,
                          result.accepted ? "ok" : "mission_command_rejected",
                          result.accepted ? "mission command accepted" : "mission command rejected"},
          result.accepted,
          dto.traceId,
          dto.missionId,
          result.accepted ? result.taskConstraint.constraintId : "",
          result.accepted ? result.allocationRequest.requestId : ""};
}

CommitAllocationDecisionResponseDto TaskMgmtResponseMapper::mapCommitAllocationDecision(
    const CommitAllocationDecisionRequestDto& dto,
    const CommitAllocationDecisionResult& result) const {
  return {ResponseMetaDto{true,
                          result.taskPackageCreated ? "ok" : "allocation_recorded",
                          result.taskPackageCreated ? "task package created" : "allocation decision recorded"},
          result.taskPackageCreated,
          dto.traceId,
          dto.missionId,
          dto.requestId,
          result.taskPackage.has_value() ? result.taskPackage->taskPackageId : ""};
}

HandleExecutionExceptionResponseDto TaskMgmtResponseMapper::mapHandleExecutionException(
    const HandleExecutionExceptionRequestDto& dto,
    const HandleExecutionExceptionResult& result) const {
  return {ResponseMetaDto{true, "ok", "execution exception processed"},
          dto.traceId,
          dto.missionId,
          dto.taskPackageId,
          result.reconstructionDecision.requiresReconstruction,
          toString(result.reconstructionDecision.reason),
          result.reconstructionDecision.expectedAction};
}

}  // namespace wp02_taskmgmt