# WP13 VersionDeploy Payload 核对表

## 1. 重点 payload

1. ReleaseEvent。
2. ReleasePlan。
3. EnvironmentCheckResult。
4. RollbackExecutionRecord。
5. ConfigChangeRecord。
6. MonitorAlert。
7. IncidentTicket。

## 2. 字段级核对重点

1. ReleaseEvent：必须覆盖开始、成功、失败、阻断和回滚等关键状态。
2. ReleasePlan：必须包含版本基线、目标环境和发布时间窗口。
3. EnvironmentCheckResult：必须表达检查项、结果、阻断原因和时间点。
4. RollbackExecutionRecord：必须表达触发来源、回滚对象、回滚结果和完成时间。
5. ConfigChangeRecord、MonitorAlert、IncidentTicket：只读消费时必须保留来源与状态。

## 3. 常见错误

1. release_event 状态覆盖不完整。
2. rollback_record 缺少触发来源和回滚结果。
3. 环境阻断没有明确阻断原因字段。
