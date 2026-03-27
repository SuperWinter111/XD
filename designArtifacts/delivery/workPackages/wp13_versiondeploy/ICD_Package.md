# WP13 VersionDeploy ICD 设计包

## 1. 适用小组

1. 版本与部署实现小组。
2. 负责 release_event、环境阻断、部署执行和回滚执行的工程师或 agent。

## 2. 主工作包入口

1. [BMS_Work_Package_13_VersionDeploy.md](BMS_Work_Package_13_VersionDeploy.md)

## 3. 必读 Formal ICD

1. [BMS_ICD_Formal_10_Ops_Audit_And_Monitoring.md](../../../icd/BMS_ICD_Formal_10_Ops_Audit_And_Monitoring.md)

## 4. 必读补充设计文档

1. [BMS_VersionDeploy_OpsMgmt_Collaboration_Rules.md](../../BMS_VersionDeploy_OpsMgmt_Collaboration_Rules.md)
2. [BMS_Integration_Matrix.md](../../BMS_Integration_Matrix.md)
3. [BMS_Execution_Index.md](../../BMS_Execution_Index.md)

## 5. 本组重点确认项

1. release_event 与 rollback_record 的边界。
2. 发布审批协同与发布执行权边界。
3. 环境阻断、发布失败和回滚的触发来源必须可追溯。

## 6. 交付前核对清单

1. 发布成功、发布失败、环境阻断和回滚样例已准备。
2. 与 OpsMgmt、MonitorLog 的协同边界已按协作文档核对。
3. release_event 的关键状态覆盖已验证。

## 7. 重点 topic 清单

1. 发布：bms/core/ops/deploy/release_event。
2. 发布：bms/core/ops/deploy/rollback_record。
3. 订阅：bms/core/ops/config_changed。
4. 订阅：bms/core/ops/monitor/alert。
5. 订阅：bms/core/ops/monitor/metric。
6. 订阅：bms/core/ops/incident_updated。

## 8. 重点 payload 清单

1. ReleaseEvent。
2. ReleasePlan。
3. EnvironmentCheckResult。
4. RollbackExecutionRecord。
5. ConfigChangeRecord。
6. MonitorAlert。
7. IncidentTicket。

## 9. 样例与测试入口

1. [Formal 10 样例基线](../../BMS_Contract_Test_Baseline.md)
2. [VersionDeploy 与 OpsMgmt 协同约束](../../BMS_VersionDeploy_OpsMgmt_Collaboration_Rules.md)

## 10. 小组签收清单

1. 已签收发布、阻断和回滚边界。
2. 已签收与 OpsMgmt、MonitorLog 的协同规则。
3. 已确认 release_event 关键状态覆盖完整。

## 11. 字段级核对表

1. [Payload_Checklist.md](Payload_Checklist.md)
