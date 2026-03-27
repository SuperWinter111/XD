#include <cassert>
#include "test_support.h"
#include "wp10_monitorlog/monitorlog_application_service.h"
using namespace wp10_monitorlog;
int main() {
  MetricIngestService a; AlertAggregationService b; LogIndexService c; TraceCorrelationService d; MonitorLogApplicationService s(a,b,c,d);
  const auto out = s.build(test_support::makeDeliveryReceipt(), test_support::makeLinkQualitySnapshot(), nullptr, nullptr, test_support::makeSecurityEvent(), test_support::makeFailedReleaseEvent());
  assert(out.traceCorrelationRecord.correlatedNodes.size() == 3);
  assert(out.monitorAlert.alertCode == "security_event_detected");
  return 0;
}