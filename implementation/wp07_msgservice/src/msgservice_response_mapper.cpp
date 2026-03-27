#include "wp07_msgservice/msgservice_response_mapper.h"

namespace wp07_msgservice {

RegisterTopicResponseDto MsgServiceResponseMapper::invalidRegisterTopic(const RegisterTopicRequestDto& dto) const {
  return {ResponseMetaDto{false, "invalid_argument", "invalid register topic request"}, false, dto.traceId, dto.topic};
}

RegisterTopicResponseDto MsgServiceResponseMapper::mapRegisterTopic(const RegisterTopicRequestDto& dto,
                                                                   bool registered) const {
  return {ResponseMetaDto{true,
                          registered ? "ok" : "register_topic_failed",
                          registered ? "topic registered" : "topic registration failed"},
          registered,
          dto.traceId,
          dto.topic};
}

RegisterSubscriptionResponseDto MsgServiceResponseMapper::invalidRegisterSubscription(
    const RegisterSubscriptionRequestDto& dto) const {
  RegisterSubscriptionResponseDto response;
  response.meta = ResponseMetaDto{false, "invalid_argument", "invalid register subscription request"};
  response.traceId = dto.traceId;
  response.subscriptionId = dto.subscriptionId;
  return response;
}

RegisterSubscriptionResponseDto MsgServiceResponseMapper::mapRegisterSubscription(
    const RegisterSubscriptionRequestDto& dto,
    const RegisterSubscriptionResult& result,
    const SubscriptionBinding& binding) const {
  RegisterSubscriptionResponseDto response;
  response.meta = ResponseMetaDto{true,
                                  result.registered ? "ok" : "register_subscription_failed",
                                  result.registered ? "subscription processed" : "subscription rejected by registry"};
  response.registered = result.registered;
  response.bindingEventPublished = result.bindingEvent.has_value();
  response.auditRecorded = result.auditRecord.has_value();
  response.traceId = dto.traceId;
  response.subscriptionId = dto.subscriptionId;
  response.auditRecordId = result.auditRecord.has_value() ? result.auditRecord->auditRecordId : "";
  response.bindingEventTopic = result.bindingEvent.has_value() ? result.bindingEvent->topic : "";
  response.subscriptionStatus = toString(binding.status);
  return response;
}

RecordDeliveryResponseDto MsgServiceResponseMapper::invalidRecordDelivery(const RecordDeliveryRequestDto& dto) const {
  RecordDeliveryResponseDto response;
  response.meta = ResponseMetaDto{false, "invalid_argument", "invalid record delivery request"};
  response.traceId = dto.traceId;
  response.topic = dto.topic;
  response.subscriberEndpointId = dto.subscriberEndpointId;
  return response;
}

RecordDeliveryResponseDto MsgServiceResponseMapper::mapRecordDelivery(const RecordDeliveryRequestDto& dto,
                                                                     const DeliveryReceipt& receipt) const {
  RecordDeliveryResponseDto response;
  response.meta = ResponseMetaDto{true, "ok", "delivery recorded"};
  response.traceId = dto.traceId;
  response.receiptId = receipt.receiptId;
  response.topic = receipt.topic;
  response.subscriberEndpointId = receipt.subscriberEndpointId;
  response.deliveryStatus = toString(receipt.status);
  response.errorCode = toString(receipt.errorCode);
  return response;
}

HandleDeliveryFailureResponseDto MsgServiceResponseMapper::invalidHandleDeliveryFailure(
    const HandleDeliveryFailureRequestDto& dto) const {
  HandleDeliveryFailureResponseDto response;
  response.meta = ResponseMetaDto{false, "invalid_argument", "invalid handle delivery failure request"};
  response.traceId = dto.traceId;
  return response;
}

HandleDeliveryFailureResponseDto MsgServiceResponseMapper::mapHandleDeliveryFailure(
    const HandleDeliveryFailureRequestDto& dto,
    const DeliveryFailureHandlingResult& result) const {
  HandleDeliveryFailureResponseDto response;
  response.meta = ResponseMetaDto{true, "ok", "delivery failure processed"};
  response.traceId = dto.traceId;
  response.scheduleId = result.retryScheduleEntry.has_value() ? result.retryScheduleEntry->scheduleId : "";
  response.deadLetterId = result.deadLetterRecord.has_value() ? result.deadLetterRecord->deadLetterId : "";
  response.retryDecision = result.retryPlan.decision == RetryDecision::kRetryScheduled ? "retry_scheduled" : "dead_lettered";
  response.retryScheduled = result.retryScheduleEntry.has_value();
  response.deadLettered = result.deadLetterRecord.has_value();
  response.failureReason = toString(result.retryPlan.failureReason);
  return response;
}

}  // namespace wp07_msgservice