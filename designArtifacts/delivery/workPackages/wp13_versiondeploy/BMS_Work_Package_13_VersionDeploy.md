# BMS 工作包 13 Version / Deploy

本文档是版本与部署分系统的可执行工作包，供软件工程师或 agent 直接领取并进入实现。

## 1. 基本信息

1. 分系统名称：Version / Deploy。
2. 负责人类型：软件工程师或 agent。
3. 对应 Container：plantumlC4/C4_L2_Container.puml 中版本与部署分系统。
4. 对应 Component 图：plantumlC4/C4_L3_Component_15_VersionDeploy.puml。
5. 对应 Code 图：无独立 code 图，以协同规则、Formal 10 和发布治理文档为主。
6. 对应正式 ICD：BMS_ICD_Formal_10。

## 2. 目标范围

1. 负责版本基线、发布计划、部署执行、发布验证和回滚执行。
2. 消费 OpsMgmt 的 config_changed、MonitorLog 的监控告警，形成发布与回滚决策闭环。
3. 输出 release_event，记录发布、失败、阻断与回滚结果。
4. 在环境阻断、发布失败和告警超阈值场景下执行回滚或终止发布。
5. 与 OpsMgmt 协同，但不替代长期运维治理 owner。

不包含：

1. 长期运维流程审批与配置治理。
2. 监控与审计对象本体实现。
3. 业务主域对象改写。

## 3. 对象边界

### 3.1 主拥有对象

1. ReleaseEvent。
2. ReleasePlan。
3. EnvironmentCheckResult。
4. RollbackExecutionRecord。

### 3.2 只读消费对象

1. ConfigChangeRecord。
2. MonitorAlert。
3. MonitorMetric。
4. IncidentTicket。

### 3.3 禁止越权修改

1. 不得替代 OpsMgmt 执行长期运维流程审批。
2. 不得替代 MonitorLog 输出监控权威对象。
3. 不得在未记录 release_event 的情况下做隐式发布或回滚。
4. 不得越权改写业务主域对象。

## 4. topic 责任

### 4.1 发布 topic

| topic | payload | 触发条件 | 下游 |
| --- | --- | --- | --- |
| bms/core/ops/deploy/release_event | ReleaseEvent | 发布启动、成功、失败、阻断或回滚完成 | OpsMgmt, MonitorLog, AuthAudit |
| bms/core/ops/deploy/rollback_record | RollbackExecutionRecord | 回滚执行完成 | OpsMgmt, MonitorLog |

### 4.2 订阅 topic

| topic | payload | 上游 | 消费动作 |
| --- | --- | --- | --- |
| bms/core/ops/config_changed | ConfigChangeRecord | OpsMgmt | 读取配置变更上下文 |
| bms/core/ops/monitor/alert | MonitorAlert | MonitorLog | 判断发布风险与回滚条件 |
| bms/core/ops/monitor/metric | MonitorMetric | MonitorLog | 进行发布后健康校验 |
| bms/core/ops/incident_updated | IncidentTicket | OpsMgmt | 接收运维处置结论 |

## 5. 模块拆分

| 模块 | 责任 | 输入 | 输出 |
| --- | --- | --- | --- |
| ReleasePlanner | 维护发布计划与版本基线 | ConfigChangeRecord, 发布请求 | ReleasePlan |
| EnvironmentGateChecker | 执行环境与依赖检查 | ReleasePlan, MonitorMetric | EnvironmentCheckResult |
| DeploymentExecutor | 执行部署与发布动作 | ReleasePlan | ReleaseEvent |
| RollbackCoordinator | 根据失败和阈值触发回滚 | MonitorAlert, IncidentTicket | RollbackExecutionRecord |
| ReleaseAuditEmitter | 输出发布与回滚记录 | 发布执行上下文 | ReleaseEvent |

## 6. 实施步骤

1. 先实现 ReleasePlanner 和 EnvironmentGateChecker，打通发布前检查主链。
2. 实现 DeploymentExecutor，输出 release_event。
3. 接入 MonitorAlert 与 IncidentTicket，补齐失败处置和回滚路径。
4. 输出 RollbackExecutionRecord，形成完整回滚审计链。
5. 最后按协同规则与 OpsMgmt、MonitorLog 完成联合验收。

## 7. 测试与验收

### 7.1 必备样例

1. 正常样例：config_changed -> 发布执行 -> release_event.success。
2. 异常样例：发布失败或健康检查失败触发回滚。
3. 边界样例：环境阻断导致发布未执行，但必须输出 release_event.blocked。

### 7.2 契约测试

1. ReleaseEvent、RollbackExecutionRecord 与相关状态必须符合 Formal 10。
2. release_event 必须覆盖开始、成功、失败、阻断和回滚等关键状态。
3. 回滚触发来源必须可追溯到 MonitorAlert、发布验证失败或 OpsMgmt 处置结论。
4. config_changed 与 release_event 的协同边界必须符合协同约束文档。

### 7.3 完成定义

1. 发布与回滚主链已形成实现骨架。
2. release_event 与 rollback_record 两条主链可验证。
3. 与 OpsMgmt、MonitorLog 的联调项已映射到联调矩阵。
4. 已准备 Formal 10 所需发布与回滚样例。

## 8. 风险与待决项

1. 风险：环境探测与健康校验阈值不稳定时，会导致误阻断或误回滚。
2. 风险：发布与配置变更同时推进时，若协同记录不足，回溯会困难。
3. 待决项：rollback_record 是否需要进一步细分人工触发与自动触发两类路径。
