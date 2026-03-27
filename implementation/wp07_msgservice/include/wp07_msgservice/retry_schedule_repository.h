#pragma once

#include <filesystem>
#include <optional>
#include <vector>

#include "wp07_msgservice/message_types.h"

namespace wp07_msgservice {

class RetryScheduleRepository {
 public:
  virtual ~RetryScheduleRepository() = default;

  virtual std::optional<RetryScheduleEntry> saveRetrySchedule(const MessageEnvelope& envelope,
                                                              const RetryPlan& retryPlan,
                                                              std::int64_t scheduledAtUtcMs) = 0;
};

class InMemoryRetryScheduleRepository final : public RetryScheduleRepository {
 public:
  std::optional<RetryScheduleEntry> saveRetrySchedule(const MessageEnvelope& envelope,
                                                      const RetryPlan& retryPlan,
                                                      std::int64_t scheduledAtUtcMs) override;

  const std::vector<RetryScheduleEntry>& scheduledEntries() const;

 private:
  std::vector<RetryScheduleEntry> scheduledEntries_;
};

class FileRetryScheduleRepository final : public RetryScheduleRepository {
 public:
  explicit FileRetryScheduleRepository(std::filesystem::path filePath);

  std::optional<RetryScheduleEntry> saveRetrySchedule(const MessageEnvelope& envelope,
                                                      const RetryPlan& retryPlan,
                                                      std::int64_t scheduledAtUtcMs) override;

  const std::filesystem::path& filePath() const;

 private:
  std::filesystem::path filePath_;
};

}  // namespace wp07_msgservice