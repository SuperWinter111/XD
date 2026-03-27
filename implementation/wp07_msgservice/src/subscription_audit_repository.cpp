#include "wp07_msgservice/subscription_audit_repository.h"

#include <fstream>

#include "wp07_msgservice/file_persistence_format.h"

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

}  // namespace

SubscriptionBindingAuditRecord InMemorySubscriptionAuditRepository::saveBindingDecision(
    const SubscriptionBinding& binding,
    const std::string& traceId,
    std::int64_t recordedAtUtcMs) {
  SubscriptionBindingAuditRecord record = makeAuditRecord(binding, traceId, recordedAtUtcMs);
  records_.push_back(record);
  return record;
}

const std::vector<SubscriptionBindingAuditRecord>& InMemorySubscriptionAuditRepository::records() const {
  return records_;
}

FileSubscriptionAuditRepository::FileSubscriptionAuditRepository(std::filesystem::path filePath)
    : filePath_(std::move(filePath)) {}

SubscriptionBindingAuditRecord FileSubscriptionAuditRepository::saveBindingDecision(
    const SubscriptionBinding& binding,
    const std::string& traceId,
    std::int64_t recordedAtUtcMs) {
  SubscriptionBindingAuditRecord record = makeAuditRecord(binding, traceId, recordedAtUtcMs);

  FilePersistenceFormat::ensureFileHeader(
      filePath_,
      FilePersistenceFormat::kSubscriptionAuditFormatVersion,
      "audit_record_id|trace_id|subscription_id|topic|subscriber_endpoint_id|status|status_reason|recorded_at_utc_ms");

  if (filePath_.has_parent_path()) {
    std::filesystem::create_directories(filePath_.parent_path());
  }

  std::ofstream output(filePath_, std::ios::app);
  output << record.auditRecordId << '|'
         << record.traceId << '|'
         << record.subscriptionId << '|'
         << record.topic << '|'
         << record.subscriberEndpointId << '|'
         << toString(record.status) << '|'
         << record.statusReason << '|'
         << record.recordedAtUtcMs << '\n';
  return record;
}

const std::filesystem::path& FileSubscriptionAuditRepository::filePath() const {
  return filePath_;
}

}  // namespace wp07_msgservice