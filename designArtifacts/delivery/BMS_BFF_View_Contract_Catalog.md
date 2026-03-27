# BMS BFF 视图契约清单

本文档用于把 BFF/HMI 的聚合视图进一步收敛成可执行视图契约，明确每类视图的来源域、刷新方式、推送通道和禁止事项。

## 1. 文档定位

本文档是 [BMS_Work_Package_12_BFF_HMI.md](workPackages/wp12_bff_hmi/BMS_Work_Package_12_BFF_HMI.md) 和 [BMS_ICD_Formal_11_BFF_Aggregation_And_UI_Push.md](../icd/BMS_ICD_Formal_11_BFF_Aggregation_And_UI_Push.md) 的细化补充。

它解决的问题是：

1. 每种视图到底聚合哪些域对象。
2. 每种视图走查询、推送还是两者结合。
3. 哪些字段属于只读展示对象，不能反写业务域。

## 2. 视图对象总表

| 视图对象 | 主 owner | 主要来源域 | 输出形态 | 刷新方式 | 推送 view_type |
| --- | --- | --- | --- | --- | --- |
| UiTaskSummary | BFF | TaskMgmt | 查询结果或嵌入 dashboard | 主动查询 + 关键变更推送 | TASK_PANEL |
| UiSituationSnapshot | BFF | SitMgmt | 查询结果或嵌入 dashboard | 订阅驱动 + 定时刷新 | SITUATION_PANEL |
| UiBattleOverview | BFF | BattleCtrl | 查询结果或嵌入 dashboard | 关键状态推送 | DASHBOARD |
| UiResourceOverview | BFF | ResMgmt | 查询结果或嵌入 dashboard | 定时刷新 + 关键变化推送 | DASHBOARD |
| UiAlertItem | BFF | MonitorLog, BattleCtrl, SitMgmt | alert_stream 项 | 事件推送 | ALERT_STREAM |
| UiDashboardResponse | BFF | 多域聚合 | dashboard 主对象 | 查询 + 推送 | DASHBOARD |
| UiPushEnvelope | BFF | BFF 聚合结果 | 统一推送包络 | 事件推送 | DASHBOARD, ALERT_STREAM, TASK_PANEL, SITUATION_PANEL |

## 3. 视图级契约

### 3.1 Dashboard

1. 目标：提供首页总览视图。
2. 聚合来源：UiTaskSummary、UiSituationSnapshot、UiBattleOverview、UiResourceOverview、UiAlertItem 摘要。
3. 输出对象：UiDashboardResponse 或封装后的 UiPushEnvelope。
4. 刷新策略：
   1. 首次进入时主动拉取。
   2. 关键状态变化时推送增量或快照。
5. 禁止：把 dashboard 的汇总结果当成任务、态势、交战、资源主对象回写业务域。

### 3.2 Alert Stream

1. 目标：提供统一告警流。
2. 聚合来源：MonitorAlert 为主，必要时引用 BattleCtrl、SitMgmt 的只读异常摘要。
3. 输出对象：UiAlertItem，经 UiPushEnvelope 推送。
4. 刷新策略：事件驱动推送。
5. 禁止：在 BFF 外部重定义不兼容的 UiAlertType 或严重等级文本。

### 3.3 Task Panel

1. 目标：提供任务摘要、任务进度和方案结果展示。
2. 聚合来源：TaskMgmt 只读结果，必要时引用 BattleCtrl 的执行摘要。
3. 输出对象：UiTaskSummary，经 UiPushEnvelope 推送或查询返回。
4. 刷新策略：主动查询为主，关键状态变化时推送。
5. 禁止：把任务面板对象当作 TaskPackage 回写 TaskMgmt。

### 3.4 Situation Panel

1. 目标：提供态势快照、威胁摘要和地图联动展示。
2. 聚合来源：SitMgmt，必要时引用 MonitorLog 告警摘要和 BattleCtrl 的战术态势摘要。
3. 输出对象：UiSituationSnapshot，经 UiPushEnvelope 推送或查询返回。
4. 刷新策略：订阅驱动 + 定时快照刷新。
5. 禁止：把态势面板对象当作 SituationPicture 或 ThreatAssessment 回写 SitMgmt。

## 4. UiPushEnvelope 使用规则

1. channel 表示推送通道，不表达业务语义 owner。
2. view_type 必须使用 Formal 11 已定义枚举。
3. payload_bytes 只承载对应视图负载，不允许跨视图混装无关对象。
4. 同一个 trace_id 下允许多视图联动，但每个视图对象仍保持只读语义。

## 5. 最小测试要求

1. Dashboard：至少 1 套多域聚合正常样例和 1 套增量刷新样例。
2. Alert Stream：至少 1 套告警推送样例和 1 套前端重连恢复样例。
3. Task Panel：至少 1 套任务进度刷新样例。
4. Situation Panel：至少 1 套态势快照推送样例。
