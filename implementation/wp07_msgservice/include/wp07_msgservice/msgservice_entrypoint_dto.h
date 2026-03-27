#pragma once

#include <cstdint>
#include <string>

namespace wp07_msgservice {

struct RegisterTopicRequestDto {
  std::string topic;
  std::string domain;
  std::string payloadType;
  std::string qosProfile;
  std::string topicState;
  std::string ownerTeam;
  std::string schemaUri;
  std::int64_t retentionMs{0};
  std::string traceId;
};

struct RegisterSubscriptionRequestDto {
  std::string subscriptionId;
  std::string topic;
  std::string subscriberEndpointId;
  std::string status;
  std::string statusReason;
  std::string traceId;
  std::int64_t recordedAtUtcMs{0};
};

struct RecordDeliveryRequestDto {
  std::string traceId;
  std::string topic;
  std::string payloadType;
  std::string schemaVersion;
  std::string subscriberEndpointId;
  std::string status;
  std::string errorCode;
  std::int64_t deliveredAtUtcMs{0};
};

struct HandleDeliveryFailureRequestDto {
  std::string traceId;
  std::string topic;
  std::string payloadType;
  std::string schemaVersion;
  std::string failureReason;
  std::uint32_t retryCount{0};
  std::int64_t scheduledAtUtcMs{0};
  std::int64_t lastAttemptUtcMs{0};
};

}  // namespace wp07_msgservice