#pragma once

#include "wp07_msgservice/msgservice_application_service.h"
#include "wp07_msgservice/msgservice_entrypoint_dto.h"
#include "wp07_msgservice/msgservice_response_dto.h"

namespace wp07_msgservice {

class MsgServiceResponseMapper {
 public:
  RegisterTopicResponseDto invalidRegisterTopic(const RegisterTopicRequestDto& dto) const;
  RegisterTopicResponseDto mapRegisterTopic(const RegisterTopicRequestDto& dto, bool registered) const;

  RegisterSubscriptionResponseDto invalidRegisterSubscription(const RegisterSubscriptionRequestDto& dto) const;
  RegisterSubscriptionResponseDto mapRegisterSubscription(const RegisterSubscriptionRequestDto& dto,
                                                          const RegisterSubscriptionResult& result,
                                                          const SubscriptionBinding& binding) const;

  RecordDeliveryResponseDto invalidRecordDelivery(const RecordDeliveryRequestDto& dto) const;
  RecordDeliveryResponseDto mapRecordDelivery(const RecordDeliveryRequestDto& dto,
                                              const DeliveryReceipt& receipt) const;

  HandleDeliveryFailureResponseDto invalidHandleDeliveryFailure(const HandleDeliveryFailureRequestDto& dto) const;
  HandleDeliveryFailureResponseDto mapHandleDeliveryFailure(const HandleDeliveryFailureRequestDto& dto,
                                                            const DeliveryFailureHandlingResult& result) const;
};

}  // namespace wp07_msgservice