#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace wp02_taskmgmt {

struct ReceiveMissionCommandRequestDto {
  std::string traceId;
  std::string missionId;
  std::string sourceId;
  std::string objective;
  std::string targetArea;
  std::int64_t startUtcMs{0};
  std::int64_t endUtcMs{0};
  std::string priority;
  std::vector<std::string> requestedResourceKinds;
};

struct CommitAllocationDecisionRequestDto {
  std::string traceId;
  std::string requestId;
  std::string missionId;
  bool accepted{false};
  std::vector<std::string> allocatedResourceIds;
  std::vector<std::string> reservedResourceIds;
};

struct HandleExecutionExceptionRequestDto {
  std::string traceId;
  std::string missionId;
  std::string taskPackageId;
  std::string reason;
  bool exceedsTaskBoundary{false};
  std::int64_t decidedAtUtcMs{0};
};

}  // namespace wp02_taskmgmt