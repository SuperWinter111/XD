#include "wp08_knowledgerule/request_context_builder.h"

namespace wp08_knowledgerule {

QueryContext RequestContextBuilder::build(const InferenceRequest& inferenceRequest,
                                          const TargetFeatureSnapshot* targetFeatureSnapshot,
                                          const ThreatAssessment* threatAssessment) const {
  QueryContext context;
  context.traceId = inferenceRequest.traceId;
  context.requestId = inferenceRequest.requestId;
  context.sourceSubsystem = inferenceRequest.sourceSubsystem;
  context.contextRefs.push_back(inferenceRequest.contextRef);
  if (targetFeatureSnapshot != nullptr) {
    context.contextRefs.push_back(targetFeatureSnapshot->featureLabel);
  }
  if (threatAssessment != nullptr) {
    context.contextRefs.push_back("threat=" + threatAssessment->threatLevel);
  }
  return context;
}

}  // namespace wp08_knowledgerule