#include "wp07_msgservice/msgservice_command_mapper.h"

namespace wp07_msgservice {

namespace {

std::optional<TopicState> parseTopicState(const std::string& value) {
  if (value == "active") {
    return TopicState::kActive;
  }
  if (value == "deprecated") {
    return TopicState::kDeprecated;
  }
  return std::nullopt;
}

std::optional<SubscriptionBindingStatus> parseSubscriptionStatus(const std::string& value) {
  if (value == "success") {
    return SubscriptionBindingStatus::kSuccess;
  }
  if (value == "rejected") {
    return SubscriptionBindingStatus::kRejected;
  }
  return std::nullopt;
}

std::optional<DeliveryStatus> parseDeliveryStatus(const std::string& value) {
  if (value == "succeeded") {
    return DeliveryStatus::kSucceeded;
  }
  if (value == "failed") {
    return DeliveryStatus::kFailed;
  }
  return std::nullopt;
}

std::optional<DeliveryErrorCode> parseDeliveryErrorCode(const std::string& value) {
  if (value == "none") {
    return DeliveryErrorCode::kNone;
  }
  if (value == "target_endpoint_unreachable") {
    return DeliveryErrorCode::kTargetEndpointUnreachable;
  }
  if (value == "serialization_error") {
    return DeliveryErrorCode::kSerializationError;
  }
  if (value == "schema_mismatch") {
    return DeliveryErrorCode::kSchemaMismatch;
  }
  if (value == "timeout") {
    return DeliveryErrorCode::kTimeout;
  }
  if (value == "unauthorized") {
    return DeliveryErrorCode::kUnauthorized;
  }
  return std::nullopt;
}

std::optional<FailureReason> parseFailureReason(const std::string& value) {
  if (value == "unknown") {
    return FailureReason::kUnknown;
  }
  if (value == "target_endpoint_unreachable") {
    return FailureReason::kTargetEndpointUnreachable;
  }
  if (value == "serialization_error") {
    return FailureReason::kSerializationError;
  }
  if (value == "schema_mismatch") {
    return FailureReason::kSchemaMismatch;
  }
  if (value == "timeout") {
    return FailureReason::kTimeout;
  }
  if (value == "unauthorized") {
    return FailureReason::kUnauthorized;
  }
  return std::nullopt;
}

}  // namespace

std::optional<RegisterTopicCommand> MsgServiceCommandMapper::map(const RegisterTopicRequestDto& dto) const {
  const auto topicState = parseTopicState(dto.topicState);
  if (!topicState.has_value()) {
    return std::nullopt;
  }

  RegisterTopicCommand command;
  command.topicDefinition = TopicDefinition{dto.topic,
                                            dto.domain,
                                            dto.payloadType,
                                            dto.qosProfile,
                                            *topicState,
                                            dto.ownerTeam,
                                            dto.schemaUri,
                                            dto.retentionMs};
  return command;
}

std::optional<RegisterSubscriptionCommand> MsgServiceCommandMapper::map(
    const RegisterSubscriptionRequestDto& dto) const {
  const auto status = parseSubscriptionStatus(dto.status);
  if (!status.has_value()) {
    return std::nullopt;
  }

  RegisterSubscriptionCommand command;
  command.binding = SubscriptionBinding{
      dto.subscriptionId, dto.topic, dto.subscriberEndpointId, *status, dto.statusReason};
  command.traceId = dto.traceId;
  command.recordedAtUtcMs = dto.recordedAtUtcMs;
  return command;
}

std::optional<RecordDeliveryCommand> MsgServiceCommandMapper::map(const RecordDeliveryRequestDto& dto) const {
  const auto status = parseDeliveryStatus(dto.status);
  const auto errorCode = parseDeliveryErrorCode(dto.errorCode);
  if (!status.has_value() || !errorCode.has_value()) {
    return std::nullopt;
  }

  RecordDeliveryCommand command;
  command.envelope = MessageEnvelope{dto.traceId, dto.topic, dto.payloadType, dto.schemaVersion};
  command.subscriber = SubscriptionBinding{"",
                                           dto.topic,
                                           dto.subscriberEndpointId,
                                           SubscriptionBindingStatus::kSuccess,
                                           ""};
  command.status = *status;
  command.errorCode = *errorCode;
  command.deliveredAtUtcMs = dto.deliveredAtUtcMs;
  return command;
}

std::optional<HandleDeliveryFailureCommand> MsgServiceCommandMapper::map(
    const HandleDeliveryFailureRequestDto& dto) const {
  const auto failureReason = parseFailureReason(dto.failureReason);
  if (!failureReason.has_value()) {
    return std::nullopt;
  }

  HandleDeliveryFailureCommand command;
  command.envelope = MessageEnvelope{dto.traceId, dto.topic, dto.payloadType, dto.schemaVersion};
  command.failureReason = *failureReason;
  command.retryCount = dto.retryCount;
  command.scheduledAtUtcMs = dto.scheduledAtUtcMs;
  command.lastAttemptUtcMs = dto.lastAttemptUtcMs;
  return command;
}

}  // namespace wp07_msgservice