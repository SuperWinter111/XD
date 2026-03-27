# WP01 BattleCtrl ICD 设计包

## 1. 适用小组

1. 交战管控实现小组。
2. 负责 BattlePlan、plan_updated、effect_report 以及任务边界内调整逻辑的工程师或 agent。

## 2. 主工作包入口

1. [BMS_Work_Package_01_BattleCtrl.md](BMS_Work_Package_01_BattleCtrl.md)

## 3. 必读 Formal ICD

1. [BMS_ICD_Formal_01_Platform_Execution_Chain.md](../../../icd/BMS_ICD_Formal_01_Platform_Execution_Chain.md)
2. [BMS_ICD_Formal_02_Task_Battle_Execution_Closure.md](../../../icd/BMS_ICD_Formal_02_Task_Battle_Execution_Closure.md)
3. [BMS_ICD_Formal_03_Resource_Allocation_And_Reservation.md](../../../icd/BMS_ICD_Formal_03_Resource_Allocation_And_Reservation.md)
4. [BMS_ICD_Formal_04_Situation_And_Threat.md](../../../icd/BMS_ICD_Formal_04_Situation_And_Threat.md)
5. [BMS_ICD_Formal_06_Threat_Reasoning_And_Rule_Inference.md](../../../icd/BMS_ICD_Formal_06_Threat_Reasoning_And_Rule_Inference.md)
6. [BMS_ICD_Formal_07_Comm_Link_And_Security.md](../../../icd/BMS_ICD_Formal_07_Comm_Link_And_Security.md)

## 4. 必读补充设计文档

1. [BMS_Task_Plan_And_Exception_Semantics.md](../../../contracts/BMS_Task_Plan_And_Exception_Semantics.md)
2. [BMS_Integration_Matrix.md](../../BMS_Integration_Matrix.md)
3. [BMS_Core_Battle_Loop_Integration_Scenarios.md](../../BMS_Core_Battle_Loop_Integration_Scenarios.md)
4. [BMS_Execution_Index.md](../../BMS_Execution_Index.md)

## 5. 本组重点确认项

1. BattlePlan 与 TaskPackage 的语义边界。
2. plan_updated 只能在 TaskConstraint 仍成立时发生。
3. AllocationDecision 只能被消费，不得被越权改写。
4. command_ack 只表示受理，不表示执行完成。
5. effect_report 必须能回接任务闭环。

## 6. 交付前核对清单

1. plan_created 与 plan_updated 两条链路已分别映射到样例。
2. BattleCtrl 对 SitMgmt、ResMgmt、EnhanceUnit、TaskMgmt 的输入边界已核对。
3. 场景 A、C、D 的 topic 顺序已与联调基线对齐。

## 7. 重点 topic 清单

1. 发布：bms/core/command/battle/plan_created。
2. 发布：bms/core/command/battle/plan_updated。
3. 发布：bms/core/command/battle/effect_report。
4. 订阅：bms/core/command/task/decomposed。
5. 订阅：bms/core/command/task/plan_created。
6. 订阅：bms/core/command/resource/allocation_committed。
7. 订阅：bms/core/situation/fused_track。
8. 订阅：bms/core/situation/threat/assessed。
9. 订阅：bms/edge/platform/event/command_ack。
10. 订阅：bms/edge/platform/event/mission_progress。

## 8. 重点 payload 清单

1. BattlePlan。
2. EngagementEffectReport。
3. TaskConstraint。
4. TaskPackage。
5. AllocationDecision。
6. FusedTrack。
7. ThreatAssessment。
8. CommandAck。
9. MissionProgress。

## 9. 样例与测试入口

1. [WP01 测试说明](../../../testAssets/workPackages/wp01_battlectrl/README.md)
2. [Formal 01 样例目录](../../../testAssets/contract/formal01_platform_execution_chain)
3. [Formal 02 样例目录](../../../testAssets/contract/formal02_task_battle_execution_closure)
4. [Formal 03 样例目录](../../../testAssets/contract/formal03_resource_allocation_and_reservation)
5. [主业务闭环追踪说明](../../../testAssets/integration/core_battle_loop/trace_scenario_a_normal.md)

## 10. 小组签收清单

1. 已签收主工作包文档。
2. 已签收必读 Formal ICD 原文。
3. 已签收 topic 和 payload 清单。
4. 已签收最小样例入口。
5. 已确认上下游联调对象。

## 11. 字段级核对表

1. [Payload_Checklist.md](Payload_Checklist.md)
