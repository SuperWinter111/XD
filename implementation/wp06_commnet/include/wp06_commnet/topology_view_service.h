#pragma once

#include "wp06_commnet/message_types.h"

namespace wp06_commnet {

class TopologyViewService {
 public:
  CommTopologySnapshot refresh(const ResourceRegistration& resourceRegistration,
                               const LinkObservation& linkObservation) const;
};

}  // namespace wp06_commnet