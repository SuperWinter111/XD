# WP12 BFF_HMI 测试资产说明

本目录用于说明 BFF / HMI 当前应对接的最小测试资产入口。

## 1. 当前映射

1. ../../contract/formal11_bff_aggregation_and_ui_push/
2. ../../integration/core_battle_loop/ 中与前端演示相关的联调基线。

## 2. 重点验证内容

1. dashboard 推送。
2. alert_stream 推送。
3. 前端重连恢复。
4. BFF 只读聚合边界。

## 3. 当前使用建议

1. 先按 [designArtifacts/delivery/BMS_Contract_Test_Baseline.md](../../../designArtifacts/delivery/BMS_Contract_Test_Baseline.md) 中 Formal 11 基线准备样例。
2. 再结合 [designArtifacts/delivery/BMS_BFF_View_Contract_Catalog.md](../../../designArtifacts/delivery/BMS_BFF_View_Contract_Catalog.md) 对齐视图对象边界。
