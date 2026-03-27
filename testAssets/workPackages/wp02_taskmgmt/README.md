# WP02 TaskMgmt 测试资产说明

本目录用于说明 TaskMgmt 当前已落地的最小测试资产入口。

## 1. 当前映射

1. ../../contract/formal02_task_battle_execution_closure/
2. ../../contract/formal03_resource_allocation_and_reservation/
3. ../../integration/core_battle_loop/

## 2. 重点验证内容

1. MissionCommand 入域、TaskConstraint 拆解与 TaskPackage 输出链路。
2. AllocationRequest 与 AllocationDecision 的语义边界。
3. 主业务闭环中 TaskMgmt 不越权直接生成 BattlePlan。
4. 任务级重构与计划级调整的分界条件。

## 3. 当前使用建议

1. 先阅读 Formal 02 的正常、异常和边界样例。
2. 再阅读 Formal 03 的资源裁定样例，确认 TaskMgmt 的消费边界。
3. 最后结合 ../../integration/core_battle_loop/trace_scenario_a_normal.md 复核最短主链。
