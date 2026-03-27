# WP06 CommNet 测试资产说明

本目录用于说明 CommNet 当前应对接的最小测试资产入口。

## 1. 当前映射

1. ../../contract/formal07_comm_link_and_security/

## 2. 重点验证内容

1. link_quality 正常发布。
2. link_degraded 异常触发。
3. security_event 安全事件上报。
4. topology_changed 与链路质量对象的边界。

## 3. 当前使用建议

1. 先按 [designArtifacts/delivery/BMS_Contract_Test_Baseline.md](../../../designArtifacts/delivery/BMS_Contract_Test_Baseline.md) 中 Formal 07 基线准备样例。
2. 再结合 [designArtifacts/delivery/BMS_MsgService_vs_CommNet_Responsibility_Matrix.md](../../../designArtifacts/delivery/BMS_MsgService_vs_CommNet_Responsibility_Matrix.md) 校对职责边界。
