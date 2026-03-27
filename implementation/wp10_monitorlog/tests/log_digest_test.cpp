#include <cassert>
#include "test_support.h"
#include "wp10_monitorlog/monitorlog_application_service.h"
using namespace wp10_monitorlog;
int main() {
  MetricIngestService a; AlertAggregationService b; LogIndexService c; TraceCorrelationService d; MonitorLogApplicationService s(a,b,c,d);
  const auto degradationAlert = test_support::makeDegradationAlert();
  const auto out = s.build(test_support::makeDeliveryReceipt(), test_support::makeLinkQualitySnapshot(), nullptr, &degradationAlert, test_support::makeSecurityEvent(), test_support::makeReleaseEvent());
  assert(out.logDigest.sourceDomain == "msg+sec");
  return 0;
}