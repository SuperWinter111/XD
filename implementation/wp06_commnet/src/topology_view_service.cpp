#include "wp06_commnet/topology_view_service.h"

namespace wp06_commnet {

CommTopologySnapshot TopologyViewService::refresh(const ResourceRegistration& resourceRegistration,
                                                  const LinkObservation& linkObservation) const {
  CommTopologySnapshot commTopologySnapshot;
  commTopologySnapshot.traceId = resourceRegistration.traceId.empty() ? linkObservation.traceId : resourceRegistration.traceId;
  commTopologySnapshot.nodeIds = {resourceRegistration.platformId, linkObservation.sourceNodeId, linkObservation.targetNodeId};
  commTopologySnapshot.linkIds = {linkObservation.linkId};
  commTopologySnapshot.changeReason = "platform_registered_or_link_updated";
  return commTopologySnapshot;
}

}  // namespace wp06_commnet