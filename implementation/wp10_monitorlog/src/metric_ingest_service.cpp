#include "wp10_monitorlog/metric_ingest_service.h"
namespace wp10_monitorlog {
MonitorMetric MetricIngestService::build(const DeliveryReceipt& deliveryReceipt, const LinkQualitySnapshot& linkQualitySnapshot) const {
  return MonitorMetric{deliveryReceipt.traceId, "delivery_link_health", deliveryReceipt.success ? static_cast<double>(linkQualitySnapshot.qualityScore) : 0.0, "msg_comm"};
}
}