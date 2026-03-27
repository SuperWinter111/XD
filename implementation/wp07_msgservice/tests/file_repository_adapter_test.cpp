#include <cassert>
#include <filesystem>
#include <fstream>
#include <string>

#include "test_support.h"
#include "wp07_msgservice/file_persistence_format.h"
#include "wp07_msgservice/retry_schedule_repository.h"
#include "wp07_msgservice/subscription_audit_repository.h"

using namespace wp07_msgservice;

int main() {
  const auto outputDir = std::filesystem::path("adapter_test_output");
  const auto auditPath = outputDir / "subscription_audit.log";
  const auto retryPath = outputDir / "retry_schedule.log";
  std::filesystem::remove_all(outputDir);

  FileSubscriptionAuditRepository auditRepository(auditPath);
  const auto auditRecord =
      auditRepository.saveBindingDecision(test_support::makeRejectedBinding(), "trace-file-001", 1711181000000);
  assert(auditRecord.subscriptionId == "sub-002");
  assert(std::filesystem::exists(auditRepository.filePath()));

  std::ifstream auditInput(auditPath);
    std::string auditHeader;
    std::string auditColumns;
  std::string auditLine;
    std::getline(auditInput, auditHeader);
    std::getline(auditInput, auditColumns);
  std::getline(auditInput, auditLine);
    assert(auditHeader == std::string("#format=") + FilePersistenceFormat::kSubscriptionAuditFormatVersion);
    assert(auditColumns ==
      "#columns=audit_record_id|trace_id|subscription_id|topic|subscriber_endpoint_id|status|status_reason|recorded_at_utc_ms");
  assert(auditLine.find("trace-file-001") != std::string::npos);
  assert(auditLine.find("rejected") != std::string::npos);
  auditInput.close();

  FileRetryScheduleRepository retryRepository(retryPath);
  RetryPlan retryPlan;
  retryPlan.decision = RetryDecision::kRetryScheduled;
  retryPlan.nextRetryCount = 2;
  retryPlan.nextAttemptDelayMs = 1000;
  retryPlan.failureReason = FailureReason::kTargetEndpointUnreachable;

  const auto retryEntry =
      retryRepository.saveRetrySchedule(test_support::makeDeliveryEnvelope("trace-file-002"), retryPlan, 1711181010000);
  assert(retryEntry.has_value());
  assert(std::filesystem::exists(retryRepository.filePath()));

  std::ifstream retryInput(retryPath);
    std::string retryHeader;
    std::string retryColumns;
  std::string retryLine;
    std::getline(retryInput, retryHeader);
    std::getline(retryInput, retryColumns);
  std::getline(retryInput, retryLine);
    assert(retryHeader == std::string("#format=") + FilePersistenceFormat::kRetryScheduleFormatVersion);
    assert(retryColumns ==
      "#columns=schedule_id|trace_id|topic|payload_type|failure_reason|retry_count|scheduled_at_utc_ms|next_attempt_at_utc_ms");
  assert(retryLine.find("trace-file-002") != std::string::npos);
  assert(retryLine.find("target_endpoint_unreachable") != std::string::npos);
  retryInput.close();

  std::filesystem::remove_all(outputDir);
  return 0;
}