# WP07 MsgService ICD 设计包

## 1. 适用小组

1. 消息治理实现小组。
2. 负责 topic 注册、订阅绑定、投递回执、重试与死信治理的工程师或 agent。

## 2. 主工作包入口

1. [BMS_Work_Package_07_MsgService.md](BMS_Work_Package_07_MsgService.md)

## 3. 必读 Formal ICD

1. [BMS_ICD_Formal_08_Message_Governance_And_Delivery.md](../../../icd/BMS_ICD_Formal_08_Message_Governance_And_Delivery.md)

## 4. 必读补充设计文档

1. [BMS_MsgService_vs_CommNet_Responsibility_Matrix.md](../../BMS_MsgService_vs_CommNet_Responsibility_Matrix.md)
2. [BMS_Contract_Test_Baseline.md](../../BMS_Contract_Test_Baseline.md)
3. [BMS_Execution_Index.md](../../BMS_Execution_Index.md)

## 5. 本组重点确认项

1. TopicDefinition、SubscriptionBinding、DeliveryReceipt、DeadLetterRecord 的边界。
2. DeliveryReceipt 不代表业务处理完成。
3. 版本兼容只能处理包络治理，不能改变业务语义。

## 6. 交付前核对清单

1. topic_defined、subscription_bound、delivery_receipt、dead_letter 样例已准备。
2. 与 CommNet 的职责分离已核对。
3. trace_id、publisher、subscriber 追踪链已验证。
4. rejected 订阅审计记录与 retry 调度样例已可回溯到 Formal 08。

## 7. 重点 topic 清单

1. 发布：bms/core/ops/msg/topic_defined。
2. 发布：bms/core/ops/msg/subscription_bound。
3. 发布：bms/core/ops/msg/delivery_receipt。
4. 发布：bms/core/ops/msg/dead_letter。
5. 订阅：bms/core/ops/msg/topic_register_requested。
6. 订阅：bms/core/ops/msg/subscription_register_requested。
7. 订阅：bms/core/ops/msg/message_enqueued。

## 8. 重点 payload 清单

1. TopicDefinition。
2. SubscriptionBinding。
3. MessageEnvelope。
4. DeliveryReceipt。
5. DeadLetterRecord。
6. SubscriptionBindingAuditRecord。
7. RetryScheduleEntry。

## 9. 样例与测试入口

1. [Formal 08 样例基线](../../BMS_Contract_Test_Baseline.md)
2. [MsgService 与 CommNet 职责对照](../../BMS_MsgService_vs_CommNet_Responsibility_Matrix.md)

## 10. 小组签收清单

1. 已签收 topic、订阅、回执、死信对象边界。
2. 已签收回执不代表业务完成的规则。
3. 已确认版本兼容仅限消息治理层。
4. 已确认 rejected 订阅需要治理事件与审计记录双落点。
5. 已确认可重试失败必须形成可调度条目。

## 11. 字段级核对表

1. [Payload_Checklist.md](Payload_Checklist.md)
