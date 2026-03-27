#include "wp03_sitmgmt/attribute_fusion_service.h"

namespace wp03_sitmgmt {

FusedTrack AttributeFusionService::fuse(const TrackCandidate& trackCandidate) const {
  FusedTrack fusedTrack;
  fusedTrack.traceId = trackCandidate.traceId;
  fusedTrack.trackId = "fused:" + trackCandidate.targetTrackToken;
  fusedTrack.sources = trackCandidate.associatedSources;
  fusedTrack.confidence = trackCandidate.associatedSources.size() > 1 ? 0.85 : 0.65;
  fusedTrack.locationToken = trackCandidate.targetTrackToken + ":grid";
  return fusedTrack;
}

}  // namespace wp03_sitmgmt