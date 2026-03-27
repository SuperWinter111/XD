# WP11 OpsMgmt 测试资产说明

本目录用于说明 OpsMgmt 当前应对接的最小测试资产入口。

## 1. 当前映射

1. ../../contract/formal10_ops_audit_and_monitoring/

## 2. 重点验证内容

1. config_changed 正常发布。
2. incident_updated 处置链路。
3. selfcheck_result 输出。
4. 与 Version / Deploy 的协同边界。

## 3. 当前使用建议

1. 先按 [designArtifacts/delivery/BMS_Contract_Test_Baseline.md](../../../designArtifacts/delivery/BMS_Contract_Test_Baseline.md) 中 Formal 10 基线准备样例。
2. 再结合 [designArtifacts/delivery/BMS_VersionDeploy_OpsMgmt_Collaboration_Rules.md](../../../designArtifacts/delivery/BMS_VersionDeploy_OpsMgmt_Collaboration_Rules.md) 校对协同规则。
