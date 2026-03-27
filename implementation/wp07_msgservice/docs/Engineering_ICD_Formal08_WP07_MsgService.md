# WP07 MsgService 工程级 ICD 初版

本文档是 wp07_msgservice 在工程实现阶段的工程级 ICD 初版。

它不是对 Formal 08 的替代，而是 Formal 08 在首个开发包中的工程化落地版本。

## 1. 当前阶段

1. 当前版本：v1.0。
2. 当前用途：审核通过版的工程接口约束与实现基线。
3. 冻结程度：可作为后续工作包接入口、持久化接入和程序集成的实现基线；跨包联调仍需遵循各包自身契约冻结节奏。

## 2. 本轮审查目标

后续需要用户重点审查以下 3 项：

1. 颗粒度是否符合预期。
2. 是否覆盖想体现的功能项。
3. 是否具备后续扩展性。

本轮审查结论已经确认：

1. 当前颗粒度可继续支撑 wp07 开发。
2. SubscriptionBinding 立即引入 success / rejected 状态。
3. TopicDefinition 首版纳入工程治理字段。
4. failure_reason 改为 enum，并通过枚举扩展。

## 3. 当前冻结项

1. topic：
   1. bms/core/ops/msg/topic_defined
   2. bms/core/ops/msg/subscription_bound
   3. bms/core/ops/msg/delivery_receipt
   4. bms/core/ops/msg/dead_letter
2. 核心 payload：
   1. TopicDefinition
   2. SubscriptionBinding
   3. MessageEnvelope
   4. DeliveryReceipt
   5. DeadLetterRecord
3. trace_id 规则：message_trace_id 必须可回接 MessageEnvelope.trace_id。
4. 边界规则：DeliveryReceipt 只表示投递结果，不代表业务处理完成。

## 4. 功能项覆盖矩阵

| 功能项 | 对应对象 | 当前状态 | 说明 |
| --- | --- | --- | --- |
| topic 注册 | TopicDefinition | 已覆盖 | 支持 topic、payload_type、QoS 初版 |
| 订阅绑定 | SubscriptionBinding | 已覆盖 | 支持 success / rejected 两类状态 |
| 标准消息包络 | MessageEnvelope | 已覆盖 | 保留 trace_id、topic、payload_type、schema_version |
| 投递回执 | DeliveryReceipt | 已覆盖 | 支持 subscriber 级回执输出，当前使用显式状态枚举与 error_code |
| 重试失败转死信 | DeadLetterRecord | 已覆盖 | failure_reason 已切换为 enum |
| 版本兼容治理 | MessageEnvelope + TopicDefinition | 已覆盖首版 | TopicDefinition 已纳入 schema_uri、owner_team、retention |
| 订阅成功/失败分流 | SubscriptionBinding | 已覆盖 | rejected 记录可保留审计语义，路由时只分发 success |
| 订阅治理事件发布 | SubscriptionBinding | 已覆盖首版 | success 与 rejected 都可形成 subscription_bound 治理事件 |
| 重试计划计算 | RetryPolicy | 已覆盖首版 | 当前支持可重试判定与指数退避初版 |

## 5. topic 工程定义

### 5.1 bms/core/ops/msg/topic_defined

1. 发布方：MsgService.TopicRegistry。
2. 订阅方：业务分系统、MonitorLog。
3. 触发条件：topic 注册成功或版本更新完成。
4. payload：TopicDefinition。

### 5.2 bms/core/ops/msg/subscription_bound

1. 发布方：MsgService.SubscriptionRegistry。
2. 订阅方：业务分系统、MonitorLog。
3. 触发条件：订阅关系注册或变更完成。
4. payload：SubscriptionBinding。
5. 当前规则：success 与 rejected 都发布治理事件，但 rejected 不进入路由面。

### 5.3 bms/core/ops/msg/delivery_receipt

1. 发布方：MsgService.DeliveryTracker。
2. 订阅方：原发布者、MonitorLog。
3. 触发条件：消息投递成功或失败。
4. payload：DeliveryReceipt。

### 5.4 bms/core/ops/msg/dead_letter

1. 发布方：MsgService.RetryAndDeadLetterService。
2. 订阅方：原发布者、MonitorLog。
3. 触发条件：重试超过阈值且最终失败。
4. payload：DeadLetterRecord。

## 6. payload 颗粒度定义

### 6.1 TopicDefinition

作用：定义 topic 的治理元数据，而不是业务 payload 本身。

