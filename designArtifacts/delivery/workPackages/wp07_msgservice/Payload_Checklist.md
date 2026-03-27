# WP07 MsgService Payload 核对表

## 1. 重点 payload

1. TopicDefinition。
2. SubscriptionBinding。
3. MessageEnvelope。
4. DeliveryReceipt。
5. DeadLetterRecord。
6. SubscriptionBindingAuditRecord。
7. RetryScheduleEntry。

## 2. 字段级核对重点

1. TopicDefinition：必须明确 topic 名称、版本、payload 绑定和 QoS。
2. SubscriptionBinding：必须明确 subscriber、topic、版本和订阅关系状态。
3. MessageEnvelope：必须保留 trace_id、payload 类型、版本和路由所需标识。
4. DeliveryReceipt：必须表达投递结果、时间点、目标端、error_code 和 trace 回接关系。
5. DeadLetterRecord：必须保留原始消息标识、重试历史和最终失败原因。
6. SubscriptionBindingAuditRecord：必须保留绑定决策、原因、trace_id 和记录时间。
7. RetryScheduleEntry：必须保留调度时间、下次尝试时间、失败原因和重试次数。

## 3. 常见错误

1. 用 DeliveryReceipt 表达业务处理完成。
2. 在 MessageEnvelope 中篡改业务 payload 语义。
3. 死信记录缺少重试历史或最终失败原因。
4. rejected 订阅只发治理事件，不留审计记录。
5. 有 RetryPlan，但没有可交给调度器的 RetryScheduleEntry。
