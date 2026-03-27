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

  const auto feature = test_support::makeTargetFeatureSnapshot();
  const auto threat = test_support::makeThreatAssessment();
  const auto result = applicationService.infer(test_support::makeInferenceRequest(), &feature, &threat);
  assert(result.reasonTrace.recommendationId == "infer-001:recommended");
  assert(result.reasonTrace.ruleChain.size() == 1);
  return 0;
}