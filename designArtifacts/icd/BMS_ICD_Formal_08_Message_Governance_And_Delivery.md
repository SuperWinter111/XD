# BMS 正式 ICD 专题 08 消息治理与投递契约

本文档定义 MsgService 在主题定义、消息包络、订阅登记、投递回执与死信治理方面的正式 ICD 约束。

## 1. 文档定位

本文档覆盖以下对象：

1. TopicDefinition。
2. EndpointBinding。
3. SchemaDescriptor。
4. MessageEnvelope。
5. SubscriptionBinding。
6. DeliveryReceipt。
7. DeadLetterRecord。
8. SubscriptionBindingAuditRecord。
9. RetryScheduleEntry。

## 2. Topic 绑定

| topic | payload | 发布方 | 订阅方 | QoS |
| --- | --- | --- | --- | --- |
| bms/core/ops/msg/topic_defined | bms.schema.message.TopicDefinition | MsgService | MonitorLog | QOS-ALERT |
| bms/core/ops/msg/subscription_bound | bms.schema.message.SubscriptionBinding | MsgService | MonitorLog, 业务分系统 | QOS-STATE |
| bms/core/ops/msg/delivery_receipt | bms.schema.message.DeliveryReceipt | MsgService | MonitorLog, 发布者 | QOS-STATE |
| bms/core/ops/msg/dead_letter | bms.schema.message.DeadLetterRecord | MsgService | MonitorLog | QOS-ALERT |

## 3. 核心对象语义

### 3.1 TopicDefinition

TopicDefinition 是系统级主题登记对象，约束 topic、payload_type、QoS、发布者、订阅者，以及工程治理字段 topic_state、owner_team、schema_uri、retention_ms。

### 3.2 MessageEnvelope

MessageEnvelope 是统一传输包络，不改写业务 payload 语义。

### 3.3 DeliveryReceipt

DeliveryReceipt 是投递结果对象，用于回执、追踪与重发依据。

它必须使用显式 status 表达投递状态，并通过 error_code 表达失败原因，不再使用自由布尔值承载全部语义。

### 3.4 DeadLetterRecord

DeadLetterRecord 是无法正常投递的消息治理对象，不得被当作业务事件重新投递。

failure_reason 必须使用受控枚举，当前至少覆盖 target_endpoint_unreachable、serialization_error、schema_mismatch、timeout、unauthorized。

### 3.5 SubscriptionBinding

SubscriptionBinding 用于表达订阅绑定与治理状态。

status 当前冻结为 success 或 rejected。

success 用于可参与路由的有效订阅。

rejected 用于保留治理审计语义，但不得参与消息实际投递。

### 3.6 SubscriptionBindingAuditRecord

SubscriptionBindingAuditRecord 用于记录 subscription_bound 相关治理决策的审计事实。

它至少应保留 trace_id、subscription_id、topic、subscriber_endpoint_id、status、status_reason 与 recorded_at_utc_ms。

### 3.7 RetryScheduleEntry

RetryScheduleEntry 用于表达 MsgService 已接受的重试调度计划。

它不是业务消息本体，而是消息治理层的调度对象，至少应保留 trace_id、retry_count、failure_reason、scheduled_at_utc_ms 与 next_attempt_at_utc_ms。

## 4. 工程规则

1. 所有跨分系统消息必须通过 MessageEnvelope 承载统一公共头。
2. 业务分系统不得绕过 TopicDefinition 私下定义未登记 topic。
3. DeliveryReceipt 只反映投递结果，不反映业务处理完成与否。
4. DeadLetterRecord 必须保留原 topic、payload_type、trace_id 与失败原因。
5. SubscriptionBinding 的 success 与 rejected 均可发布到 subscription_bound 主题，但只有 success 可进入路由面。
6. TopicDefinition 在工程首版必须提供 owner_team、schema_uri、retention_ms，不能只保留语义最小字段。
7. DeliveryReceipt 失败时必须填写 error_code；成功时 error_code 必须为 NONE。
8. rejected 订阅一旦形成治理事件，必须同步形成可审计记录，不得只在瞬时内存中丢失。
9. RetryPlan 一旦进入可重试决策，必须可落为 RetryScheduleEntry，便于后续调度器或任务框架接管。

## 5. 下一阶段建议

1. 下一阶段可补重试策略对象、时序约束与流控策略对象。
2. 下一阶段可补 TopicDefinition 的路由优先级、兼容级别与废弃策略字段。
3. 下一阶段可补 SubscriptionBinding 的 pending、版本偏好与过滤表达式字段。
4. 下一阶段可补 SubscriptionBindingAuditRecord 与 RetryScheduleEntry 的持久化和对外发布边界。
