# BMS 正式 ICD 专题 06 威胁理由与规则推理

本文档定义 ThreatAssessment 的结构化理由表达方式，以及 SitMgmt、TaskMgmt、BattleCtrl 与 KnowledgeRule 之间的规则推理接口约束。

## 1. 文档定位

本文档解决以下问题：

1. threat_reason 不再只停留于自由文本。
2. ThreatAssessment 如何同时承载人可读解释与结构化理由引用。
3. KnowledgeRule 如何通过 InferenceRequest 与 RecommendationItem 参与威胁判断解释。

本文档来源包括：

1. designArtifacts/icd/BMS_ICD_Formal_04_Situation_And_Threat.md
2. designArtifacts/icd/BMS_ICD_Formal_05_Target_Feature_And_Status_Extension.md
3. proto/bms/schema/situation.proto
4. proto/bms/schema/knowledge.proto
5. designArtifacts/contracts/BMS_DDS_Topic_Catalog.md

## 2. Topic 绑定

| topic | payload | 发布方 | 订阅方 | QoS |
| --- | --- | --- | --- | --- |
| bms/core/knowledge/inference/requested | bms.schema.knowledge.InferenceRequest | SitMgmt, TaskMgmt, BattleCtrl | KnowledgeRule | QOS-CMD |
| bms/core/knowledge/inference/recommended | bms.schema.knowledge.RecommendationItem | KnowledgeRule | SitMgmt, TaskMgmt, BattleCtrl | QOS-ALERT |
| bms/core/situation/threat/assessed | bms.schema.situation.ThreatAssessment | SitMgmt | BattleCtrl, HMI-BFF | QOS-ALERT |

## 3. ThreatAssessment 结构化理由

ThreatAssessment 当前正式结构扩展为：

```proto
message ThreatReasonRef {
  ThreatReasonCode reason_code = 1;
  string source_rule_or_template_id = 2;
  string evidence_ref = 3;
  double confidence = 4;
}

message ThreatAssessment {
  CommonHeader header = 1;
  string threat_id = 2;
  string track_id = 3;
  int32 threat_level = 4;
  int32 priority_rank = 5;
  string threat_reason = 6;
  repeated ThreatReasonRef reasons = 7;
}
```

规则：

1. threat_reason 继续承载人工可读摘要。
2. reasons 承载结构化理由引用。
3. 二者可以同时存在，但含义不同。

## 4. ThreatReasonCode 使用范围

当前标准理由码包括：

1. 高优先级目标。
2. 时敏目标。
3. 高机动目标。
4. 高威胁武器目标。
5. 防空威胁。
6. 任务目标相关。
7. 进入保护区域。
8. 行为升级。

说明：

1. 理由码用于支持检索、排序、解释一致性。
2. 理由码不是最终算法模型全集，可后续扩展。

## 5. KnowledgeRule 参与方式

### 5.1 InferenceRequest

InferenceRequest 用于请求规则或知识推理，其输入可包含：

1. FusedTrack 引用。
2. TargetFeatureSnapshot 引用。
3. TargetStatus 引用。
4. Doctrine 或模板上下文。

### 5.2 RecommendationItem

RecommendationItem 作为推理结果，可为 ThreatAssessment 提供：

1. source_rule_or_template_id。
2. summary。
3. confidence。

### 5.3 SitMgmt 的职责

1. SitMgmt 仍然拥有 ThreatAssessment 的最终发布权。
2. KnowledgeRule 只提供推荐与解释，不直接发布 ThreatAssessment 覆盖 SitMgmt。

## 6. HMI 与 BattleCtrl 的消费原则

1. HMI 应优先展示 threat_reason 文本摘要，再按需展开 reasons 明细。
2. BattleCtrl 可基于 reasons 中的 reason_code 做解释型排序或规则命中展示。
3. 不得仅根据单一 reason_code 直接生成交战命令。

## 7. 下一阶段建议

1. 为 target_source 建立标准码表。
2. 为 detection_method 建立标准码表。
3. 在需要时为 evidence_ref 定义统一引用格式。
