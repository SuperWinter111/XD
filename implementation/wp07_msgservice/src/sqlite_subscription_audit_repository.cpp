#include "wp07_msgservice/sqlite_subscription_audit_repository.h"

#include <stdexcept>

#include <sqlite3.h>

namespace wp07_msgservice {

namespace {

SubscriptionBindingAuditRecord makeAuditRecord(const SubscriptionBinding& binding,
                                               const std::string& traceId,
                                               std::int64_t recordedAtUtcMs) {
  SubscriptionBindingAuditRecord record;
  record.auditRecordId = binding.subscriptionId + ":audit:" + traceId;
  record.traceId = traceId;
  record.subscriptionId = binding.subscriptionId;
  record.topic = binding.topic;
  record.subscriberEndpointId = binding.subscriberEndpointId;
  record.status = binding.status;
  record.statusReason = binding.statusReason;
  record.recordedAtUtcMs = recordedAtUtcMs;
  return record;
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

SqliteSubscriptionAuditRepository::SqliteSubscriptionAuditRepository(std::filesystem::path databasePath)
    : databasePath_(std::move(databasePath)) {
  open();
  ensureSchema();
}

SqliteSubscriptionAuditRepository::~SqliteSubscriptionAuditRepository() {
  if (database_ != nullptr) {
    sqlite3_close(database_);
  }
}

SubscriptionBindingAuditRecord SqliteSubscriptionAuditRepository::saveBindingDecision(
    const SubscriptionBinding& binding,
    const std::string& traceId,
    std::int64_t recordedAtUtcMs) {
  SubscriptionBindingAuditRecord record = makeAuditRecord(binding, traceId, recordedAtUtcMs);

  static constexpr const char* kInsertSql =
      "INSERT INTO subscription_audit (audit_record_id, trace_id, subscription_id, topic, subscriber_endpoint_id, status, status_reason, recorded_at_utc_ms) "
      "VALUES (?, ?, ?, ?, ?, ?, ?, ?);";

  sqlite3_stmt* statement = nullptr;
  if (sqlite3_prepare_v2(database_, kInsertSql, -1, &statement, nullptr) != SQLITE_OK) {
    throw std::runtime_error("failed to prepare subscription audit insert statement");
  }

  sqlite3_bind_text(statement, 1, record.auditRecordId.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(statement, 2, record.traceId.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(statement, 3, record.subscriptionId.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(statement, 4, record.topic.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(statement, 5, record.subscriberEndpointId.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(statement, 6, toString(record.status), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(statement, 7, record.statusReason.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_int64(statement, 8, record.recordedAtUtcMs);

  if (sqlite3_step(statement) != SQLITE_DONE) {
    sqlite3_finalize(statement);
    throw std::runtime_error("failed to insert subscription audit record");
  }

  sqlite3_finalize(statement);
  return record;
}

const std::filesystem::path& SqliteSubscriptionAuditRepository::databasePath() const {
  return databasePath_;
}

void SqliteSubscriptionAuditRepository::open() {
  if (databasePath_.has_parent_path()) {
    std::filesystem::create_directories(databasePath_.parent_path());
  }

  if (sqlite3_open(databasePath_.string().c_str(), &database_) != SQLITE_OK) {
    throw std::runtime_error("failed to open sqlite database for subscription audit");
  }
}

void SqliteSubscriptionAuditRepository::ensureSchema() {
  execOrThrow(database_,
              "CREATE TABLE IF NOT EXISTS subscription_audit ("
              "audit_record_id TEXT PRIMARY KEY,"
              "trace_id TEXT NOT NULL,"
              "subscription_id TEXT NOT NULL,"
              "topic TEXT NOT NULL,"
              "subscriber_endpoint_id TEXT NOT NULL,"
              "status TEXT NOT NULL,"
              "status_reason TEXT NOT NULL,"
              "recorded_at_utc_ms INTEGER NOT NULL"
              ");");
}

}  // namespace wp07_msgservice