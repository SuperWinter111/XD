#pragma once
#include "wp10_monitorlog/message_types.h"
namespace wp10_monitorlog::test_support {
inline DeliveryReceipt makeDeliveryReceipt() { return DeliveryReceipt{"trace-mon-001", "bms/core/ops/msg/delivery_receipt", true}; }
inline LinkQualitySnapshot makeLinkQualitySnapshot() { return LinkQualitySnapshot{"trace-mon-001", "link-001", 82}; }
inline DeadLetterRecord makeDeadLetterRecord() { return DeadLetterRecord{"trace-mon-002", "bms/core/ops/msg/dead_letter", "retry_exhausted"}; }
inline DegradationAlert makeDegradationAlert() { return DegradationAlert{"trace-mon-003", "link-003", "uav-001->cmd-001"}; }
inline SecurityEvent makeSecurityEvent() { return SecurityEvent{"trace-mon-001", "node-a", "critical"}; }
inline ReleaseEvent makeReleaseEvent() { return ReleaseEvent{"trace-mon-001", "release-001", "success"}; }
inline ReleaseEvent makeFailedReleaseEvent() { return ReleaseEvent{"trace-mon-004", "release-004", "rollback"}; }
}