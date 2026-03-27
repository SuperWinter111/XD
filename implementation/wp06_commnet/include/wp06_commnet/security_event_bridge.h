#pragma once

#include "wp06_commnet/message_types.h"

namespace wp06_commnet {

class SecurityEventBridge {
 public:
  SecurityEvent build(const RawSecuritySignal& rawSecuritySignal) const;
};

}  // namespace wp06_commnet