#pragma once

#include <filesystem>
#include <string>

namespace wp07_msgservice {

class FilePersistenceFormat {
 public:
  static constexpr const char* kSubscriptionAuditFormatVersion = "wp07.subscription_audit.v1";
  static constexpr const char* kRetryScheduleFormatVersion = "wp07.retry_schedule.v1";

  static void ensureFileHeader(const std::filesystem::path& filePath,
                               const std::string& formatVersion,
                               const std::string& columns);
};

}  // namespace wp07_msgservice