#pragma once

#include <string>

namespace wp02_taskmgmt {

struct ResponseMetaDto {
  bool accepted{false};
  std::string code;
  std::string message;
};

struct ReceiveMissionCommandResponseDto {
  ResponseMetaDto meta;
  bool acceptedCommand{false};
  std::string traceId;
  std::string missionId;
  std::string constraintId;
  std::string allocationRequestId;
};

struct CommitAllocationDecisionResponseDto {
  ResponseMetaDto meta;
  bool taskPackageCreated{false};
  std::string traceId;
  std::string missionId;
  std::string requestId;
  std::string taskPackageId;
};

struct HandleExecutionExceptionResponseDto {
  ResponseMetaDto meta;
  std::string traceId;
  std::string missionId;
  std::string taskPackageId;
  bool requiresReconstruction{false};
  std::string reconstructionReason;
  std::string expectedAction;
};

}  // namespace wp02_taskmgmt