#include "wp01_battlectrl/rule_assist_gateway.h"

namespace wp01_battlectrl {

InferenceRequest RuleAssistGateway::build(const ThreatAssessment& threatAssessment,
                                          const EngagementInput& engagementInput) const {
  InferenceRequest inferenceRequest;
  inferenceRequest.traceId = engagementInput.traceId;
  inferenceRequest.requestId = engagementInput.taskId + ":inference";
  inferenceRequest.trackId = threatAssessment.trackId;
  inferenceRequest.problemStatement = "assist_for_" + engagementInput.requestedAction;
  return inferenceRequest;
}

}  // namespace wp01_battlectrl