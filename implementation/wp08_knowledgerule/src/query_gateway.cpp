#include "wp08_knowledgerule/query_gateway.h"

namespace wp08_knowledgerule {

InferenceRequest QueryGateway::normalize(const InferenceRequest& inferenceRequest) const {
  return inferenceRequest;
}

}  // namespace wp08_knowledgerule