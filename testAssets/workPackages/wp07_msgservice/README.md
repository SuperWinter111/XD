# WP07 MsgService 测试资产说明

本目录用于说明 MsgService 当前应对接的最小测试资产入口。

## 1. 当前映射

1. ../../contract/formal08_message_governance_and_delivery/

## 2. 重点验证内容

1. topic_defined 正常登记。
2. subscription_bound 的 success 或 rejected 治理语义。
3. delivery_receipt.success 与 failure 路径。
4. dead_letter 进入条件。
5. RetryScheduleEntry 只对可重试失败生成。
6. DeliveryReceipt 不代表业务处理完成。

## 3. 当前使用建议

1. 先按 [designArtifacts/delivery/BMS_Contract_Test_Baseline.md](../../../designArtifacts/delivery/BMS_Contract_Test_Baseline.md) 中 Formal 08 基线准备样例。
2. 再结合 [designArtifacts/delivery/BMS_MsgService_vs_CommNet_Responsibility_Matrix.md](../../../designArtifacts/delivery/BMS_MsgService_vs_CommNet_Responsibility_Matrix.md) 复核职责边界。
3. 补充验证 rejected 订阅是否同时生成 subscription_bound 事件与审计记录。
4. 补充验证 retry plan 是否可以稳定转成 schedule entry。
