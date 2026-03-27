# WP09 AuthAudit 测试资产说明

本目录用于说明 AuthAudit 当前应对接的最小测试资产入口。

## 1. 当前映射

1. ../../contract/formal10_ops_audit_and_monitoring/

## 2. 重点验证内容

1. audit_event 正常发布。
2. access_decision 记录链路。
3. SecurityEvent 纳入审计的关联路径。
4. 审计对象不反写监控或业务对象。

## 3. 当前使用建议

1. 先按 [designArtifacts/delivery/BMS_Contract_Test_Baseline.md](../../../designArtifacts/delivery/BMS_Contract_Test_Baseline.md) 中 Formal 10 基线准备样例。
2. 再结合 [designArtifacts/delivery/BMS_Execution_Index.md](../../../designArtifacts/delivery/BMS_Execution_Index.md) 对齐上下游联调对象。
