#pragma once

#include "wp08_knowledgerule/message_types.h"

namespace wp08_knowledgerule {

class RuleExecutionEngine {
 public:
  RuleEvaluationResult execute(const QueryContext& queryContext) const;
};

}  // namespace wp08_knowledgerule