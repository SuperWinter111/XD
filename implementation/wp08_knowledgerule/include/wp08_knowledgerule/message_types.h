#pragma once

#include <string>
#include <vector>

namespace wp08_knowledgerule {

struct InferenceRequest {
  std::string traceId;
  std::string requestId;
  std::string sourceSubsystem;
  std::string contextRef;
};

struct TargetFeatureSnapshot {
  std::string traceId;
  std::string trackId;
  std::string featureLabel;
};

struct ThreatAssessment {
  std::string traceId;
  std::string trackId;
  std::string threatLevel;
};

struct QueryContext {
  std::string traceId;
  std::string requestId;
  std::string sourceSubsystem;
  std::vector<std::string> contextRefs;
};

struct RuleEvaluationResult {
  std::string traceId;
  std::string requestId;
  std::vector<std::string> matchedRules;
  std::vector<std::string> missedRules;
  std::string decision;
};

struct RecommendationItem {
  std::string traceId;
  std::string recommendationId;
  std::string recommendedAction;
  std::string sourceRuleId;
};

struct ReasonTrace {
  std::string traceId;
  std::string recommendationId;
  std::vector<std::string> ruleChain;
  std::string explanation;
};

}  // namespace wp08_knowledgerule