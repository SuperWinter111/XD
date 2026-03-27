#pragma once

#include <filesystem>
#include <memory>

#include "wp07_msgservice/retry_schedule_repository.h"
#include "wp07_msgservice/subscription_audit_repository.h"

namespace wp07_msgservice {

enum class PersistenceBackend {
  kFile,
  kSqlite,
};

class MsgServiceRepositoryFactory {
 public:
  static PersistenceBackend defaultBackend();

  static std::unique_ptr<SubscriptionAuditRepository> createSubscriptionAuditRepository(
      PersistenceBackend backend,
      const std::filesystem::path& basePath);

  static std::unique_ptr<RetryScheduleRepository> createRetryScheduleRepository(
      PersistenceBackend backend,
      const std::filesystem::path& basePath);

  static std::unique_ptr<SubscriptionAuditRepository> createDefaultSubscriptionAuditRepository(
      const std::filesystem::path& basePath);

  static std::unique_ptr<RetryScheduleRepository> createDefaultRetryScheduleRepository(
      const std::filesystem::path& basePath);
};

}  // namespace wp07_msgservice