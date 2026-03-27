#pragma once

#include "wp04_resmgmt/message_types.h"

namespace wp04_resmgmt {

class LinkImpactEvaluator {
 public:
  AvailabilityImpact evaluate(const LinkQualitySnapshot& linkQualitySnapshot,
                              const DegradationAlert* degradationAlert) const;
};

}  // namespace wp04_resmgmt