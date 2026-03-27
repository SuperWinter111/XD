#pragma once

#include "wp06_commnet/message_types.h"

namespace wp06_commnet {

class QualityScoringService {
 public:
  LinkQualitySnapshot score(const LinkObservation& linkObservation) const;
};

}  // namespace wp06_commnet