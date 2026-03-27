#pragma once

#include "wp08_knowledgerule/message_types.h"

namespace wp08_knowledgerule {

class RecommendationAssembler {
 public:
  RecommendationItem assemble(const RuleEvaluationResult& ruleEvaluationResult) const;
};

}  // namespace wp08_knowledgerule