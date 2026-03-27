# WP11 OpsMgmt ICD 设计包

## 1. 适用小组

1. 运维管理实现小组。
2. 负责 config_changed、incident_updated、ops_job、自检和流程治理的工程师或 agent。

## 2. 主工作包入口

1. [BMS_Work_Package_11_OpsMgmt.md](BMS_Work_Package_11_OpsMgmt.md)

## 3. 必读 Formal ICD

1. [BMS_ICD_Formal_10_Ops_Audit_And_Monitoring.md](../../../icd/BMS_ICD_Formal_10_Ops_Audit_And_Monitoring.md)

## 4. 必读补充设计文档

1. [BMS_VersionDeploy_OpsMgmt_Collaboration_Rules.md](../../BMS_VersionDeploy_OpsMgmt_Collaboration_Rules.md)
2. [BMS_Integration_Matrix.md](../../BMS_Integration_Matrix.md)
3. [BMS_Execution_Index.md](../../BMS_Execution_Index.md)

## 5. 本组重点确认项

1. config_changed、incident_updated、ops_job、自检结果的边界。
2. OpsMgmt 负责处置与流程，不负责发布和回滚执行。
3. 与 MonitorLog、AuthAudit、Version / Deploy 的协同边界必须清晰。

## 6. 交付前核对清单

1. config_changed、incident_updated、selfcheck_result 样例已准备。
2. 发布与回滚协同边界已按协作文档核对。
3. 运维流程记录与审计关联已验证。

## 7. 重点 topic 清单

1. 发布：bms/core/ops/config_changed。
2. 发布：bms/core/ops/job_dispatched。
3. 发布：bms/core/ops/selfcheck_result。
4. 发布：bms/core/ops/incident_updated。
5. 订阅：bms/core/ops/monitor/metric。
6. 订阅：bms/core/ops/monitor/alert。
7. 订阅：bms/core/ops/sec/audit_event。
8. 订阅：bms/core/ops/deploy/release_event。

## 8. 重点 payload 清单

1. ConfigChangeRecord。
2. OpsJobRecord。
3. SelfCheckResult。
4. IncidentTicket。
5. MonitorMetric。
6. MonitorAlert。
7. AuditEvent。
8. ReleaseEvent。

## 9. 样例与测试入口

1. [Formal 10 样例基线](../../BMS_Contract_Test_Baseline.md)
2. [VersionDeploy 与 OpsMgmt 协同约束](../../BMS_VersionDeploy_OpsMgmt_Collaboration_Rules.md)

## 10. 小组签收清单

1. 已签收配置、处置、作业、自检对象边界。
2. 已签收与 Version / Deploy 的协同规则。
3. 已确认不越权执行发布和回滚。

## 11. 字段级核对表

1. [Payload_Checklist.md](Payload_Checklist.md)
