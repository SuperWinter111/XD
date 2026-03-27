# WP08 KnowledgeRule Payload 核对表

## 1. 重点 payload

1. InferenceRequest。
2. RecommendationItem。
3. ReasonTrace。
4. RuleEvaluationResult。

## 2. 字段级核对重点

1. InferenceRequest：必须包含请求来源、上下文对象引用和 trace_id。
2. RecommendationItem：必须包含推荐结论、适用条件和来源规则标识。
3. ReasonTrace：必须表达推理链、命中规则和解释文本或结构化原因。
4. RuleEvaluationResult：必须保留规则命中与未命中的判定依据。

## 3. 常见错误

1. RecommendationItem 缺少来源规则标识。
2. 用 RecommendationItem 替代 ThreatAssessment。
3. ReasonTrace 只有文本没有结构化原因引用。
