#include "wp08_knowledgerule/knowledgerule_application_service.h"

namespace wp08_knowledgerule {

KnowledgeRuleApplicationService::KnowledgeRuleApplicationService(QueryGateway& queryGateway,
                                                                 RequestContextBuilder& requestContextBuilder,
                                                                 RuleExecutionEngine& ruleExecutionEngine,
                                                                 RecommendationAssembler& recommendationAssembler,
                                                                 ReasonTraceService& reasonTraceService)
    : queryGateway_(queryGateway),
      requestContextBuilder_(requestContextBuilder),
      ruleExecutionEngine_(ruleExecutionEngine),
      recommendationAssembler_(recommendationAssembler),
      reasonTraceService_(reasonTraceService) {}

InferenceResult KnowledgeRuleApplicationService::infer(const InferenceRequest& inferenceRequest,
                                                       const TargetFeatureSnapshot* targetFeatureSnapshot,
                                                       const ThreatAssessment* threatAssessment) const {
  InferenceResult result;
  const auto normalizedRequest = queryGateway_.normalize(inferenceRequest);
  result.queryContext = requestContextBuilder_.build(normalizedRequest, targetFeatureSnapshot, threatAssessment);
  result.ruleEvaluationResult = ruleExecutionEngine_.execute(result.queryContext);
  result.recommendationItem = recommendationAssembler_.assemble(result.ruleEvaluationResult);
  result.reasonTrace = reasonTraceService_.build(result.ruleEvaluationResult, result.recommendationItem);
  return result;
}

}  // namespace wp08_knowledgerule