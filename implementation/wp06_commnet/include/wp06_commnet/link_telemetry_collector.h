#pragma once

#include "wp06_commnet/message_types.h"

namespace wp06_commnet {

class LinkTelemetryCollector {
 public:
  LinkObservation collect(const RawLinkTelemetry& rawLinkTelemetry) const;
};

}  // namespace wp06_commnet