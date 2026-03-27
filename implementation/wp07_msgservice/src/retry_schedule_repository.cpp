#include "wp07_msgservice/retry_schedule_repository.h"

#include <filesystem>
#include <fstream>
#include <string>

#include "wp07_msgservice/file_persistence_format.h"

namespace wp07_msgservice {

namespace {

RetryScheduleEntry makeScheduleEntry(const MessageEnvelope& envelope,
                                     const RetryPlan& retryPlan,
                                     std::int64_t scheduledAtUtcMs) {
  RetryScheduleEntry entry;
  entry.scheduleId = envelope.traceId + ":retry:" + std::to_string(retryPlan.nextRetryCount);
  entry.traceId = envelope.traceId;
  entry.topic = envelope.topic;
  entry.payloadType = envelope.payloadType;
  entry.failureReason = retryPlan.failureReason;
  entry.retryCount = retryPlan.nextRetryCount;
  entry.scheduledAtUtcMs = scheduledAtUtcMs;
  entry.nextAttemptAtUtcMs = scheduledAtUtcMs + retryPlan.nextAttemptDelayMs;
  return entry;
}

}  // namespace

std::optional<RetryScheduleEntry> InMemoryRetryScheduleRepository::saveRetrySchedule(
    const MessageEnvelope& envelope,
    const RetryPlan& retryPlan,
    std::int64_t scheduledAtUtcMs) {
  if (retryPlan.decision != RetryDecision::kRetryScheduled) {
    return std::nullopt;
  }

  RetryScheduleEntry entry = makeScheduleEntry(envelope, retryPlan, scheduledAtUtcMs);
  scheduledEntries_.push_back(entry);
  return entry;
}

const std::vector<RetryScheduleEntry>& InMemoryRetryScheduleRepository::scheduledEntries() const {
  return scheduledEntries_;
}

FileRetryScheduleRepository::FileRetryScheduleRepository(std::filesystem::path filePath)
    : filePath_(std::move(filePath)) {}

std::optional<RetryScheduleEntry> FileRetryScheduleRepository::saveRetrySchedule(
    const MessageEnvelope& envelope,
    const RetryPlan& retryPlan,
    std::int64_t scheduledAtUtcMs) {
  if (retryPlan.decision != RetryDecision::kRetryScheduled) {
    return std::nullopt;
  }

  RetryScheduleEntry entry = makeScheduleEntry(envelope, retryPlan, scheduledAtUtcMs);
  FilePersistenceFormat::ensureFileHeader(
      filePath_,
      FilePersistenceFormat::kRetryScheduleFormatVersion,
      "schedule_id|trace_id|topic|payload_type|failure_reason|retry_count|scheduled_at_utc_ms|next_attempt_at_utc_ms");

  if (filePath_.has_parent_path()) {
    std::filesystem::create_directories(filePath_.parent_path());
  }

  std::ofstream output(filePath_, std::ios::app);
  output << entry.scheduleId << '|'
         << entry.traceId << '|'
         << entry.topic << '|'
         << entry.payloadType << '|'
         << toString(entry.failureReason) << '|'
         << entry.retryCount << '|'
         << entry.scheduledAtUtcMs << '|'
         << entry.nextAttemptAtUtcMs << '\n';
  return entry;
}

const std::filesystem::path& FileRetryScheduleRepository::filePath() const {
  return filePath_;
}

}  // namespace wp07_msgservice