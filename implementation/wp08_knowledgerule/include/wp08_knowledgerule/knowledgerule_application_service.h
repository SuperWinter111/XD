#pragma once

#include "wp08_knowledgerule/query_gateway.h"
#include "wp08_knowledgerule/reason_trace_service.h"
#include "wp08_knowledgerule/recommendation_assembler.h"
#include "wp08_knowledgerule/request_context_builder.h"
#include "wp08_knowledgerule/rule_execution_engine.h"

namespace wp08_knowledgerule {

struct InferenceResult {
  QueryContext queryContext;
  RuleEvaluationResult ruleEvaluationResult;
  RecommendationItem recommendationItem;
  ReasonTrace reasonTrace;
};

class KnowledgeRuleApplicationService {
 public:
  KnowledgeRuleApplicationService(QueryGateway& queryGateway,
                                  RequestContextBuilder& requestContextBuilder,
                                  RuleExecutionEngine& ruleExecutionEngine,
                                  RecommendationAssembler& recommendationAssembler,
                                  ReasonTraceService& reasonTraceService);

  InferenceResult infer(const InferenceRequest& inferenceRequest,
                        const TargetFeatureSnapshot* targetFeatureSnapshot,
                        const ThreatAssessment* threatAssessment) const;

 private:
  QueryGateway& queryGateway_;
  RequestContextBuilder& requestContextBuilder_;
  RuleExecutionEngine& ruleExecutionEngine_;
  RecommendationAssembler& recommendationAssembler_;
  ReasonTraceService& reasonTraceService_;
};

}  // namespace wp08_knowledgerule