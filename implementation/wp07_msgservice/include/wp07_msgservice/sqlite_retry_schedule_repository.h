#pragma once

#include <filesystem>
#include <optional>

#include "wp07_msgservice/retry_schedule_repository.h"

struct sqlite3;

namespace wp07_msgservice {

class SqliteRetryScheduleRepository final : public RetryScheduleRepository {
 public:
  explicit SqliteRetryScheduleRepository(std::filesystem::path databasePath);
  ~SqliteRetryScheduleRepository() override;

  SqliteRetryScheduleRepository(const SqliteRetryScheduleRepository&) = delete;
  SqliteRetryScheduleRepository& operator=(const SqliteRetryScheduleRepository&) = delete;

  std::optional<RetryScheduleEntry> saveRetrySchedule(const MessageEnvelope& envelope,
                                                      const RetryPlan& retryPlan,
                                                      std::int64_t scheduledAtUtcMs) override;

  const std::filesystem::path& databasePath() const;

 private:
  void open();
  void ensureSchema();

  std::filesystem::path databasePath_;
  sqlite3* database_{nullptr};
};

}  // namespace wp07_msgservice