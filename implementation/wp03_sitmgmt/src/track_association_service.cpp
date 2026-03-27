#include "wp03_sitmgmt/track_association_service.h"

namespace wp03_sitmgmt {

TrackCandidate TrackAssociationService::associate(const StandardizedObservation& standardizedObservation) const {
  TrackCandidate candidate;
  candidate.traceId = standardizedObservation.traceId;
  candidate.targetTrackToken = standardizedObservation.targetTrackToken;
  candidate.associatedSources = standardizedObservation.sources;
  return candidate;
}

}  // namespace wp03_sitmgmt