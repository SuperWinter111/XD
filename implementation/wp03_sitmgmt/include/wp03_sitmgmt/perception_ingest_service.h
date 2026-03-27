#pragma once

#include "wp03_sitmgmt/message_types.h"

namespace wp03_sitmgmt {

class PerceptionIngestService {
 public:
  StandardizedObservation ingest(const RawTargetInput& rawTargetInput,
                                 const ExternalObservation* externalObservation,
                                 const TargetTruth* targetTruth) const;
};

}  // namespace wp03_sitmgmt