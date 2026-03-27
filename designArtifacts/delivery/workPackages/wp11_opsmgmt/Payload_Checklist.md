# WP11 OpsMgmt Payload 核对表

## 1. 重点 payload

1. ConfigChangeRecord。
2. OpsJobRecord。
3. SelfCheckResult。
4. IncidentTicket。
5. OpsWorkflowRecord。
6. ReleaseEvent。

## 2. 字段级核对重点

1. ConfigChangeRecord：必须明确变更对象、审批结果、生效时间和关联告警或需求。
2. OpsJobRecord：必须表达作业类型、触发来源、执行状态和时间点。
3. SelfCheckResult：必须表达检查项、结果、环境和时间点。
4. IncidentTicket：必须表达告警来源、处置状态、责任人和流转时间。
5. OpsWorkflowRecord：必须能关联 IncidentTicket 和 OpsJobRecord。
6. ReleaseEvent：只读消费时必须保留发布来源和状态，不得改写。

## 3. 常见错误

1. config_changed 缺少审批结果或生效时间。
2. incident_updated 不能追溯到原始 MonitorAlert。
3. 用 OpsMgmt 对象替代发布域 release_event。
