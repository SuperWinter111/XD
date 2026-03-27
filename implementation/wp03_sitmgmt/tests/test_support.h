#pragma once

#include "wp03_sitmgmt/message_types.h"

namespace wp03_sitmgmt::test_support {

inline RawTargetInput makeRawTargetInput() {
  return RawTargetInput{"trace-sit-001", "uav-001", "sensor-eo-001", "track-001", 1711186000000};
}

inline ExternalObservation makeExternalObservation() {
  return ExternalObservation{"trace-sit-001", "ext-analysis", "track-001"};
}

inline RecommendationItem makeRecommendationItem() {
  return RecommendationItem{"trace-sit-001", "rule-001", "focus_track", "rule_support_high_threat"};
}

inline TargetTruth makeTargetTruth() {
  return TargetTruth{"trace-sit-001", "track-001", "simulated_hostile"};
}

}  // namespace wp03_sitmgmt::test_support