#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

#include "wp07_msgservice/message_types.h"

namespace wp07_msgservice {

class SubscriptionAuditRepository {
 public:
  virtual ~SubscriptionAuditRepository() = default;

  virtual SubscriptionBindingAuditRecord saveBindingDecision(const SubscriptionBinding& binding,
                                                             const std::string& traceId,
                                                             std::int64_t recordedAtUtcMs) = 0;
};

class InMemorySubscriptionAuditRepository final : public SubscriptionAuditRepository {
 public:
  SubscriptionBindingAuditRecord saveBindingDecision(const SubscriptionBinding& binding,
                                                     const std::string& traceId,
                                                     std::int64_t recordedAtUtcMs) override;

  const std::vector<SubscriptionBindingAuditRecord>& records() const;

 private:
  std::vector<SubscriptionBindingAuditRecord> records_;
};

class FileSubscriptionAuditRepository final : public SubscriptionAuditRepository {
 public:
  explicit FileSubscriptionAuditRepository(std::filesystem::path filePath);

  SubscriptionBindingAuditRecord saveBindingDecision(const SubscriptionBinding& binding,
                                                     const std::string& traceId,
                                                     std::int64_t recordedAtUtcMs) override;

  const std::filesystem::path& filePath() const;

 private:
  std::filesystem::path filePath_;
};

}  // namespace wp07_msgservice