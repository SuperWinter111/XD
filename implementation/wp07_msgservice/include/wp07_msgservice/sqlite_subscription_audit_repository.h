#pragma once

#include <filesystem>

#include "wp07_msgservice/subscription_audit_repository.h"

struct sqlite3;

namespace wp07_msgservice {

class SqliteSubscriptionAuditRepository final : public SubscriptionAuditRepository {
 public:
  explicit SqliteSubscriptionAuditRepository(std::filesystem::path databasePath);
  ~SqliteSubscriptionAuditRepository() override;

  SqliteSubscriptionAuditRepository(const SqliteSubscriptionAuditRepository&) = delete;
  SqliteSubscriptionAuditRepository& operator=(const SqliteSubscriptionAuditRepository&) = delete;

  SubscriptionBindingAuditRecord saveBindingDecision(const SubscriptionBinding& binding,
                                                     const std::string& traceId,
                                                     std::int64_t recordedAtUtcMs) override;

  const std::filesystem::path& databasePath() const;

 private:
  void open();
  void ensureSchema();

  std::filesystem::path databasePath_;
  sqlite3* database_{nullptr};
};

}  // namespace wp07_msgservice