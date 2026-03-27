#include "wp03_sitmgmt/perception_ingest_service.h"

namespace wp03_sitmgmt {

StandardizedObservation PerceptionIngestService::ingest(const RawTargetInput& rawTargetInput,
                                                        const ExternalObservation* externalObservation,
                                                        const TargetTruth* targetTruth) const {
  StandardizedObservation observation;
  observation.traceId = rawTargetInput.traceId;
  observation.targetTrackToken = rawTargetInput.targetTrackToken;
  observation.sources.push_back(rawTargetInput.sensorId);
  if (externalObservation != nullptr) {
    observation.sources.push_back(externalObservation->sourceName);
  }
  if (targetTruth != nullptr) {
    observation.sources.push_back("simulation_truth_ref");
  }
  observation.observedAtUtcMs = rawTargetInput.reportedAtUtcMs;
  return observation;
}

}  // namespace wp03_sitmgmt