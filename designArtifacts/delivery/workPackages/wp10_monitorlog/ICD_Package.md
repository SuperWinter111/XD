# WP10 MonitorLog ICD 设计包

## 1. 适用小组

1. 监控与日志实现小组。
2. 负责 metric、alert、日志汇总和 trace 关联的工程师或 agent。

## 2. 主工作包入口

1. [BMS_Work_Package_10_MonitorLog.md](BMS_Work_Package_10_MonitorLog.md)

## 3. 必读 Formal ICD

1. [BMS_ICD_Formal_10_Ops_Audit_And_Monitoring.md](../../../icd/BMS_ICD_Formal_10_Ops_Audit_And_Monitoring.md)

## 4. 必读补充设计文档

1. [BMS_BFF_View_Contract_Catalog.md](../../BMS_BFF_View_Contract_Catalog.md)
2. [BMS_VersionDeploy_OpsMgmt_Collaboration_Rules.md](../../BMS_VersionDeploy_OpsMgmt_Collaboration_Rules.md)
3. [BMS_Execution_Index.md](../../BMS_Execution_Index.md)

## 5. 本组重点确认项

1. MonitorMetric 与 MonitorAlert 的边界。
2. dead_letter、link_degraded、security_event、audit_event 的汇聚口径。
3. 告警只读输出，不得反写业务主域。

## 6. 交付前核对清单

1. metric、alert 和 trace 聚合样例已准备。
2. 与 AuthAudit、MsgService、CommNet、OpsMgmt、BFF 的输入输出边界已核对。
3. 告警等级与界面视图口径一致。

## 7. 重点 topic 清单

1. 发布：bms/core/ops/monitor/metric。
2. 发布：bms/core/ops/monitor/alert。
3. 发布：bms/core/ops/monitor/log_digest。
4. 订阅：bms/core/ops/msg/delivery_receipt。
5. 订阅：bms/core/ops/msg/dead_letter。
6. 订阅：bms/core/ops/comm/link_quality。
7. 订阅：bms/core/ops/comm/link_degraded。
8. 订阅：bms/core/ops/sec/audit_event。
9. 订阅：bms/core/ops/deploy/release_event。

## 8. 重点 payload 清单

1. MonitorMetric。
2. MonitorAlert。
3. LogDigest。
4. DeliveryReceipt。
5. DeadLetterRecord。
6. LinkQualitySnapshot。
7. SecurityEvent。
8. AuditEvent。
9. ReleaseEvent。

## 9. 样例与测试入口

1. [Formal 10 样例基线](../../BMS_Contract_Test_Baseline.md)
2. [BFF 视图契约清单](../../BMS_BFF_View_Contract_Catalog.md)
3. [VersionDeploy 与 OpsMgmt 协同约束](../../BMS_VersionDeploy_OpsMgmt_Collaboration_Rules.md)

## 10. 小组签收清单

1. 已签收 metric 与 alert 边界。
2. 已签收多域输入来源映射。
3. 已确认监控对象只读输出，不反写业务域。

## 11. 字段级核对表

1. [Payload_Checklist.md](Payload_Checklist.md)
