#pragma once

#include "wp03_sitmgmt/message_types.h"

namespace wp03_sitmgmt {

class AttributeFusionService {
 public:
  FusedTrack fuse(const TrackCandidate& trackCandidate) const;
};

}  // namespace wp03_sitmgmt