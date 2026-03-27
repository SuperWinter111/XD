#include "wp08_knowledgerule/rule_execution_engine.h"

namespace wp08_knowledgerule {

RuleEvaluationResult RuleExecutionEngine::execute(const QueryContext& queryContext) const {
  RuleEvaluationResult result;
  result.traceId = queryContext.traceId;
  result.requestId = queryContext.requestId;
  if (queryContext.contextRefs.size() >= 2) {
    result.matchedRules.push_back("rule-priority-target");
    result.decision = "recommend_focus_engagement";
  } else {
    result.missedRules.push_back("rule-context-insufficient");
    result.decision = "recommend_hold";
  }
  return result;
}

}  // namespace wp08_knowledgerule