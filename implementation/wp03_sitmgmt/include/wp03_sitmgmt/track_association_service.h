#pragma once

#include "wp03_sitmgmt/message_types.h"

namespace wp03_sitmgmt {

class TrackAssociationService {
 public:
  TrackCandidate associate(const StandardizedObservation& standardizedObservation) const;
};

}  // namespace wp03_sitmgmt