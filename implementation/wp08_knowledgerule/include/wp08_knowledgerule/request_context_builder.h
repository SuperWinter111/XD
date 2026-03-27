#pragma once

#include "wp08_knowledgerule/message_types.h"

namespace wp08_knowledgerule {

class RequestContextBuilder {
 public:
  QueryContext build(const InferenceRequest& inferenceRequest,
                     const TargetFeatureSnapshot* targetFeatureSnapshot,
                     const ThreatAssessment* threatAssessment) const;
};

}  // namespace wp08_knowledgerule