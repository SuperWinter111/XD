# WP04 ResMgmt ICD 设计包

## 1. 适用小组

1. 资源管理实现小组。
2. 负责 AllocationDecision、ResourceStateSnapshot、ReservationTicket 的工程师或 agent。

## 2. 主工作包入口

1. [BMS_Work_Package_04_ResMgmt.md](BMS_Work_Package_04_ResMgmt.md)

## 3. 必读 Formal ICD

1. [BMS_ICD_Formal_03_Resource_Allocation_And_Reservation.md](../../../icd/BMS_ICD_Formal_03_Resource_Allocation_And_Reservation.md)
2. [BMS_ICD_Formal_07_Comm_Link_And_Security.md](../../../icd/BMS_ICD_Formal_07_Comm_Link_And_Security.md)

## 4. 必读补充设计文档

1. [BMS_Integration_Matrix.md](../../BMS_Integration_Matrix.md)
2. [BMS_Core_Battle_Loop_Integration_Scenarios.md](../../BMS_Core_Battle_Loop_Integration_Scenarios.md)
3. [BMS_Execution_Index.md](../../BMS_Execution_Index.md)

## 5. 本组重点确认项

1. AllocationDecision 是唯一资源裁定权威结果。
2. accepted 不等于完全满足。
3. reserve_only 与即时分配必须区分。
4. 链路质量只能影响裁定，不得替代裁定对象。

## 6. 交付前核对清单

1. state_snapshot、allocation_committed、reservation_updated 已准备样例。
2. 场景 A、B、C 的资源边界已完成核对。
3. LinkQualitySnapshot 与 DegradationAlert 的使用边界已验证。

## 7. 重点 topic 清单

1. 发布：bms/core/resource/state_snapshot。
2. 发布：bms/core/command/resource/allocation_committed。
3. 发布：bms/core/resource/reservation_updated。
4. 订阅：bms/core/command/resource/allocation_requested。
5. 订阅：bms/edge/platform/event/platform_registered。
6. 订阅：bms/core/ops/comm/link_quality。
7. 订阅：bms/core/ops/comm/link_degraded。

## 8. 重点 payload 清单

1. ResourceStateSnapshot。
2. CapabilityProfile。
3. AllocationRequest。
4. AllocationDecision。
5. ReservationTicket。
6. LinkQualitySnapshot。
7. DegradationAlert。

## 9. 样例与测试入口

1. [WP04 测试说明](../../../testAssets/workPackages/wp04_resmgmt/README.md)
2. [Formal 03 样例目录](../../../testAssets/contract/formal03_resource_allocation_and_reservation)
3. [主业务闭环追踪说明](../../../testAssets/integration/core_battle_loop/trace_scenario_a_normal.md)

## 10. 小组签收清单

1. 已签收资源裁定权威边界。
2. 已签收部分满足与预留语义。
3. 已确认链路质量只影响裁定，不替代裁定结果。

## 11. 字段级核对表

1. [Payload_Checklist.md](Payload_Checklist.md)
