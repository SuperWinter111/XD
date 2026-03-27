# WP08 KnowledgeRule ICD 设计包

## 1. 适用小组

1. 知识与规则实现小组。
2. 负责推理请求、规则解释和推荐输出的工程师或 agent。

## 2. 主工作包入口

1. [BMS_Work_Package_08_KnowledgeRule.md](BMS_Work_Package_08_KnowledgeRule.md)

## 3. 必读 Formal ICD

1. [BMS_ICD_Formal_06_Threat_Reasoning_And_Rule_Inference.md](../../../icd/BMS_ICD_Formal_06_Threat_Reasoning_And_Rule_Inference.md)

## 4. 必读补充设计文档

1. [BMS_Integration_Matrix.md](../../BMS_Integration_Matrix.md)
2. [BMS_Execution_Index.md](../../BMS_Execution_Index.md)

## 5. 本组重点确认项

1. InferenceRequest、RecommendationItem、ReasonTrace 的边界。
2. RecommendationItem 只能作为辅助输入。
3. 不得越权直接发布 ThreatAssessment、TaskPackage 或 BattlePlan。

## 6. 交付前核对清单

1. requested、recommended、reason_trace 样例已准备。
2. 推荐结果与解释链可追溯。
3. 与 SitMgmt、TaskMgmt、BattleCtrl 的消费边界已核对。

## 7. 重点 topic 清单

1. 发布：bms/core/knowledge/inference/recommended。
2. 发布：bms/core/knowledge/inference/reason_trace。
3. 订阅：bms/core/knowledge/inference/requested。
4. 订阅：bms/core/situation/target/feature_snapshot。
5. 订阅：bms/core/situation/threat/assessed。

## 8. 重点 payload 清单

1. InferenceRequest。
2. RecommendationItem。
3. ReasonTrace。
4. RuleEvaluationResult。

## 9. 样例与测试入口

1. [Formal 06 样例基线](../../BMS_Contract_Test_Baseline.md)
2. [主业务闭环场景 E](../../BMS_Core_Battle_Loop_Integration_Scenarios.md)

## 10. 小组签收清单

1. 已签收推荐与权威对象边界。
2. 已签收解释链输出要求。
3. 已确认不越权发布业务主对象。

## 11. 字段级核对表

1. [Payload_Checklist.md](Payload_Checklist.md)
