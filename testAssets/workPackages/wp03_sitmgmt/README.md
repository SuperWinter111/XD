# WP03 SitMgmt 测试资产说明

本目录用于说明 SitMgmt 当前应对接的最小测试资产入口。

## 1. 当前映射

1. ../../integration/core_battle_loop/
2. ../../contract/formal04_situation_and_threat/
3. ../../contract/formal05_target_feature_and_status_extension/
4. ../../contract/formal06_threat_reasoning_and_rule_inference/
5. ../../contract/formal09_simulation_and_training_integration/

## 2. 重点验证内容

1. raw target 到 fused_track 的事实观测链路。
2. fused_track 到 threat_assessed 的判断链路。
3. RecommendationItem 作为辅助输入的边界。
4. TargetTruth 不冒充真实融合态势。

## 3. 当前使用建议

1. 先按 [designArtifacts/delivery/BMS_Contract_Test_Baseline.md](../../../designArtifacts/delivery/BMS_Contract_Test_Baseline.md) 中 Formal 04、05、06、09 基线准备样例。
2. 再结合 [designArtifacts/delivery/BMS_Core_Battle_Loop_Integration_Scenarios.md](../../../designArtifacts/delivery/BMS_Core_Battle_Loop_Integration_Scenarios.md) 的场景 E 规划联调输入输出。
