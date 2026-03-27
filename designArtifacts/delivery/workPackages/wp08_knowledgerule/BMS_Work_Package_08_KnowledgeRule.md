# BMS 工作包 08 KnowledgeRule

本文档是知识与规则分系统的可执行工作包，供软件工程师或 agent 直接领取并进入实现。

## 1. 基本信息

1. 分系统名称：KnowledgeRule。
2. 负责人类型：软件工程师或 agent。
3. 对应 Container：plantumlC4/C4_L2_Container.puml 中知识与规则分系统。
4. 对应 Component 图：plantumlC4/C4_L3_Component_08_KnowledgeRule.puml。
5. 对应 Code 图：plantumlC4/Code_07_KnowledgeRule.puml。
6. 对应正式 ICD：BMS_ICD_Formal_06。

## 2. 目标范围

1. 接收来自 SitMgmt、TaskMgmt、BattleCtrl 的推理请求，执行规则与知识推理。
2. 输出 RecommendationItem 与原因链，作为业务分系统的辅助决策输入。
3. 保证推荐结果解释可追踪、原因可审查。
4. 通过统一 query gateway 管理不同推理请求上下文。
5. 严格保持“推荐”与“权威业务对象”之间的边界。

不包含：

1. 直接发布 ThreatAssessment、TaskPackage、BattlePlan 等权威业务对象。
2. 态势融合与交战计划本体实现。
3. 前端视图聚合实现。

## 3. 对象边界

### 3.1 主拥有对象

1. InferenceRequest。
2. RecommendationItem。
3. ReasonTrace。
4. RuleEvaluationResult。

### 3.2 只读消费对象

1. TargetFeatureSnapshot。
2. ThreatAssessment。
3. TaskConstraint。
4. BattlePlan 上下文摘要。

### 3.3 禁止越权修改

1. 不得直接发布 ThreatAssessment。
2. 不得直接生成或改写 TaskPackage。
3. 不得直接生成或改写 BattlePlan。
4. 不得把推荐结果伪装成权威业务结论。

## 4. topic 责任

### 4.1 发布 topic

| topic | payload | 触发条件 | 下游 |
| --- | --- | --- | --- |
| bms/core/knowledge/inference/recommended | RecommendationItem | 完成规则推理与推荐组装 | SitMgmt, TaskMgmt, BattleCtrl |
| bms/core/knowledge/inference/reason_trace | ReasonTrace | 需要输出结构化解释 | MonitorLog, AuthAudit |

### 4.2 订阅 topic

| topic | payload | 上游 | 消费动作 |
| --- | --- | --- | --- |
| bms/core/knowledge/inference/requested | InferenceRequest | SitMgmt, TaskMgmt, BattleCtrl | 启动推理流程 |
| bms/core/situation/target/feature_snapshot | TargetFeatureSnapshot | SitMgmt | 丰富推理上下文 |
| bms/core/situation/threat/assessed | ThreatAssessment | SitMgmt | 提供当前威胁判断上下文 |

## 5. 模块拆分

| 模块 | 责任 | 输入 | 输出 |
| --- | --- | --- | --- |
| RequestContextBuilder | 整理不同来源的推理请求上下文 | InferenceRequest, TargetFeatureSnapshot | 规则执行上下文 |
| RuleExecutionEngine | 执行规则集与推理策略 | 规则执行上下文 | RuleEvaluationResult |
| RecommendationAssembler | 组装 RecommendationItem | RuleEvaluationResult | RecommendationItem |
| ReasonTraceService | 输出结构化解释与因果链 | RuleEvaluationResult | ReasonTrace |
| QueryGateway | 管理不同来源请求的统一入口 | InferenceRequest | 标准化请求 |

## 6. 实施步骤

1. 先实现 QueryGateway，统一 SitMgmt、TaskMgmt、BattleCtrl 的请求入口。
2. 实现 RuleExecutionEngine，打通 requested 到 recommended 主链。
3. 补齐 ReasonTraceService，输出可解释理由链。
4. 接入更多上下文对象，控制推荐结果边界。
5. 最后与 SitMgmt、TaskMgmt、BattleCtrl 完成联合验收。

## 7. 测试与验收

### 7.1 必备样例

1. 正常样例：InferenceRequest -> RecommendationItem。
2. 异常样例：规则无命中或规则冲突时输出空推荐或解释不足结果。
3. 边界样例：KnowledgeRule 不越权直接发布 ThreatAssessment 或 BattlePlan。

### 7.2 契约测试

1. InferenceRequest、RecommendationItem、ReasonTrace 必须符合 Formal 06。
2. 推荐对象必须保留来源理由与规则命中信息。
3. RecommendationItem 只能作为辅助输入，不得替代权威业务对象。
4. trace_id 必须贯穿 requested、recommended 与 reason_trace。

### 7.3 完成定义

1. Code_07_KnowledgeRule 的主模块已形成实现骨架。
2. requested 到 recommended 主链可验证。
3. 与 SitMgmt、TaskMgmt、BattleCtrl 的联调项已映射到联调矩阵。
4. 已准备主业务闭环场景 E 所需推荐样例。

## 8. 风险与待决项

1. 风险：规则来源增多后，优先级冲突和解释一致性会快速复杂化。
2. 风险：若输入上下文不完整，容易产生看似合理但不可执行的推荐结果。
3. 待决项：reason_trace 的最小披露粒度是否需要区分内部审查版与外部展示版。
