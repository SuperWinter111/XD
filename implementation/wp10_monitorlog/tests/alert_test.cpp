#include <cassert>
#include "test_support.h"
#include "wp10_monitorlog/monitorlog_application_service.h"
using namespace wp10_monitorlog;
int main() {
  MetricIngestService a; AlertAggregationService b; LogIndexService c; TraceCorrelationService d; MonitorLogApplicationService s(a,b,c,d);
  const auto dead = test_support::makeDeadLetterRecord();
  const auto out = s.build(test_support::makeDeliveryReceipt(), test_support::makeLinkQualitySnapshot(), &dead, nullptr, test_support::makeSecurityEvent(), test_support::makeReleaseEvent());
  assert(out.monitorAlert.alertCode == "dead_letter_detected");
  return 0;
}