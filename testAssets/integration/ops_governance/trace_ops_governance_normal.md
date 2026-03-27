# 运维治理链路示例

1. MonitorLog 发布 monitor_alert。
2. OpsMgmt 接收告警并生成 incident_updated。
3. AuthAudit 记录 audit_event。
4. VersionDeploy 消费运维结论进行发布阻断或放行判断。
