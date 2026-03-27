#include <cassert>

#include "test_support.h"
#include "wp08_knowledgerule/knowledgerule_application_service.h"

using namespace wp08_knowledgerule;

int main() {
  QueryGateway queryGateway;
  RequestContextBuilder requestContextBuilder;
  RuleExecutionEngine ruleExecutionEngine;
  RecommendationAssembler recommendationAssembler;
  ReasonTraceService reasonTraceService;
  KnowledgeRuleApplicationService applicationService(queryGateway,
                                                     requestContextBuilder,
                                                     ruleExecutionEngine,
                                                     recommendationAssembler,
                                                     reasonTraceService);

  const auto result = applicationService.infer(test_support::makeSparseRequest(), nullptr, nullptr);
  assert(result.recommendationItem.recommendedAction == "recommend_hold");
  assert(result.reasonTrace.ruleChain.front() == "rule-context-insufficient");
  return 0;
}