#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace wp03_sitmgmt {

struct RawTargetInput {
  std::string traceId;
  std::string platformId;
  std::string sensorId;
  std::string targetTrackToken;
  std::int64_t reportedAtUtcMs{0};
};

struct RecommendationItem {
  std::string traceId;
  std::string ruleId;
  std::string suggestion;
  std::string explanation;
};

struct TargetTruth {
  std::string traceId;
  std::string targetTrackToken;
  std::string truthLabel;
};

struct ExternalObservation {
  std::string traceId;
  std::string sourceName;
  std::string targetTrackToken;
};

struct StandardizedObservation {
  std::string traceId;
  std::string targetTrackToken;
  std::vector<std::string> sources;
  std::int64_t observedAtUtcMs{0};
};

struct TrackCandidate {
  std::string traceId;
  std::string targetTrackToken;
  std::vector<std::string> associatedSources;
};

struct FusedTrack {
  std::string traceId;
  std::string trackId;
  std::vector<std::string> sources;
  double confidence{0.0};
  std::string locationToken;
};

struct ThreatAssessment {
  std::string traceId;
  std::string trackId;
  std::string threatLevel;
  std::vector<std::string> reasons;
};

struct SituationSnapshot {
  std::string traceId;
  std::vector<std::string> activeTrackIds;
  std::string summary;
};

struct SituationSummaryReport {
  std::string traceId;
  std::string reportId;
  std::string summary;
};

struct CriticalAlert {
  std::string traceId;
  std::string alertCode;
  std::string severity;
};

}  // namespace wp03_sitmgmt