#include <cassert>
#include <filesystem>
#include <memory>
#include <stdexcept>

#include "wp07_msgservice/msgservice_repository_factory.h"

using namespace wp07_msgservice;

int main() {
  const auto outputDir = std::filesystem::path("factory_test_output");
  std::filesystem::remove_all(outputDir);

  {
    const auto fileAuditRepository =
        MsgServiceRepositoryFactory::createSubscriptionAuditRepository(PersistenceBackend::kFile, outputDir);
    const auto fileRetryRepository =
        MsgServiceRepositoryFactory::createRetryScheduleRepository(PersistenceBackend::kFile, outputDir);
    assert(fileAuditRepository != nullptr);
    assert(fileRetryRepository != nullptr);

#if defined(BMS_MSGSERVICE_HAS_SQLITE)
    const auto defaultAuditRepository = MsgServiceRepositoryFactory::createDefaultSubscriptionAuditRepository(outputDir);
    const auto defaultRetryRepository = MsgServiceRepositoryFactory::createDefaultRetryScheduleRepository(outputDir);
    assert(defaultAuditRepository != nullptr);
    assert(defaultRetryRepository != nullptr);
#else
    bool defaultAuditThrew = false;
    try {
      (void)MsgServiceRepositoryFactory::createDefaultSubscriptionAuditRepository(outputDir);
    } catch (const std::runtime_error&) {
      defaultAuditThrew = true;
    }
    assert(defaultAuditThrew);

    bool defaultRetryThrew = false;
    try {
      (void)MsgServiceRepositoryFactory::createDefaultRetryScheduleRepository(outputDir);
    } catch (const std::runtime_error&) {
      defaultRetryThrew = true;
    }
    assert(defaultRetryThrew);
#endif
  }

  std::filesystem::remove_all(outputDir);
  return 0;
}