#pragma once

#include "wp01_battlectrl/message_types.h"

namespace wp01_battlectrl {

class RuleAssistGateway {
 public:
  InferenceRequest build(const ThreatAssessment& threatAssessment, const EngagementInput& engagementInput) const;
};

}  // namespace wp01_battlectrl