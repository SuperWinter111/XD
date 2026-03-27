# WP04 ResMgmt 工程级 ICD 初版

## 1. 当前阶段

1. 当前版本：v0.2。
2. 当前用途：资源状态、能力画像、裁定与预留的模块完成版工程实现约束。
3. 冻结程度：模块完成待审核，可继续联调前置开发。

## 2. 当前冻结项

1. AllocationRequest 只表达需求与约束，不表达裁定结果。
2. AllocationDecision 必须显式区分 accepted、partial 和 reserve_only。
3. ReservationTicket 必须保留请求标识与有效时间窗。
4. link_degraded 只参与可用性修正，不替代 ResourceStateSnapshot。

## 3. 当前实现映射

1. ResourceRegistry：注册信息/飞行状态 -> ResourceDescriptor/ResourceStateSnapshot。
2. CapabilityAggregator：SensorState/WeaponState -> CapabilityProfile。
3. LinkImpactEvaluator：LinkQualitySnapshot/DegradationAlert -> AvailabilityImpact。
4. ConflictArbitrationService：请求规模与可用性 -> 仲裁原因。
5. ResourceSchedulingService：AllocationRequest -> AllocationDecision。
6. ReservationManager：预留裁定 -> ReservationTicket。

## 4. 当前验证状态

1. state_snapshot_test：验证 ResourceStateSnapshot 与 CapabilityProfile 聚合输出。
2. allocation_test：验证 accepted 正常裁定链路。
3. partial_test：验证 partial 与链路降级拒绝语义。
4. reservation_test：验证 reserve_only 到 ReservationTicket 输出。