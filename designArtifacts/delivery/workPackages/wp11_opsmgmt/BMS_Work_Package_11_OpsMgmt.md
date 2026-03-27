# BMS 工作包 11 OpsMgmt

本文档是运维管理分系统的可执行工作包，供软件工程师或 agent 直接领取并进入实现。

## 1. 基本信息

1. 分系统名称：OpsMgmt。
2. 负责人类型：软件工程师或 agent。
3. 对应 Container：plantumlC4/C4_L2_Container.puml 中运维管理分系统。
4. 对应 Component 图：plantumlC4/C4_L3_Component_14_OpsMgmt.puml。
5. 对应 Code 图：无独立 code 图，以协同规则、监控对象和 Formal 10 为主。
6. 对应正式 ICD：BMS_ICD_Formal_10。

## 2. 目标范围

1. 负责配置治理、运维作业、处置流程和自检任务的统一管理。
2. 消费 MonitorLog、AuthAudit 和 Version / Deploy 的输入，形成运维处置闭环。
3. 输出 config_changed、ops_job 和 selfcheck 等运维域权威对象。
4. 负责告警处置流程与运维记录，不替代 Version / Deploy 做发布和回滚执行。
5. 作为长期运维治理 owner 保持与发布域的协同边界清晰。

不包含：

1. 版本发布、部署和回滚执行。
2. 监控聚合与审计本体实现。
3. 业务主域对象改写。

## 3. 对象边界

### 3.1 主拥有对象

1. ConfigChangeRecord。
2. OpsJobRecord。
3. SelfCheckResult。
4. IncidentTicket。
5. OpsWorkflowRecord。

### 3.2 只读消费对象

1. MonitorMetric。
2. MonitorAlert。
3. AuditEvent。
4. ReleaseEvent。

### 3.3 禁止越权修改

1. 不得直接替代 Version / Deploy 执行发布或回滚。
2. 不得替代 MonitorLog 输出监控权威对象。
3. 不得改写 AuditEvent 的事实内容。
4. 不得越权改写业务主域对象。

## 4. topic 责任

### 4.1 发布 topic

| topic | payload | 触发条件 | 下游 |
| --- | --- | --- | --- |
| bms/core/ops/config_changed | ConfigChangeRecord | 配置变更审批并生效 | Version / Deploy, MonitorLog |
| bms/core/ops/job_dispatched | OpsJobRecord | 运维作业下发或执行 | MonitorLog, AuthAudit |
| bms/core/ops/selfcheck_result | SelfCheckResult | 自检完成 | MonitorLog, BFF |
| bms/core/ops/incident_updated | IncidentTicket | 告警处置状态更新 | MonitorLog, BFF |

### 4.2 订阅 topic

| topic | payload | 上游 | 消费动作 |
| --- | --- | --- | --- |
| bms/core/ops/monitor/metric | MonitorMetric | MonitorLog | 更新运维态势 |
| bms/core/ops/monitor/alert | MonitorAlert | MonitorLog | 触发处置流程 |
| bms/core/ops/sec/audit_event | AuditEvent | AuthAudit | 记录运维审计上下文 |
| bms/core/ops/deploy/release_event | ReleaseEvent | Version / Deploy | 协同发布和回滚流程 |

## 5. 模块拆分

| 模块 | 责任 | 输入 | 输出 |
| --- | --- | --- | --- |
| ConfigGovernanceService | 管理配置变更与生效审批 | 配置请求, MonitorAlert | ConfigChangeRecord |
| IncidentHandlingService | 驱动告警处置流程 | MonitorAlert, AuditEvent | IncidentTicket |
| OpsJobScheduler | 调度运维作业与流程 | IncidentTicket, 运维请求 | OpsJobRecord |
| SelfCheckService | 执行周期性与触发式自检 | 运维上下文 | SelfCheckResult |
| OpsWorkflowRecorder | 记录流程状态和处置证据 | IncidentTicket, OpsJobRecord | OpsWorkflowRecord |

## 6. 实施步骤

1. 先打通 monitor/alert 到 incident_updated 的处置主链。
2. 实现 ConfigGovernanceService，输出 config_changed。
3. 接入 OpsJobScheduler 和 SelfCheckService，完善运维执行能力。
4. 接入 release_event，形成与 Version / Deploy 的协同闭环。
5. 最后补齐运维流程记录与审计关联。

## 7. 测试与验收

### 7.1 必备样例

1. 正常样例：告警触发 -> incident_updated -> ops_job 执行。
2. 异常样例：环境阻断或高危告警触发升级处置。
3. 边界样例：OpsMgmt 触发回滚要求，但回滚执行仍由 Version / Deploy 完成。

### 7.2 契约测试

1. ConfigChangeRecord、OpsJobRecord、SelfCheckResult 必须符合 Formal 10。
2. config_changed 与 release_event 的协同边界必须符合协作文档约束。
3. 告警处置与审计记录必须具备可追溯 trace_id。
4. 不得在未记录 config_changed 的情况下做隐式配置变更。

### 7.3 完成定义

1. 运维治理主链已形成实现骨架。
2. config_changed、incident_updated 与 selfcheck_result 三条主链可验证。
3. 与 MonitorLog、AuthAudit、Version / Deploy 的联调项已映射到联调矩阵。
4. 已准备 Formal 10 所需运维样例与验收记录。

## 8. 风险与待决项

1. 风险：告警风暴下处置流程和作业调度容易发生雪崩。
2. 风险：配置变更与发布流程绑定过紧时，职责边界容易再次混淆。
3. 待决项：incident_updated 是否需要进一步区分人工处置和自动处置状态。
