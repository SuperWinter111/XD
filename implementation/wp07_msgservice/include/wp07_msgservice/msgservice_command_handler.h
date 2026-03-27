#pragma once

#include <optional>

#include "wp07_msgservice/msgservice_application_service.h"
#include "wp07_msgservice/msgservice_command_mapper.h"
#include "wp07_msgservice/msgservice_response_mapper.h"

namespace wp07_msgservice {

class MsgServiceCommandHandler {
 public:
  MsgServiceCommandHandler(MsgServiceCommandMapper& commandMapper,
                           MsgServiceResponseMapper& responseMapper,
                           MsgServiceApplicationService& applicationService);

  std::optional<bool> handle(const RegisterTopicRequestDto& dto) const;
  std::optional<RegisterSubscriptionResult> handle(const RegisterSubscriptionRequestDto& dto) const;
  std::optional<DeliveryReceipt> handle(const RecordDeliveryRequestDto& dto) const;
  std::optional<DeliveryFailureHandlingResult> handle(const HandleDeliveryFailureRequestDto& dto) const;

  RegisterTopicResponseDto handleRequest(const RegisterTopicRequestDto& dto) const;
  RegisterSubscriptionResponseDto handleRequest(const RegisterSubscriptionRequestDto& dto) const;
  RecordDeliveryResponseDto handleRequest(const RecordDeliveryRequestDto& dto) const;
  HandleDeliveryFailureResponseDto handleRequest(const HandleDeliveryFailureRequestDto& dto) const;

 private:
  MsgServiceCommandMapper& commandMapper_;
  MsgServiceResponseMapper& responseMapper_;
  MsgServiceApplicationService& applicationService_;
};

}  // namespace wp07_msgservice