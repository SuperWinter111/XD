# WP08 KnowledgeRule 实现工程

本目录是 wp08_knowledgerule 的独立实现工程。

## 1. 对应设计输入

1. ../../designArtifacts/delivery/workPackages/wp08_knowledgerule/BMS_Work_Package_08_KnowledgeRule.md
2. ../../designArtifacts/delivery/workPackages/wp08_knowledgerule/Payload_Checklist.md
3. ../../designArtifacts/delivery/workPackages/wp08_knowledgerule/TODO.md
4. ../../designArtifacts/delivery/workPackages/wp08_knowledgerule/STATUS.md

## 2. 当前工程范围

1. InferenceRequest 统一入口归一。
2. 请求上下文构建与规则执行主链。
3. RecommendationItem 与 ReasonTrace 输出。
4. 无命中上下文下的保守推荐路径。

## 3. 当前实现原则

1. KnowledgeRule 只输出辅助推荐对象，不越权发布 ThreatAssessment 或 BattlePlan。
2. RecommendationItem 保留 sourceRuleId。
3. ReasonTrace 保留结构化规则链。