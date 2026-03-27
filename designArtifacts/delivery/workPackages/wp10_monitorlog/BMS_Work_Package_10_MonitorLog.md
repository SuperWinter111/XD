# BMS 工作包 10 MonitorLog

本文档是监控与日志分系统的可执行工作包，供软件工程师或 agent 直接领取并进入实现。

## 1. 基本信息

1. 分系统名称：MonitorLog。
2. 负责人类型：软件工程师或 agent。
3. 对应 Container：plantumlC4/C4_L2_Container.puml 中监控与日志分系统。
4. 对应 Component 图：plantumlC4/C4_L3_Component_13_MonitorLog.puml。
5. 对应 Code 图：无独立 code 图，以监控对象目录、Formal 10 和协作文档为主。
6. 对应正式 ICD：BMS_ICD_Formal_10。

## 2. 目标范围

1. 汇聚消息治理、通信、审计、部署与业务域输出的指标、日志和告警信号。
2. 统一生成 MonitorMetric、MonitorAlert 和可追踪日志索引对象。
3. 向 OpsMgmt 和 BFF 提供只读监控与告警输出。
4. 支撑跨分系统 trace_id 关联排障和联调观测。
5. 保持监控只读语义，不反写业务主域对象。

不包含：

1. 运维流程审批与配置治理。
2. 版本发布与回滚执行。
3. 审计权威结论输出。

## 3. 对象边界

### 3.1 主拥有对象

1. MonitorMetric。
2. MonitorAlert。
3. LogDigest。
4. TraceCorrelationRecord。

### 3.2 只读消费对象

1. DeliveryReceipt。
2. DeadLetterRecord。
3. LinkQualitySnapshot。
4. DegradationAlert。
5. SecurityEvent。
6. AuditEvent。
7. ReleaseEvent。

### 3.3 禁止越权修改

1. 不得替代 AuthAudit 输出审计权威对象。
2. 不得替代 OpsMgmt 执行处置流程。
3. 不得把监控对象回写业务主域。
4. 不得把 MonitorAlert 伪装成业务执行结论。

## 4. topic 责任

### 4.1 发布 topic

| topic | payload | 触发条件 | 下游 |
| --- | --- | --- | --- |
| bms/core/ops/monitor/metric | MonitorMetric | 指标汇总或周期采集完成 | OpsMgmt, BFF |
| bms/core/ops/monitor/alert | MonitorAlert | 告警条件满足或升级 | OpsMgmt, BFF |
| bms/core/ops/monitor/log_digest | LogDigest | 日志汇总或检索结果输出 | OpsMgmt |

### 4.2 订阅 topic

| topic | payload | 上游 | 消费动作 |
| --- | --- | --- | --- |
| bms/core/ops/msg/delivery_receipt | DeliveryReceipt | MsgService | 汇入消息治理指标 |
| bms/core/ops/msg/dead_letter | DeadLetterRecord | MsgService | 触发消息异常监控 |
| bms/core/ops/comm/link_quality | LinkQualitySnapshot | CommNet | 汇入链路质量指标 |
| bms/core/ops/comm/link_degraded | DegradationAlert | CommNet | 触发链路告警 |
| bms/core/ops/comm/security_event | SecurityEvent | CommNet | 汇入安全监控上下文 |
| bms/core/ops/sec/audit_event | AuditEvent | AuthAudit | 汇入审计观测 |
| bms/core/ops/deploy/release_event | ReleaseEvent | Version / Deploy | 汇入发布观测 |

## 5. 模块拆分

| 模块 | 责任 | 输入 | 输出 |
| --- | --- | --- | --- |
| MetricIngestService | 汇总多域指标输入 | DeliveryReceipt, LinkQualitySnapshot 等 | MonitorMetric |
| AlertAggregationService | 统一生成与升级告警 | 指标流, 异常事件 | MonitorAlert |
| LogIndexService | 维护日志与检索索引 | 各类事件流 | LogDigest |
| TraceCorrelationService | 基于 trace_id 做跨域关联 | 多域事件流 | TraceCorrelationRecord |
| OpsReadModelBuilder | 为 OpsMgmt 和 BFF 生成只读监控视图 | MonitorMetric, MonitorAlert | 只读监控视图 |

## 6. 实施步骤

1. 先接入 MsgService 和 CommNet 输入，形成指标与告警主链。
2. 接入 AuditEvent 与 ReleaseEvent，补齐安全与发布观测。
3. 实现 TraceCorrelationService，支撑跨分系统联调排障。
4. 建立 BFF 所需只读监控视图输出。
5. 最后与 OpsMgmt 完成运维处置联调。

## 7. 测试与验收

### 7.1 必备样例

1. 正常样例：metric 汇总与 alert 推送正常输出。
2. 异常样例：dead_letter、security_event 或 release failure 触发监控告警。
3. 边界样例：MonitorAlert 只读输出，不反写业务域或审计域对象。

### 7.2 契约测试

1. MonitorMetric 与 MonitorAlert 必须符合 Formal 10。
2. dead_letter、link_degraded、security_event 的来源和 trace_id 必须可追溯。
3. 告警等级与 BFF 展示视图必须保持一致口径。
4. 监控聚合不得抹平原始 owner 对象来源。

### 7.3 完成定义

1. 监控聚合主链已形成实现骨架。
2. metric 与 alert 两条主链可验证。
3. 与 AuthAudit、MsgService、CommNet、OpsMgmt、BFF 的联调项已映射到联调矩阵。
4. 已准备 Formal 10 的监控样例与验收记录。

## 8. 风险与待决项

1. 风险：多域事件同时汇入时，告警去重和关联规则容易复杂化。
2. 风险：若 trace_id 覆盖不完整，会降低联调和排障价值。
3. 待决项：是否需要追加面向联调阶段的专项 trace 查询视图。
