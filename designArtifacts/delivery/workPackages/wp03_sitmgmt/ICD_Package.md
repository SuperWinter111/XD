# WP03 SitMgmt ICD 设计包

## 1. 适用小组

1. 态势管理实现小组。
2. 负责 FusedTrack、ThreatAssessment、SituationSnapshot 等对象的工程师或 agent。

## 2. 主工作包入口

1. [BMS_Work_Package_03_SitMgmt.md](BMS_Work_Package_03_SitMgmt.md)

## 3. 必读 Formal ICD

1. [BMS_ICD_Formal_04_Situation_And_Threat.md](../../../icd/BMS_ICD_Formal_04_Situation_And_Threat.md)
2. [BMS_ICD_Formal_05_Target_Feature_And_Status_Extension.md](../../../icd/BMS_ICD_Formal_05_Target_Feature_And_Status_Extension.md)
3. [BMS_ICD_Formal_06_Threat_Reasoning_And_Rule_Inference.md](../../../icd/BMS_ICD_Formal_06_Threat_Reasoning_And_Rule_Inference.md)
4. [BMS_ICD_Formal_09_Simulation_And_Training_Integration.md](../../../icd/BMS_ICD_Formal_09_Simulation_And_Training_Integration.md)

## 4. 必读补充设计文档

1. [BMS_Integration_Matrix.md](../../BMS_Integration_Matrix.md)
2. [BMS_Core_Battle_Loop_Integration_Scenarios.md](../../BMS_Core_Battle_Loop_Integration_Scenarios.md)
3. [BMS_Execution_Index.md](../../BMS_Execution_Index.md)

## 5. 本组重点确认项

1. FusedTrack 是事实观测对象。
2. ThreatAssessment 是判断对象，不是命令对象。
3. RecommendationItem 只能作为辅助输入。
4. TargetTruth 不得冒充真实融合态势。

## 6. 交付前核对清单

1. fused_track 与 threat_assessed 主链已准备样例。
2. Feature 扩展字段与状态扩展字段已对齐 Formal 05。
3. 场景 E 的输入、输出与 trace_id 已对齐。

## 7. 重点 topic 清单

1. 发布：bms/core/situation/fused_track。
2. 发布：bms/core/situation/threat/assessed。
3. 发布：bms/core/situation/snapshot。
4. 发布：bms/core/situation/summary_generated。
5. 订阅：edge.payload/perception/*。
6. 订阅：bms/simulation/payload/target_truth。
7. 订阅：bms/core/knowledge/inference/recommended。

## 8. 重点 payload 清单

1. FusedTrack。
2. ThreatAssessment。
3. SituationSnapshot。
4. SituationSummaryReport。
5. TargetFeatureSnapshot。
6. TargetStatus。
7. RecommendationItem。
8. TargetTruth。

## 9. 样例与测试入口

1. [Formal 04 样例基线](../../BMS_Contract_Test_Baseline.md)
2. [Formal 05 样例基线](../../BMS_Contract_Test_Baseline.md)
3. [Formal 06 样例基线](../../BMS_Contract_Test_Baseline.md)
4. [Formal 09 样例基线](../../BMS_Contract_Test_Baseline.md)
5. [主业务闭环场景 E](../../BMS_Core_Battle_Loop_Integration_Scenarios.md)

## 10. 小组签收清单

1. 已签收态势对象与推理对象边界。
2. 已签收感知、融合、威胁评估主链。
3. 已确认仿真输入不冒充真实态势。

## 11. 字段级核对表

1. [Payload_Checklist.md](Payload_Checklist.md)
