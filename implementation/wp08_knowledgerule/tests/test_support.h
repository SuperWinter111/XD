#pragma once

#include "wp08_knowledgerule/message_types.h"

namespace wp08_knowledgerule::test_support {

inline InferenceRequest makeInferenceRequest() {
  return InferenceRequest{"trace-rule-001", "infer-001", "BattleCtrl", "battle_context"};
}

inline TargetFeatureSnapshot makeTargetFeatureSnapshot() {
  return TargetFeatureSnapshot{"trace-rule-001", "fused:track-001", "fast_mover"};
}

inline ThreatAssessment makeThreatAssessment() {
  return ThreatAssessment{"trace-rule-001", "fused:track-001", "high"};
}

inline InferenceRequest makeSparseRequest() {
  return InferenceRequest{"trace-rule-002", "infer-002", "TaskMgmt", "task_context"};
}

}  // namespace wp08_knowledgerule::test_support