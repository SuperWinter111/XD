# WP08 KnowledgeRule 工程级 ICD 初版

## 1. 当前阶段

1. 当前版本：v0.2。
2. 当前用途：推理请求、推荐输出与解释链的模块完成版工程实现约束。
3. 冻结程度：模块完成待审核，可继续联调前置开发。

## 2. 当前冻结项

1. InferenceRequest 必须保留 sourceSubsystem、contextRef 和 traceId。
2. RecommendationItem 必须保留 recommendationId、recommendedAction 和 sourceRuleId。
3. ReasonTrace 必须保留 ruleChain 和 explanation。
4. 推荐输出不替代 ThreatAssessment、TaskPackage、BattlePlan。

## 3. 当前实现映射

1. QueryGateway：InferenceRequest 归一入口。
2. RequestContextBuilder：InferenceRequest + 上下文对象 -> QueryContext。
3. RuleExecutionEngine：QueryContext -> RuleEvaluationResult。
4. RecommendationAssembler：RuleEvaluationResult -> RecommendationItem。
5. ReasonTraceService：RuleEvaluationResult + RecommendationItem -> ReasonTrace。

## 4. 当前验证状态

1. recommendation_test：验证 inference_requested 到 recommended 主链。
2. reason_trace_test：验证结构化解释链输出。
3. conflict_test：验证无命中上下文下的保守推荐路径。
4. boundary_test：验证 RecommendationItem 不越权替代 ThreatAssessment。