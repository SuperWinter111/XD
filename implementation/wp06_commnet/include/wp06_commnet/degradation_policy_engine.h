#pragma once

#include <optional>

#include "wp06_commnet/message_types.h"

namespace wp06_commnet {

class DegradationPolicyEngine {
 public:
  std::optional<DegradationAlert> evaluate(const LinkQualitySnapshot& linkQualitySnapshot) const;
};

}  // namespace wp06_commnet