| 字段 | 类型 | 必填 | 当前语义 | 扩展建议 |
| --- | --- | --- | --- | --- |
| topic | string | 是 | topic 唯一标识 | 当前冻结 |
| domain | string | 是 | 所属域 | 后续可补 owner_team |
| payload_type | string | 是 | 绑定 payload 类型 | 后续可补 schema_uri |
| qos_profile | string | 是 | QoS 档位 | 后续可替换为强类型枚举 |
| topic_state | enum | 是 | topic 生命周期状态，首版含 active / deprecated | 后续可补 retired |
| owner_team | string | 是 | topic 工程责任团队 | 当前冻结 |
| schema_uri | string | 是 | schema 权威位置 | 当前冻结 |
| retention_ms | int64 | 是 | 保留周期 | 后续可补 retention_policy |

### 6.2 SubscriptionBinding

作用：表达 subscriber 与 topic 的绑定关系。

| 字段 | 类型 | 必填 | 当前语义 | 扩展建议 |
| --- | --- | --- | --- | --- |
| subscription_id | string | 是 | 订阅唯一标识 | 后续可补生命周期状态 |
| topic | string | 是 | 绑定 topic | 后续可补版本偏好 |
| subscriber_endpoint_id | string | 是 | 订阅端唯一标识 | 后续可补 endpoint_type |
| status | enum | 是 | 当前含 success / rejected | 后续可补 pending |
| status_reason | string | 否 | rejected 或特殊治理状态原因 | 后续可拆 error_code |

### 6.3 MessageEnvelope

作用：承载消息治理层所需的最小包络信息。

| 字段 | 类型 | 必填 | 当前语义 | 扩展建议 |
| --- | --- | --- | --- | --- |
| trace_id | string | 是 | 全链路追踪标识 | 后续可补 parent_trace_id |
| topic | string | 是 | 目标 topic | 当前冻结 |
| payload_type | string | 是 | payload 类型名 | 后续可补 descriptor |
| schema_version | string | 是 | schema 版本 | 当前冻结 |

### 6.4 DeliveryReceipt

作用：表达单 subscriber 粒度的投递结果。

| 字段 | 类型 | 必填 | 当前语义 | 扩展建议 |
| --- | --- | --- | --- | --- |
| receipt_id | string | 是 | 回执唯一标识 | 可补 attempt_no |
| topic | string | 是 | 来源 topic | 当前冻结 |
| message_trace_id | string | 是 | 对应包络 trace_id | 当前冻结 |
| subscriber_endpoint_id | string | 是 | 回执目标端 | 当前冻结 |
| status | enum | 是 | 当前含 succeeded / failed | 后续可补 delayed / dropped |
| error_code | enum | 是 | 当前含 none、target_endpoint_unreachable、serialization_error、schema_mismatch、timeout、unauthorized | 后续可补 quota_exceeded |
| delivered_at_utc_ms | int64 | 是 | 投递完成时间 | 当前冻结 |

### 6.5 DeadLetterRecord

作用：表达最终失败且进入死信的消息记录。

| 字段 | 类型 | 必填 | 当前语义 | 扩展建议 |
| --- | --- | --- | --- | --- |
| dead_letter_id | string | 是 | 死信记录标识 | 当前冻结 |
| original_topic | string | 是 | 原始 topic | 当前冻结 |
| payload_type | string | 是 | 原始 payload 类型 | 当前冻结 |
| message_trace_id | string | 是 | 原始 trace_id | 当前冻结 |
| failure_reason | enum | 是 | 当前含 unknown、target_endpoint_unreachable、serialization_error、schema_mismatch、timeout、unauthorized | 后续按 enum 扩展 |
| retry_count | uint32 | 是 | 已重试次数 | 当前冻结 |
| last_attempt_utc_ms | int64 | 是 | 最后一次尝试时间 | 当前已补入代码骨架 |

## 7. 扩展性设计说明

当前工程级 ICD 采用以下扩展策略：

1. topic 与 payload 分离，便于后续追加 topic_state、retry_policy 等治理对象。
2. MessageEnvelope 保持轻量，只放治理层必需字段，避免把业务语义侵入消息治理层。
3. DeliveryReceipt 与 DeadLetterRecord 分离，便于后续对回执和死信分别扩展错误码、重试策略、统计信息。
4. SubscriptionBinding 已引入状态字段，后续可继续增补版本偏好、过滤条件，而不破坏当前骨架。
5. DeadLetterRecord 采用 enum 型 failure_reason，后续扩展失败原因时优先增枚举，不再走自由文本漂移。
6. RetryPolicy 目前保持为服务内部策略对象，待跨包联调前再决定是否上升为 Formal 08 公共契约对象。

## 8. 当前实现映射

当前代码骨架已覆盖：

