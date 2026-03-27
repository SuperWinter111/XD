#pragma once

#include "wp08_knowledgerule/message_types.h"

namespace wp08_knowledgerule {

class QueryGateway {
 public:
  InferenceRequest normalize(const InferenceRequest& inferenceRequest) const;
};

}  // namespace wp08_knowledgerule