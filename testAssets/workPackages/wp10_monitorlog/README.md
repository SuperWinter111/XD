# WP10 MonitorLog 测试资产说明

本目录用于说明 MonitorLog 当前应对接的最小测试资产入口。

## 1. 当前映射

1. ../../contract/formal10_ops_audit_and_monitoring/

## 2. 重点验证内容

1. MonitorMetric 聚合。
2. MonitorAlert 触发与升级。
3. dead_letter、link_degraded、security_event 的汇聚。
4. trace_id 关联查询。

## 3. 当前使用建议

1. 先按 [designArtifacts/delivery/BMS_Contract_Test_Baseline.md](../../../designArtifacts/delivery/BMS_Contract_Test_Baseline.md) 中 Formal 10 基线准备样例。
2. 再结合 [designArtifacts/delivery/BMS_BFF_View_Contract_Catalog.md](../../../designArtifacts/delivery/BMS_BFF_View_Contract_Catalog.md) 校对告警展示口径。
