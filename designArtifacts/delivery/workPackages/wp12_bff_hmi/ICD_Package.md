# WP12 BFF_HMI ICD 设计包

## 1. 适用小组

1. API Gateway / BFF / HMI 实现小组。
2. 负责 dashboard、alert_stream、task_panel、situation_panel 聚合与推送的工程师或 agent。

## 2. 主工作包入口

1. [BMS_Work_Package_12_BFF_HMI.md](BMS_Work_Package_12_BFF_HMI.md)

## 3. 必读 Formal ICD

1. [BMS_ICD_Formal_11_BFF_Aggregation_And_UI_Push.md](../../../icd/BMS_ICD_Formal_11_BFF_Aggregation_And_UI_Push.md)

## 4. 必读补充设计文档

1. [BMS_BFF_View_Contract_Catalog.md](../../BMS_BFF_View_Contract_Catalog.md)
2. [BMS_Integration_Matrix.md](../../BMS_Integration_Matrix.md)
3. [BMS_Execution_Index.md](../../BMS_Execution_Index.md)

## 5. 本组重点确认项

1. UiDashboardResponse、UiPushEnvelope 和各 view_type 的边界。
2. BFF 只读聚合，不得反写业务主对象。
3. HMI 不得直接绕过 BFF 消费后端业务 topic。

## 6. 交付前核对清单

1. dashboard、alert_stream 和重连恢复样例已准备。
2. 视图对象与来源域映射已按契约清单核对。
3. 与 MonitorLog、TaskMgmt、SitMgmt、BattleCtrl、ResMgmt 的只读边界已验证。

## 7. 重点 topic 清单

1. 发布：bms/ui/push/dashboard。
2. 发布：bms/ui/push/alert_stream。
3. 发布：bms/ui/push/task_panel。
4. 发布：bms/ui/push/situation_panel。
5. 订阅：bms/core/command/task/*。
6. 订阅：bms/core/situation/*。
7. 订阅：bms/core/command/battle/*。
8. 订阅：bms/core/resource/state_snapshot。
9. 订阅：bms/core/ops/monitor/*。

## 8. 重点 payload 清单

1. UiDashboardResponse。
2. UiPushEnvelope。
3. UiTaskSummary。
4. UiSituationSnapshot。
5. UiBattleOverview。
6. UiResourceOverview。
7. UiAlertItem。

## 9. 样例与测试入口

1. [Formal 11 样例基线](../../BMS_Contract_Test_Baseline.md)
2. [BFF 视图契约清单](../../BMS_BFF_View_Contract_Catalog.md)
3. [主业务闭环联调场景](../../BMS_Core_Battle_Loop_Integration_Scenarios.md)

## 10. 小组签收清单

1. 已签收 dashboard、alert_stream 和恢复路径要求。
2. 已签收只读聚合边界。
3. 已确认 HMI 不直连后端业务 topic。

## 11. 字段级核对表

1. [Payload_Checklist.md](Payload_Checklist.md)
