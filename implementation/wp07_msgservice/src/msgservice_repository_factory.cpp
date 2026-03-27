#include "wp07_msgservice/msgservice_repository_factory.h"

#include <stdexcept>

#include "wp07_msgservice/retry_schedule_repository.h"
#include "wp07_msgservice/sqlite_retry_schedule_repository.h"
#include "wp07_msgservice/sqlite_subscription_audit_repository.h"
#include "wp07_msgservice/subscription_audit_repository.h"

namespace wp07_msgservice {

PersistenceBackend MsgServiceRepositoryFactory::defaultBackend() {
  return PersistenceBackend::kSqlite;
}

std::unique_ptr<SubscriptionAuditRepository> MsgServiceRepositoryFactory::createSubscriptionAuditRepository(
    PersistenceBackend backend,
    const std::filesystem::path& basePath) {
  switch (backend) {
    case PersistenceBackend::kFile:
      return std::make_unique<FileSubscriptionAuditRepository>(basePath / "subscription_audit.log");
    case PersistenceBackend::kSqlite:
#if defined(BMS_MSGSERVICE_HAS_SQLITE)
      return std::make_unique<SqliteSubscriptionAuditRepository>(basePath / "msgservice.sqlite3");
#else
      throw std::runtime_error("SQLite persistence selected, but SQLite3 dependency is not available in this build");
#endif
  }

  throw std::runtime_error("Unsupported persistence backend for subscription audit repository");
}

std::unique_ptr<RetryScheduleRepository> MsgServiceRepositoryFactory::createRetryScheduleRepository(
    PersistenceBackend backend,
    const std::filesystem::path& basePath) {
  switch (backend) {
    case PersistenceBackend::kFile:
      return std::make_unique<FileRetryScheduleRepository>(basePath / "retry_schedule.log");
    case PersistenceBackend::kSqlite:
#if defined(BMS_MSGSERVICE_HAS_SQLITE)
      return std::make_unique<SqliteRetryScheduleRepository>(basePath / "msgservice.sqlite3");
#else
      throw std::runtime_error("SQLite persistence selected, but SQLite3 dependency is not available in this build");
#endif
  }

  throw std::runtime_error("Unsupported persistence backend for retry schedule repository");
}

std::unique_ptr<SubscriptionAuditRepository> MsgServiceRepositoryFactory::createDefaultSubscriptionAuditRepository(
    const std::filesystem::path& basePath) {
  return createSubscriptionAuditRepository(defaultBackend(), basePath);
}

std::unique_ptr<RetryScheduleRepository> MsgServiceRepositoryFactory::createDefaultRetryScheduleRepository(
    const std::filesystem::path& basePath) {
  return createRetryScheduleRepository(defaultBackend(), basePath);
}

}  // namespace wp07_msgservice