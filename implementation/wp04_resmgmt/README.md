# WP04 ResMgmt 实现工程

本目录是 wp04_resmgmt 的独立实现工程。

## 1. 对应设计输入

1. ../../designArtifacts/delivery/workPackages/wp04_resmgmt/BMS_Work_Package_04_ResMgmt.md
2. ../../designArtifacts/delivery/workPackages/wp04_resmgmt/Payload_Checklist.md
3. ../../designArtifacts/delivery/workPackages/wp04_resmgmt/TODO.md
4. ../../designArtifacts/delivery/workPackages/wp04_resmgmt/STATUS.md

## 2. 当前工程范围

1. 平台注册与飞行状态汇总为 ResourceDescriptor 和 ResourceStateSnapshot。
2. 载荷/武器状态聚合为 CapabilityProfile。
3. AllocationRequest 裁定为 AllocationDecision。
4. reserve_only 场景输出 ReservationTicket。
5. link_quality 与 link_degraded 参与资源可用性修正。

## 3. 当前实现原则

1. ResMgmt 是 AllocationDecision 的唯一 owner。
2. accepted 不等于完全满足，部分满足单独显式建模。
3. DegradationAlert 仅作为裁定输入，不直接落成持续资源状态对象。