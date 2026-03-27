# WP04 ResMgmt Payload 核对表

## 1. 重点 payload

1. ResourceStateSnapshot。
2. CapabilityProfile。
3. AllocationRequest。
4. AllocationDecision。
5. ReservationTicket。

## 2. 字段级核对重点

1. ResourceStateSnapshot：必须能标识资源、状态时间点和可用性。
2. CapabilityProfile：能力字段必须和平台、载荷、武器状态来源区分清楚。
3. AllocationRequest：只能表达需求与约束，不表达裁定结果。
4. AllocationDecision：必须显式表达 accepted、部分满足、预留和拒绝原因。
5. ReservationTicket：必须包含预留对象、有效时间窗和关联请求标识。

## 3. 常见错误

1. 用 accepted=true 推断完全满足。
2. 混淆 allocated_resource_ids 与 reserved_resource_ids。
3. 用链路事件直接替代资源状态快照。
