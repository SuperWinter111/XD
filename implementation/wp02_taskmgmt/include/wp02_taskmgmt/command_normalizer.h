#pragma once

#include <optional>

#include "wp02_taskmgmt/message_types.h"

namespace wp02_taskmgmt {

class CommandNormalizer {
 public:
  std::optional<MissionCommand> normalize(const MissionCommand& input) const;
};

}  // namespace wp02_taskmgmt