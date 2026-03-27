# BMS 工作包 07 MsgService

本文档是消息服务分系统的可执行工作包，供软件工程师或 agent 直接领取并进入实现。

## 1. 基本信息

1. 分系统名称：MsgService。
2. 负责人类型：软件工程师或 agent。
3. 对应 Container：plantumlC4/C4_L2_Container.puml 中消息服务分系统。
4. 对应 Component 图：plantumlC4/C4_L3_Component_07_MsgService.puml。
5. 对应 Code 图：plantumlC4/Code_06_MsgService.puml。
6. 对应正式 ICD：BMS_ICD_Formal_08。

## 2. 目标范围

1. 提供 topic 注册、订阅绑定、消息包络、回执、重试与死信的统一治理能力。
2. 保证跨分系统消息的版本兼容、投递可追踪和失败可回溯。
3. 向业务分系统暴露被治理后的消息通道，而不是让业务系统各自实现消息总线策略。
4. 向 MonitorLog 输出可观测的回执、重试和死信事件。
5. 保持消息治理职责与 CommNet 的承载职责清晰分离。

不包含：

1. 业务对象语义建模。
2. 网络链路质量评估。
3. 业务处理成功与否的最终判定。

## 3. 对象边界

### 3.1 主拥有对象

1. TopicDefinition。
2. SubscriptionBinding。
3. MessageEnvelope。
4. DeliveryReceipt。
5. DeadLetterRecord。
6. RetryPolicyBinding。

### 3.2 只读消费对象

1. 各业务分系统的发布声明。
2. 各业务分系统的订阅声明。
3. 待治理的跨分系统消息。

### 3.3 禁止越权修改

1. 不得把 DeliveryReceipt 解释成业务处理完成。
2. 不得修改业务 payload 的业务语义，只能做包络治理与版本适配。
3. 不得替代 CommNet 输出链路质量或安全事件。
4. 不得替代业务 owner 做 topic 语义裁定。

## 4. topic 责任

### 4.1 发布 topic

| topic | payload | 触发条件 | 下游 |
| --- | --- | --- | --- |
| bms/core/ops/msg/topic_defined | TopicDefinition | 完成 topic 注册或版本更新 | 全部分系统, MonitorLog |
| bms/core/ops/msg/subscription_bound | SubscriptionBinding | 订阅关系注册或变更 | 全部分系统, MonitorLog |
| bms/core/ops/msg/delivery_receipt | DeliveryReceipt | 消息投递完成或失败 | 发布者, MonitorLog |
| bms/core/ops/msg/dead_letter | DeadLetterRecord | 重试失败或消息进入死信 | 发布者, MonitorLog |

### 4.2 订阅 topic

| topic | payload | 上游 | 消费动作 |
| --- | --- | --- | --- |
| bms/core/ops/msg/topic_register_requested | TopicDefinition | 各业务分系统 | 注册 topic 与版本 |
| bms/core/ops/msg/subscription_register_requested | SubscriptionBinding | 各业务分系统 | 建立订阅关系 |
| bms/core/ops/msg/message_enqueued | MessageEnvelope | 发布者 | 进行路由、投递与回执 |

## 5. 模块拆分

| 模块 | 责任 | 输入 | 输出 |
| --- | --- | --- | --- |
| TopicRegistry | 管理 topic 定义与版本 | TopicDefinition | topic_defined |
| SubscriptionRegistry | 管理订阅绑定与兼容校验 | SubscriptionBinding | subscription_bound |
| EnvelopeRouter | 进行消息路由与投递 | MessageEnvelope | 投递任务 |
| DeliveryTracker | 记录投递回执与重试结果 | 投递任务 | DeliveryReceipt |
| RetryAndDeadLetterService | 处理重试与死信 | DeliveryReceipt | DeadLetterRecord |
| VersionCompatibilityAdapter | 处理版本兼容与字段适配 | MessageEnvelope | 兼容后的包络 |

## 6. 实施步骤

1. 先实现 TopicRegistry 和 SubscriptionRegistry，打通 topic_defined 与 subscription_bound。
2. 实现 EnvelopeRouter，形成标准化消息路由主链。
3. 接入 DeliveryTracker，输出 delivery_receipt。
4. 补齐 RetryAndDeadLetterService，完成失败路径治理。
5. 最后补齐版本兼容适配并与 MonitorLog 完成观测联调。

## 7. 测试与验收

### 7.1 必备样例

1. 正常样例：topic_defined -> delivery_receipt.success。
2. 异常样例：重试失败后进入 dead_letter。
3. 边界样例：DeliveryReceipt 只表示投递结果，不表示业务处理成功。

### 7.2 契约测试

1. TopicDefinition、SubscriptionBinding、DeliveryReceipt、DeadLetterRecord 必须符合 Formal 08。
2. 版本适配不能改变业务 payload 的原始业务语义。
3. 回执必须可追踪到 topic、publisher、subscriber 与 trace_id。
4. 死信记录必须保留失败原因与重试历史。

### 7.3 完成定义

1. Code_06_MsgService 的主模块已形成实现骨架。
2. topic_defined、delivery_receipt 和 dead_letter 三条主链可验证。
3. 与发布者、订阅者、MonitorLog 的联调项已映射到联调矩阵。
4. 已准备 Formal 08 所需样例与回归清单。

## 8. 风险与待决项

1. 风险：多版本 payload 并行期可能导致兼容适配逻辑膨胀。
2. 风险：若回执与业务处理状态混淆，下游会错误推断消息已被消费成功。
3. 待决项：subscription_bound 是否需要细分为注册成功与兼容失败两类事件。
