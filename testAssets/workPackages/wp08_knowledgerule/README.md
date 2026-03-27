# WP08 KnowledgeRule 测试资产说明

本目录用于说明 KnowledgeRule 当前应对接的最小测试资产入口。

## 1. 当前映射

1. ../../contract/formal06_threat_reasoning_and_rule_inference/
2. ../../integration/core_battle_loop/ 中场景 E 的联调基线。

## 2. 重点验证内容

1. inference_requested 到 recommended 的主链。
2. 规则冲突或无命中时的异常路径。
3. reason_trace 的解释链输出。
4. RecommendationItem 不越权替代权威业务对象。

## 3. 当前使用建议

1. 先按 [designArtifacts/delivery/BMS_Contract_Test_Baseline.md](../../../designArtifacts/delivery/BMS_Contract_Test_Baseline.md) 中 Formal 06 基线准备样例。
2. 再对齐 [designArtifacts/delivery/BMS_Core_Battle_Loop_Integration_Scenarios.md](../../../designArtifacts/delivery/BMS_Core_Battle_Loop_Integration_Scenarios.md) 中场景 E 的输入输出。
