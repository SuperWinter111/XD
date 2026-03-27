# BMS 契约测试基线

本文档用于为正式 ICD 和跨分系统 topic 提供统一的契约测试最小集合，确保“可追踪、可验证、可 mock”从设计原则落到可执行测试输入。

## 1. 适用范围

本文档适用于：

1. 所有正式 ICD 专题文档。
2. 所有跨分系统 topic。
3. 所有工作包中的正常样例、异常样例、拒绝样例与回归样例。

## 2. 通用必测项

每条跨分系统链路至少必须验证：

1. topic 名称与 DDS 目录一致。
2. payload 类型与 schema 绑定一致。
3. 关键字段语义与正式 ICD 一致。
4. trace_id 可贯通上游、下游与回执。
5. owner rule 未被破坏。
6. 正常路径与异常路径至少各 1 套。

## 3. 按正式 ICD 分组的最小测试集

### 3.1 Formal 01 平台执行链

1. 正常样例：平台命令 -> CommandAck.accepted -> MissionProgress -> PlatformAlert 无异常。
2. 拒绝样例：禁飞区、模式不可切换或平台离线 -> CommandAck.rejected。
3. 边界样例：CommandAck 表示受理，不表示执行完成。

### 3.2 Formal 02 任务-交战-执行闭环

1. 正常样例：TaskPackage -> BattlePlan -> ExecutionStateSnapshot -> EngagementEffectReport。
2. 异常样例：ExecutionException 触发计划级调整或任务重构。
3. 边界样例：TaskMgmt 不越权直接生成 BattlePlan。

### 3.3 Formal 03 资源分配与预留

1. 正常样例：AllocationRequest -> AllocationDecision.accepted。
2. 预留样例：reserve_only -> ReservationTicket 或 reserved_resource_ids。
3. 边界样例：AllocationRequest 不等于 AllocationDecision。

### 3.4 Formal 04 态势与威胁

1. 正常样例：感知输入 -> FusedTrack -> ThreatAssessment。
2. 异常样例：观测不足或置信度下降 -> ThreatAssessment 降级或理由不足。
3. 边界样例：ThreatAssessment 不直接生成交战命令。

### 3.5 Formal 05 目标特征与状态扩展

1. 正常样例：目标特征快照、状态快照完整对齐。
2. 异常样例：特征缺失或来源冲突时的降级策略。
3. 边界样例：TargetFeatureSnapshot 不等于知识域 TargetFeatureProfile。

### 3.6 Formal 06 威胁理由与规则推理

1. 正常样例：InferenceRequest -> RecommendationItem -> ThreatAssessment 引用 reasons。
2. 异常样例：规则冲突或无命中 -> 推荐为空或解释不足。
3. 边界样例：KnowledgeRule 不越权发布 ThreatAssessment。

### 3.7 Formal 07 通信链路与安全事件

1. 正常样例：link_quality 正常发布。
2. 异常样例：link_degraded 或 security_event 触发。
3. 边界样例：DegradationAlert 是事件，不是持续状态对象。

### 3.8 Formal 08 消息治理与投递契约

1. 正常样例：topic_defined -> delivery_receipt.success。
2. 异常样例：重试失败 -> dead_letter。
3. 边界样例：DeliveryReceipt 仅表达投递结果，不表达业务处理完成。

### 3.9 Formal 09 仿真训练接口

1. 正常样例：clock_tick + SimFlightState 注入 EnhanceUnit。
2. 异常样例：仿真时间漂移或场景控制异常。
3. 边界样例：TargetTruth 不冒充真实融合态势。

### 3.10 Formal 10 运维审计与监控

1. 正常样例：audit_event、monitor_alert 正常发布。
2. 异常样例：安全事件或告警升级链路。
3. 边界样例：监控与审计对象不反写业务主域。

### 3.11 Formal 11 BFF 聚合与 UI 推送

1. 正常样例：dashboard 推送、alert_stream 推送。
2. 异常样例：订阅恢复或重连恢复。
3. 边界样例：BFF 只读聚合，不反写业务主对象。

## 4. 每个工作包至少要交的测试件

1. 1 套正常样例。
2. 1 套异常样例。
3. 1 套边界负样例。
4. 如涉及回执、重试、降级、重构、裁决，则额外提供对应样例。

## 5. 验收要求

1. 契约测试样例必须能映射到正式 ICD 编号。
2. 契约测试样例必须能映射到联调矩阵中的上下游链路。
3. 契约测试样例必须能在工作包中找到归属。
4. 若 topic、schema、ownership 发生变化，必须回归受影响的测试组。