1. TopicRegistry。
2. SubscriptionRegistry。
3. SubscriptionGovernanceService。
4. SubscriptionAuditRepository 接口与 InMemory 或 File 适配器。
5. EnvelopeRouter。
6. DeliveryTracker。
7. MsgServiceApplicationService。
8. RetryAndDeadLetterService。
9. RetryScheduleRepository 接口与 InMemory 或 File 适配器。
10. RegisterTopicCommand、RegisterSubscriptionCommand、RecordDeliveryCommand、HandleDeliveryFailureCommand。
11. RegisterTopicRequestDto、RegisterSubscriptionRequestDto、RecordDeliveryRequestDto、HandleDeliveryFailureRequestDto。
12. MsgServiceCommandMapper。
13. MsgServiceCommandHandler。
14. SqliteSubscriptionAuditRepository、SqliteRetryScheduleRepository 的 SQLite-ready 骨架。
15. RegisterTopicResponseDto、RegisterSubscriptionResponseDto、RecordDeliveryResponseDto、HandleDeliveryFailureResponseDto。
16. MsgServiceResponseMapper。
17. MsgServiceRepositoryFactory，默认持久化策略指向 sqlite。

File adapter 当前冻结的持久化约束：

1. 文件首行必须为格式版本头。
2. 文件次行必须为固定字段顺序声明。
3. 数据行字段顺序不得随适配器实现漂移。

对应工程目录：

1. ../include/wp07_msgservice/
2. ../src/
3. ../tests/

## 9. 下一版补齐项

在进入跨包联调前，必须补齐：

1. subscription_bound 的审计持久化介质与归档周期。
2. 回执错误码与 dead letter failure_reason 的映射规则。
3. 重试策略时序约束与调度接口对外契约。
4. QoS 强类型化。
5. 版本兼容与废弃字段策略。
6. endpoint_type、publisher、subscriber 的扩展字段表。
7. application service 与外部 adapter 的事务边界。
8. File adapter 到数据库或任务框架 adapter 的迁移策略。
9. use case 输入命令到外部 API 或消息入口 DTO 的映射方式。
10. 文件持久化格式的转义规则与兼容升级策略。

## 10. 模块完成判定

当前 wp07 已达到“模块完成，审核通过”状态，依据如下：

1. 领域对象、治理规则、审计与重试路径已具备最小闭环。
2. application service、command mapper、command handler 已形成从外部输入到内部用例的入口链。
3. repository 已具备 in-memory、file 两类可运行适配器。
4. sqlite adapter 已形成可编译、可运行、可落库验证的真实持久化实现。
5. response dto 与 response mapper 已形成对外稳定返回模型。
6. repository factory 已把默认持久化策略固化为 sqlite。
7. file adapter 已被提升为正式轻量部署形态，而非调试专用。
8. 测试已从 smoke test 演进为分职责测试集合。

当前模块外的后续关注项如下，不再构成 wp07 审核阻断：

1. file format 的转义和升级策略细节。
2. command handler 对外错误模型与返回码契约是否满足上层系统约定。
3. adapter 层与未来 API、消息总线、任务框架的事务边界。
4. 上层最终程序对 SQLite 运行库分发 helper 的实际接入。

当前 SQLite 接入状态补充说明：

1. 当前工程环境已完成 sqlite3:x64-windows 安装。
2. `implementation/wp07_msgservice/CMakeLists.txt` 已支持原生 SQLite3 包与 vcpkg 安装目录双路径发现。
3. 当前阶段已满足 sqlite adapter 编译接入条件。
4. `sqlite3.dll` 部署基线冻结为随程序目录分发，不走系统 PATH 注入。
5. 本模块提供 `bms_msgservice_attach_sqlite_runtime(<target>)` 与 `bms_msgservice_install_sqlite_runtime(bin)` 两个 CMake 入口，分别用于构建后复制与安装期落盘。
6. 联调阶段只需统一程序安装目录与业务数据目录约定，不再单独讨论 SQLite 运行库装载策略。

## 11. 审查建议

本轮审查已经形成明确结论，后续不再停留在是否引入，而转入如何细化：

1. DeliveryReceipt 继续保持单 subscriber 粒度。
2. SubscriptionBinding 以 success / rejected 为首版冻结状态。
3. TopicDefinition 首版冻结纳入 topic_state、owner_team、schema_uri、retention_ms。
4. DeadLetterRecord 的 failure_reason 按 enum 体系扩展。

建议本轮模块审核优先审查四个问题：

1. command handler 与 response dto 组成的对外入口边界，是否符合你预期。
2. 默认持久化=sqlite、file=正式轻量部署 的策略是否符合你预期。
3. response dto 中新增的 trace_id、schedule_id、dead_letter_id、audit_record_id 等追踪字段是否足够。
4. failure_reason、delivery error_code 与 TopicDefinition 治理字段是否还需要继续扩展。
