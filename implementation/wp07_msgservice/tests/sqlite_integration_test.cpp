#include <cassert>
#include <filesystem>
#include <memory>
#include <stdexcept>
#include <string>

#include <sqlite3.h>

#include "test_support.h"
#include "wp07_msgservice/delivery_tracker.h"
#include "wp07_msgservice/msgservice_application_service.h"
#include "wp07_msgservice/msgservice_repository_factory.h"

using namespace wp07_msgservice;

namespace {

int queryCount(sqlite3* database, const char* sql) {
  sqlite3_stmt* statement = nullptr;
  if (sqlite3_prepare_v2(database, sql, -1, &statement, nullptr) != SQLITE_OK) {
    throw std::runtime_error("failed to prepare sqlite count query");
  }

  const int stepResult = sqlite3_step(statement);
  if (stepResult != SQLITE_ROW) {
    sqlite3_finalize(statement);
    throw std::runtime_error("failed to execute sqlite count query");
  }

  const int count = sqlite3_column_int(statement, 0);
  sqlite3_finalize(statement);
  return count;
}

std::string queryTextByTraceId(sqlite3* database,
                               const char* sql,
                               const std::string& traceId) {
  sqlite3_stmt* statement = nullptr;
  if (sqlite3_prepare_v2(database, sql, -1, &statement, nullptr) != SQLITE_OK) {
    throw std::runtime_error("failed to prepare sqlite text query");
  }

  sqlite3_bind_text(statement, 1, traceId.c_str(), -1, SQLITE_TRANSIENT);

  const int stepResult = sqlite3_step(statement);
  if (stepResult != SQLITE_ROW) {
    sqlite3_finalize(statement);
    throw std::runtime_error("failed to execute sqlite text query");
  }

  const unsigned char* text = sqlite3_column_text(statement, 0);
  std::string value = text != nullptr ? reinterpret_cast<const char*>(text) : "";
  sqlite3_finalize(statement);
  return value;
}

std::int64_t queryInt64ByTraceId(sqlite3* database,
                                 const char* sql,
                                 const std::string& traceId) {
  sqlite3_stmt* statement = nullptr;
  if (sqlite3_prepare_v2(database, sql, -1, &statement, nullptr) != SQLITE_OK) {
    throw std::runtime_error("failed to prepare sqlite int64 query");
  }

  sqlite3_bind_text(statement, 1, traceId.c_str(), -1, SQLITE_TRANSIENT);

  const int stepResult = sqlite3_step(statement);
  if (stepResult != SQLITE_ROW) {
    sqlite3_finalize(statement);
    throw std::runtime_error("failed to execute sqlite int64 query");
  }

  const auto value = sqlite3_column_int64(statement, 0);
  sqlite3_finalize(statement);
  return value;
}

}  // namespace

int main() {
#if !defined(BMS_MSGSERVICE_HAS_SQLITE)
  return 0;
#else
  const auto outputDir = std::filesystem::path("sqlite_integration_output");
  const auto databasePath = outputDir / "msgservice.sqlite3";
  std::filesystem::remove_all(outputDir);

  {
    TopicRegistry topicRegistry;
    SubscriptionRegistry subscriptionRegistry;
    SubscriptionGovernanceService subscriptionGovernanceService;
    DeliveryTracker deliveryTracker;
    RetryAndDeadLetterService retryAndDeadLetterService(RetryPolicy{3, 1000, 8000, true});
    assert(MsgServiceRepositoryFactory::defaultBackend() == PersistenceBackend::kSqlite);

    std::unique_ptr<SubscriptionAuditRepository> subscriptionAuditRepository =
      MsgServiceRepositoryFactory::createDefaultSubscriptionAuditRepository(outputDir);
    std::unique_ptr<RetryScheduleRepository> retryScheduleRepository =
      MsgServiceRepositoryFactory::createDefaultRetryScheduleRepository(outputDir);

    MsgServiceApplicationService applicationService(topicRegistry,
                                                    subscriptionRegistry,
                                                    subscriptionGovernanceService,
                                                    deliveryTracker,
                                                    retryAndDeadLetterService,
                            *subscriptionAuditRepository,
                            *retryScheduleRepository);

    assert(applicationService.registerTopic(RegisterTopicCommand{test_support::makeDeliveryReceiptTopic()}));

    const auto rejectedResult = applicationService.registerSubscription(RegisterSubscriptionCommand{
        test_support::makeRejectedBinding(), "trace-subscription-sqlite-001", 1711180700000});
    assert(rejectedResult.registered);
    assert(rejectedResult.auditRecord.has_value());

    const auto acceptedResult = applicationService.registerSubscription(RegisterSubscriptionCommand{
        test_support::makeSuccessBinding(), "trace-subscription-sqlite-002", 1711180701000});
    assert(acceptedResult.registered);
    assert(acceptedResult.auditRecord.has_value());

    const auto failureResult = applicationService.handleDeliveryFailure(HandleDeliveryFailureCommand{
        test_support::makeDeliveryEnvelope("trace-sqlite-010"),
        FailureReason::kTargetEndpointUnreachable,
        1,
        1711180910000,
        1711180910000});
    assert(failureResult.retryPlan.decision == RetryDecision::kRetryScheduled);
    assert(failureResult.retryScheduleEntry.has_value());
  }

  assert(std::filesystem::exists(databasePath));

  sqlite3* database = nullptr;
  assert(sqlite3_open(databasePath.string().c_str(), &database) == SQLITE_OK);

  const auto auditCount = queryCount(database, "SELECT COUNT(*) FROM subscription_audit;");
  const auto retryCount = queryCount(database, "SELECT COUNT(*) FROM retry_schedule;");

  assert(auditCount == 2);
  assert(retryCount == 1);

  assert(queryTextByTraceId(
             database,
             "SELECT status FROM subscription_audit WHERE trace_id = ?;",
             "trace-subscription-sqlite-001") == "rejected");
  assert(queryTextByTraceId(
             database,
             "SELECT status_reason FROM subscription_audit WHERE trace_id = ?;",
             "trace-subscription-sqlite-001") == "schema_version_not_allowed");
  assert(queryTextByTraceId(
             database,
             "SELECT subscriber_endpoint_id FROM subscription_audit WHERE trace_id = ?;",
             "trace-subscription-sqlite-002") == "monitorlog");
  assert(queryTextByTraceId(
             database,
             "SELECT failure_reason FROM retry_schedule WHERE trace_id = ?;",
             "trace-sqlite-010") == "target_endpoint_unreachable");
  assert(queryInt64ByTraceId(
             database,
             "SELECT next_attempt_at_utc_ms FROM retry_schedule WHERE trace_id = ?;",
             "trace-sqlite-010") == 1711180911000);

  sqlite3_close(database);
  std::filesystem::remove_all(outputDir);
  return 0;
#endif
}