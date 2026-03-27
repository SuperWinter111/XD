#include "wp08_knowledgerule/recommendation_assembler.h"

namespace wp08_knowledgerule {

RecommendationItem RecommendationAssembler::assemble(const RuleEvaluationResult& ruleEvaluationResult) const {
  RecommendationItem recommendationItem;
  recommendationItem.traceId = ruleEvaluationResult.traceId;
  recommendationItem.recommendationId = ruleEvaluationResult.requestId + ":recommended";
  recommendationItem.recommendedAction = ruleEvaluationResult.decision;
  recommendationItem.sourceRuleId = ruleEvaluationResult.matchedRules.empty()
                                        ? "rule-context-insufficient"
                                        : ruleEvaluationResult.matchedRules.front();
  return recommendationItem;
}

}  // namespace wp08_knowledgerule