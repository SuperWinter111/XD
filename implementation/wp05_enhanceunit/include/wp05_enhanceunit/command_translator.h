#pragma once

#include "wp05_enhanceunit/message_types.h"

namespace wp05_enhanceunit {

class CommandTranslator {
 public:
  PlatformCommand translate(const BattlePlan& battlePlan) const;
};

}  // namespace wp05_enhanceunit