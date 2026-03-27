#pragma once

#include "wp08_knowledgerule/message_types.h"

namespace wp08_knowledgerule {

class ReasonTraceService {
 public:
  ReasonTrace build(const RuleEvaluationResult& ruleEvaluationResult,
                    const RecommendationItem& recommendationItem) const;
};

}  // namespace wp08_knowledgerule