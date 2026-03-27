#include "wp08_knowledgerule/reason_trace_service.h"

namespace wp08_knowledgerule {

ReasonTrace ReasonTraceService::build(const RuleEvaluationResult& ruleEvaluationResult,
                                      const RecommendationItem& recommendationItem) const {
  ReasonTrace reasonTrace;
  reasonTrace.traceId = ruleEvaluationResult.traceId;
  reasonTrace.recommendationId = recommendationItem.recommendationId;
  reasonTrace.ruleChain = ruleEvaluationResult.matchedRules.empty()
                              ? ruleEvaluationResult.missedRules
                              : ruleEvaluationResult.matchedRules;
  reasonTrace.explanation = "decision=" + recommendationItem.recommendedAction;
  return reasonTrace;
}

}  // namespace wp08_knowledgerule