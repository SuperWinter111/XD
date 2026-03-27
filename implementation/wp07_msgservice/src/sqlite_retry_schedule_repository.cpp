#include "wp07_msgservice/sqlite_retry_schedule_repository.h"

#include <stdexcept>

#include <sqlite3.h>

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

void execOrThrow(sqlite3* database, const char* sql) {
  char* errorMessage = nullptr;
  if (sqlite3_exec(database, sql, nullptr, nullptr, &errorMessage) != SQLITE_OK) {
    const std::string message = errorMessage != nullptr ? errorMessage : "sqlite exec failed";
    sqlite3_free(errorMessage);
    throw std::runtime_error(message);
  }
}

}  // namespace

SqliteRetryScheduleRepository::SqliteRetryScheduleRepository(std::filesystem::path databasePath)
    : databasePath_(std::move(databasePath)) {
  open();
  ensureSchema();
}

SqliteRetryScheduleRepository::~SqliteRetryScheduleRepository() {
  if (database_ != nullptr) {
    sqlite3_close(database_);
  }
}

std::optional<RetryScheduleEntry> SqliteRetryScheduleRepository::saveRetrySchedule(
    const MessageEnvelope& envelope,
    const RetryPlan& retryPlan,
    std::int64_t scheduledAtUtcMs) {
  if (retryPlan.decision != RetryDecision::kRetryScheduled) {
    return std::nullopt;
  }

  RetryScheduleEntry entry = makeScheduleEntry(envelope, retryPlan, scheduledAtUtcMs);

  static constexpr const char* kInsertSql =
      "INSERT INTO retry_schedule (schedule_id, trace_id, topic, payload_type, failure_reason, retry_count, scheduled_at_utc_ms, next_attempt_at_utc_ms) "
      "VALUES (?, ?, ?, ?, ?, ?, ?, ?);";

  sqlite3_stmt* statement = nullptr;
  if (sqlite3_prepare_v2(database_, kInsertSql, -1, &statement, nullptr) != SQLITE_OK) {
    throw std::runtime_error("failed to prepare retry schedule insert statement");
  }

  sqlite3_bind_text(statement, 1, entry.scheduleId.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(statement, 2, entry.traceId.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(statement, 3, entry.topic.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(statement, 4, entry.payloadType.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(statement, 5, toString(entry.failureReason), -1, SQLITE_TRANSIENT);
  sqlite3_bind_int(statement, 6, static_cast<int>(entry.retryCount));
  sqlite3_bind_int64(statement, 7, entry.scheduledAtUtcMs);
  sqlite3_bind_int64(statement, 8, entry.nextAttemptAtUtcMs);

  if (sqlite3_step(statement) != SQLITE_DONE) {
    sqlite3_finalize(statement);
    throw std::runtime_error("failed to insert retry schedule entry");
  }

  sqlite3_finalize(statement);
  return entry;
}

const std::filesystem::path& SqliteRetryScheduleRepository::databasePath() const {
  return databasePath_;
}

void SqliteRetryScheduleRepository::open() {
  if (databasePath_.has_parent_path()) {
    std::filesystem::create_directories(databasePath_.parent_path());
  }

  if (sqlite3_open(databasePath_.string().c_str(), &database_) != SQLITE_OK) {
    throw std::runtime_error("failed to open sqlite database for retry schedule");
  }
}

void SqliteRetryScheduleRepository::ensureSchema() {
  execOrThrow(database_,
              "CREATE TABLE IF NOT EXISTS retry_schedule ("
              "schedule_id TEXT PRIMARY KEY,"
              "trace_id TEXT NOT NULL,"
              "topic TEXT NOT NULL,"
              "payload_type TEXT NOT NULL,"
              "failure_reason TEXT NOT NULL,"
              "retry_count INTEGER NOT NULL,"
              "scheduled_at_utc_ms INTEGER NOT NULL,"
              "next_attempt_at_utc_ms INTEGER NOT NULL"
              ");");
}

}  // namespace wp07_msgservice