# WP01 BattleCtrl 测试资产说明

本目录用于说明 BattleCtrl 当前已落地的最小测试资产入口。

## 1. 当前映射

1. ../../contract/formal01_platform_execution_chain/
2. ../../contract/formal02_task_battle_execution_closure/
3. ../../contract/formal03_resource_allocation_and_reservation/
4. ../../integration/core_battle_loop/

## 2. 重点验证内容

1. 平台命令、command_ack 与 mission_progress 的执行链语义。
2. TaskPackage 与 BattlePlan 的边界。
3. AllocationDecision 只读消费原则。
4. 主业务闭环场景 A 的最短闭环链路。

## 3. 当前使用建议

1. 先阅读 Formal 01、02、03 的样例文件。
2. 再结合 ../../integration/core_battle_loop/trace_scenario_a_normal.md 验证 topic 顺序。
3. 若新增计划级调整或任务级重构样例，应继续归档到 BattleCtrl 对应目录说明中。
