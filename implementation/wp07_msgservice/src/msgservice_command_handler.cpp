#include "wp07_msgservice/msgservice_command_handler.h"

namespace wp07_msgservice {

MsgServiceCommandHandler::MsgServiceCommandHandler(MsgServiceCommandMapper& commandMapper,
                           MsgServiceResponseMapper& responseMapper,
                                                   MsgServiceApplicationService& applicationService)
  : commandMapper_(commandMapper), responseMapper_(responseMapper), applicationService_(applicationService) {}

std::optional<bool> MsgServiceCommandHandler::handle(const RegisterTopicRequestDto& dto) const {
  const auto command = commandMapper_.map(dto);
  if (!command.has_value()) {
    return std::nullopt;
  }

  return applicationService_.registerTopic(*command);
}

std::optional<RegisterSubscriptionResult> MsgServiceCommandHandler::handle(
    const RegisterSubscriptionRequestDto& dto) const {
  const auto command = commandMapper_.map(dto);
  if (!command.has_value()) {
    return std::nullopt;
  }

  return applicationService_.registerSubscription(*command);
}

std::optional<DeliveryReceipt> MsgServiceCommandHandler::handle(const RecordDeliveryRequestDto& dto) const {
  const auto command = commandMapper_.map(dto);
  if (!command.has_value()) {
    return std::nullopt;
  }

  return applicationService_.recordDelivery(*command);
}

std::optional<DeliveryFailureHandlingResult> MsgServiceCommandHandler::handle(
    const HandleDeliveryFailureRequestDto& dto) const {
  const auto command = commandMapper_.map(dto);
  if (!command.has_value()) {
    return std::nullopt;
  }

  return applicationService_.handleDeliveryFailure(*command);
}

RegisterTopicResponseDto MsgServiceCommandHandler::handleRequest(const RegisterTopicRequestDto& dto) const {
  const auto command = commandMapper_.map(dto);
  if (!command.has_value()) {
    return responseMapper_.invalidRegisterTopic(dto);
  }

  return responseMapper_.mapRegisterTopic(dto, applicationService_.registerTopic(*command));
}

RegisterSubscriptionResponseDto MsgServiceCommandHandler::handleRequest(
    const RegisterSubscriptionRequestDto& dto) const {
  const auto command = commandMapper_.map(dto);
  if (!command.has_value()) {
    return responseMapper_.invalidRegisterSubscription(dto);
  }

  const auto result = applicationService_.registerSubscription(*command);
  return responseMapper_.mapRegisterSubscription(dto, result, command->binding);
}

RecordDeliveryResponseDto MsgServiceCommandHandler::handleRequest(const RecordDeliveryRequestDto& dto) const {
  const auto command = commandMapper_.map(dto);
  if (!command.has_value()) {
    return responseMapper_.invalidRecordDelivery(dto);
  }

  return responseMapper_.mapRecordDelivery(dto, applicationService_.recordDelivery(*command));
}

HandleDeliveryFailureResponseDto MsgServiceCommandHandler::handleRequest(
    const HandleDeliveryFailureRequestDto& dto) const {
  const auto command = commandMapper_.map(dto);
  if (!command.has_value()) {
    return responseMapper_.invalidHandleDeliveryFailure(dto);
  }

  return responseMapper_.mapHandleDeliveryFailure(dto, applicationService_.handleDeliveryFailure(*command));
}

}  // namespace wp07_msgservice