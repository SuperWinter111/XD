# BMS 正式 ICD 专题 10 运维审计与监控

本文档定义 AuthAudit、MonitorLog、OpsMgmt 之间的审计、安全告警、监控指标与监控告警接口约束。

## 1. Topic 绑定

| topic | payload | 发布方 | 订阅方 | QoS |
| --- | --- | --- | --- | --- |
| bms/core/ops/sec/audit_event | bms.schema.audit.AuditEvent | AuthAudit | MonitorLog | QOS-ALERT |
| bms/core/ops/monitor/metric | bms.schema.monitor.MonitorMetric | MonitorLog | OpsMgmt | QOS-STATE |
| bms/core/ops/monitor/alert | bms.schema.monitor.MonitorAlert | MonitorLog | OpsMgmt, HMI-BFF | QOS-ALERT |

## 2. 对象边界

1. AuditEvent 是审计对象，不是业务命令对象。
2. SecurityAlert 是安全告警对象，不是通信安全事件本体替代物。
3. MonitorMetric 是监控读数集合，不是业务主状态。
4. MonitorAlert 是统一运维告警对象，不替代业务域异常对象。

## 3. 工程规则

1. AuditEvent 必须可回溯 actor、action、target 与 result。
2. MonitorMetric 中的 MetricPoint 必须声明单位。
3. MonitorAlert 必须引用标准严重等级。
4. OpsMgmt 可以消费这些对象做运维治理，但不得回写业务域主数据。
