#pragma once
#include "wp10_monitorlog/alert_aggregation_service.h"
#include "wp10_monitorlog/log_index_service.h"
#include "wp10_monitorlog/metric_ingest_service.h"
#include "wp10_monitorlog/trace_correlation_service.h"
namespace wp10_monitorlog {
struct MonitorOutputs { MonitorMetric monitorMetric; MonitorAlert monitorAlert; LogDigest logDigest; TraceCorrelationRecord traceCorrelationRecord; };
class MonitorLogApplicationService {
 public:
  MonitorLogApplicationService(MetricIngestService& metricIngestService,
                               AlertAggregationService& alertAggregationService,
                               LogIndexService& logIndexService,
                               TraceCorrelationService& traceCorrelationService);
  MonitorOutputs build(const DeliveryReceipt& deliveryReceipt,
                       const LinkQualitySnapshot& linkQualitySnapshot,
                       const DeadLetterRecord* deadLetterRecord,
                       const DegradationAlert* degradationAlert,
                       const SecurityEvent& securityEvent,
                       const ReleaseEvent& releaseEvent) const;
 private:
  MetricIngestService& metricIngestService_;
  AlertAggregationService& alertAggregationService_;
  LogIndexService& logIndexService_;
  TraceCorrelationService& traceCorrelationService_;
};
}