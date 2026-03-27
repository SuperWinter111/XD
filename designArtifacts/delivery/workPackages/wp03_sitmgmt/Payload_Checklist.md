# WP03 SitMgmt Payload 核对表

## 1. 重点 payload

1. FusedTrack。
2. ThreatAssessment。
3. SituationSnapshot。
4. TargetFeatureSnapshot。
5. TargetStatus。
6. RecommendationItem。
7. TargetTruth。

## 2. 字段级核对重点

1. FusedTrack：必须保留目标标识、来源、置信度和时空位置。
2. ThreatAssessment：必须区分事实输入、威胁等级和 reasons/依据字段。
3. TargetFeatureSnapshot 与 TargetStatus：扩展字段必须与 Formal 05 对齐。
4. RecommendationItem：必须带来源规则和解释，不得直接冒充 ThreatAssessment。
5. TargetTruth：必须显式标识仿真来源，不能与真实态势对象混用。

## 3. 常见错误

1. 把 RecommendationItem 当成权威态势对象。
2. 用 TargetTruth 替代真实融合输出。
3. 在 ThreatAssessment 中缺失 reasons 导致不可解释。
