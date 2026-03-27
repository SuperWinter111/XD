#pragma once

#include <optional>

#include "wp07_msgservice/msgservice_entrypoint_dto.h"
#include "wp07_msgservice/msgservice_use_cases.h"

namespace wp07_msgservice {

class MsgServiceCommandMapper {
 public:
  std::optional<RegisterTopicCommand> map(const RegisterTopicRequestDto& dto) const;
  std::optional<RegisterSubscriptionCommand> map(const RegisterSubscriptionRequestDto& dto) const;
  std::optional<RecordDeliveryCommand> map(const RecordDeliveryRequestDto& dto) const;
  std::optional<HandleDeliveryFailureCommand> map(const HandleDeliveryFailureRequestDto& dto) const;
};

}  // namespace wp07_msgservice