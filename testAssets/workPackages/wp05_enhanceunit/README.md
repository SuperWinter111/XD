# WP05 EnhanceUnit 测试资产说明

本目录用于说明 EnhanceUnit 当前已落地的最小测试资产入口。

## 1. 当前映射

1. ../../contract/formal01_platform_execution_chain/
2. ../../integration/core_battle_loop/

## 2. 重点验证内容

1. BattlePlan 下发后的平台命令受理与执行进度回传。
2. command_ack.accepted 与 command_ack.rejected 的语义差异。
3. mission_progress 与 platform_alert 的反馈边界。
4. EnhanceUnit 作为边缘桥接层，不越权生成任务或交战对象。

## 3. 当前使用建议

1. 先阅读 Formal 01 的正常、拒绝和边界样例。
2. 再结合 ../../integration/core_battle_loop/trace_scenario_a_normal.md 校核命令回传链。
3. Formal 09 的仿真样例当前尚未在本目录落地，后续补齐时应在此处追加入口说明。
