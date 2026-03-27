# BMS 正式 ICD 专题 11 BFF 聚合视图与 UI 推送

本文档定义 API Gateway / BFF 面向 HMI 的聚合查询与推送视图接口约束。

## 1. Topic 与对象绑定

| topic | payload | 发布方 | 订阅方 | QoS |
| --- | --- | --- | --- | --- |
| bms/ui/push/dashboard | bms.schema.bff.UiPushEnvelope 或 UiDashboardResponse | API Gateway / BFF | HMI 前端 | QOS-ALERT |
| bms/ui/push/alert_stream | bms.schema.bff.UiPushEnvelope | API Gateway / BFF | HMI 前端 | QOS-ALERT |

## 2. 聚合视图边界

1. UiDashboardResponse 是只读聚合视图。
2. UiTaskSummary、UiSituationSnapshot、UiBattleOverview、UiResourceOverview、UiAlertItem 都是展示对象。
3. BFF 不拥有任务、态势、交战、资源主语义。

## 3. UiPushEnvelope 规则

UiPushEnvelope 已收敛为标准化 view_type：

1. DASHBOARD。
2. ALERT_STREAM。
3. TASK_PANEL。
4. SITUATION_PANEL。

规则：

1. channel 表示推送通道。
2. view_type 表示前端视图类型。
3. payload_bytes 承载具体视图负载。

## 4. 工程规则

1. BFF 可聚合多个域对象，但不得把聚合结果反向写回业务分系统作为权威对象。
2. UiAlertItem 必须继续使用标准化 UiAlertType 与 ExceptionSeverity。
3. HMI 前端只消费 BFF 输出，不直接订阅后端 DDS 业务 topic。
