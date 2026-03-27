# WP09 AuthAudit ICD 设计包

## 1. 适用小组

1. 权限与安全审计实现小组。
2. 负责 audit_event、access_decision 和安全审计关联的工程师或 agent。

## 2. 主工作包入口

1. [BMS_Work_Package_09_AuthAudit.md](BMS_Work_Package_09_AuthAudit.md)

## 3. 必读 Formal ICD

1. [BMS_ICD_Formal_10_Ops_Audit_And_Monitoring.md](../../../icd/BMS_ICD_Formal_10_Ops_Audit_And_Monitoring.md)

## 4. 必读补充设计文档

1. [BMS_Integration_Matrix.md](../../BMS_Integration_Matrix.md)
2. [BMS_Execution_Index.md](../../BMS_Execution_Index.md)

## 5. 本组重点确认项

1. AuditEvent 与 AccessDecisionRecord 的边界。
2. SecurityEvent 纳入审计时必须保留原始来源。
3. 审计对象不得替代 MonitorLog 的监控对象。

## 6. 交付前核对清单

1. audit_event 与 access_decision 样例已准备。
2. 与 CommNet、MonitorLog、OpsMgmt 的边界已核对。
3. 高危动作与安全事件的追溯链已验证。

## 7. 重点 topic 清单

1. 发布：bms/core/ops/sec/audit_event。
2. 发布：bms/core/ops/sec/access_decision。
3. 订阅：bms/core/ops/comm/security_event。
4. 订阅：bms/ui/user_action/*。

## 8. 重点 payload 清单

1. AuditEvent。
2. AccessDecisionRecord。
3. SecurityEvent。
4. SecurityReviewRecord。

## 9. 样例与测试入口

1. [Formal 10 样例基线](../../BMS_Contract_Test_Baseline.md)
2. [BMS_Execution_Index.md](../../BMS_Execution_Index.md)

## 10. 小组签收清单

1. 已签收审计对象边界。
2. 已签收安全事件纳入审计的保真规则。
3. 已确认不替代监控和运维对象。

## 11. 字段级核对表

1. [Payload_Checklist.md](Payload_Checklist.md)
