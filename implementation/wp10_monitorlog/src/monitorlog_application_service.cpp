#include "wp10_monitorlog/monitorlog_application_service.h"
namespace wp10_monitorlog {
MonitorLogApplicationService::MonitorLogApplicationService(MetricIngestService& metricIngestService,
                                                           AlertAggregationService& alertAggregationService,
                                                           LogIndexService& logIndexService,
                                                           TraceCorrelationService& traceCorrelationService)
    : metricIngestService_(metricIngestService),
      alertAggregationService_(alertAggregationService),
      logIndexService_(logIndexService),
      traceCorrelationService_(traceCorrelationService) {}
MonitorOutputs MonitorLogApplicationService::build(const DeliveryReceipt& deliveryReceipt,
                                                   const LinkQualitySnapshot& linkQualitySnapshot,
                                                   const DeadLetterRecord* deadLetterRecord,
                                                   const DegradationAlert* degradationAlert,
                                                   const SecurityEvent& securityEvent,
                                                   const ReleaseEvent& releaseEvent) const {
  return MonitorOutputs{metricIngestService_.build(deliveryReceipt, linkQualitySnapshot),
                        alertAggregationService_.build(deadLetterRecord, degradationAlert, &securityEvent, &releaseEvent),
                        logIndexService_.build(deliveryReceipt, securityEvent),
                        traceCorrelationService_.correlate(deliveryReceipt, securityEvent, releaseEvent)};
}
}