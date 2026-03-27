#pragma once
#include "wp10_monitorlog/message_types.h"
namespace wp10_monitorlog {
class MetricIngestService {
 public:
  MonitorMetric build(const DeliveryReceipt& deliveryReceipt, const LinkQualitySnapshot& linkQualitySnapshot) const;
};
}