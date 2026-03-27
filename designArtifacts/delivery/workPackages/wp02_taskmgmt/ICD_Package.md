# WP02 TaskMgmt ICD 设计包

## 1. 适用小组

1. 任务管理实现小组。
2. 负责 MissionCommand 入域、TaskConstraint、TaskPackage 和任务级重构逻辑的工程师或 agent。

## 2. 主工作包入口

1. [BMS_Work_Package_02_TaskMgmt.md](BMS_Work_Package_02_TaskMgmt.md)

## 3. 必读 Formal ICD

1. [BMS_ICD_Formal_02_Task_Battle_Execution_Closure.md](../../../icd/BMS_ICD_Formal_02_Task_Battle_Execution_Closure.md)
2. [BMS_ICD_Formal_03_Resource_Allocation_And_Reservation.md](../../../icd/BMS_ICD_Formal_03_Resource_Allocation_And_Reservation.md)
3. [BMS_ICD_Formal_06_Threat_Reasoning_And_Rule_Inference.md](../../../icd/BMS_ICD_Formal_06_Threat_Reasoning_And_Rule_Inference.md)

## 4. 必读补充设计文档

1. [BMS_Task_Plan_And_Exception_Semantics.md](../../../contracts/BMS_Task_Plan_And_Exception_Semantics.md)
2. [BMS_Integration_Matrix.md](../../BMS_Integration_Matrix.md)
3. [BMS_Core_Battle_Loop_Integration_Scenarios.md](../../BMS_Core_Battle_Loop_Integration_Scenarios.md)
4. [BMS_Execution_Index.md](../../BMS_Execution_Index.md)

## 5. 本组重点确认项

1. TaskConstraint 与 TaskPackage 是任务层权威对象。
2. TaskMgmt 不得越权直接生成 BattlePlan。
3. AllocationRequest 不等于 AllocationDecision。
4. 任务级重构与计划级调整边界必须清晰。

## 6. 交付前核对清单

1. command_received、decomposed、plan_created 三条主链已准备样例。
2. 场景 A、B、D 的任务边界已对齐。
3. trace_id 在任务闭环和重构路径中可追溯。

## 7. 重点 topic 清单

1. 发布：bms/core/command/task/command_received。
2. 发布：bms/core/command/task/decomposed。
3. 发布：bms/core/command/task/plan_created。
4. 发布：bms/core/command/resource/allocation_requested。
5. 订阅：bms/core/command/resource/allocation_committed。
6. 订阅：bms/edge/platform/event/mission_progress。
7. 订阅：bms/edge/platform/event/command_ack。
8. 订阅：bms/core/command/battle/effect_report。

## 8. 重点 payload 清单

1. MissionCommand。
2. TaskConstraint。
3. TaskPackage。
4. AllocationRequest。
5. AllocationDecision。
6. EngagementEffectReport。
7. RecommendationItem。

## 9. 样例与测试入口

1. [WP02 测试说明](../../../testAssets/workPackages/wp02_taskmgmt/README.md)
2. [Formal 02 样例目录](../../../testAssets/contract/formal02_task_battle_execution_closure)
3. [Formal 03 样例目录](../../../testAssets/contract/formal03_resource_allocation_and_reservation)
4. [主业务闭环追踪说明](../../../testAssets/integration/core_battle_loop/trace_scenario_a_normal.md)

## 10. 小组签收清单

1. 已签收任务层对象边界。
2. 已签收任务到资源申请主链样例。
3. 已确认不越权生成 BattlePlan。
4. 已确认重构与计划调整的分界条件。

## 11. 字段级核对表

1. [Payload_Checklist.md](Payload_Checklist.md)
