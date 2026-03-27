# BMS 工作包 12 BFF / HMI

本文档是 API Gateway / BFF / HMI 侧的可执行工作包，供软件工程师或 agent 直接领取并进入实现。

## 1. 基本信息

1. 分系统名称：API Gateway / BFF / HMI。
2. 负责人类型：软件工程师或 agent。
3. 对应 Container：plantumlC4/C4_L2_Container.puml 中 HMI 与 API Gateway / BFF。
4. 对应 Component 图：plantumlC4/C4_L3_Component_02_HMI.puml。
5. 对应 Code 图：无独立 code 图，当前以聚合视图对象和 Formal 11 为主依据。
6. 对应正式 ICD：BMS_ICD_Formal_11。

## 2. 目标范围

1. 聚合 TaskMgmt、SitMgmt、BattleCtrl、ResMgmt、MonitorLog 的只读数据，形成前端消费视图。
2. 输出 dashboard、alert_stream、task_panel、situation_panel 等推送和查询结果。
3. 处理前端订阅恢复、重连恢复与只读视图一致性。
4. 保持前端视图与业务主对象解耦，不反写业务主语义。
5. 作为主业务、运维告警和界面展示的统一只读入口。

不包含：

1. 直接订阅和处理后端 DDS 业务 topic 的前端实现。
2. 任务、态势、交战、资源等业务主对象的 owner 语义。
3. 运维审批、审计和发布执行本体实现。

## 3. 对象边界

### 3.1 主拥有对象

1. UiTaskSummary。
2. UiSituationSnapshot。
3. UiBattleOverview。
4. UiResourceOverview。
5. UiAlertItem。
6. UiDashboardResponse。
7. UiPushEnvelope。

### 3.2 只读消费对象

1. TaskMgmt 的任务摘要对象。
2. SitMgmt 的态势快照与威胁评估摘要。
3. BattleCtrl 的交战状态摘要。
4. ResMgmt 的资源状态摘要。
5. MonitorLog 的监控指标与告警摘要。

### 3.3 禁止越权修改

1. 不得把 UiDashboardResponse 或 UiTaskSummary 回写为业务主对象。
2. 不得让 HMI 前端直接绕过 BFF 订阅后端 DDS 业务 topic。
3. 不得在 BFF 中重新定义与 Formal 11 不兼容的 view_type、告警类型或严重等级。
4. 不得替代业务 owner 输出权威业务结论。

## 4. topic 责任

### 4.1 发布 topic

| topic | payload | 触发条件 | 下游 |
| --- | --- | --- | --- |
| bms/ui/push/dashboard | UiDashboardResponse | 首页聚合视图刷新 | HMI |
| bms/ui/push/alert_stream | UiPushEnvelope | 监控或业务告警推送 | HMI |
| bms/ui/push/task_panel | UiPushEnvelope | 任务摘要发生关键变化 | HMI |
| bms/ui/push/situation_panel | UiPushEnvelope | 态势快照或威胁摘要变化 | HMI |

### 4.2 订阅 topic

| topic | payload | 上游 | 消费动作 |
| --- | --- | --- | --- |
| bms/core/command/task/* | 任务域只读摘要 | TaskMgmt | 更新任务面板与 dashboard |
| bms/core/situation/* | 态势域只读摘要 | SitMgmt | 更新态势面板与 dashboard |
| bms/core/command/battle/* | 交战域只读摘要 | BattleCtrl | 更新交战概览 |
| bms/core/resource/state_snapshot | ResourceStateSnapshot | ResMgmt | 更新资源概览 |
| bms/core/ops/monitor/* | MonitorMetric, MonitorAlert | MonitorLog | 更新告警流与运维视图 |

## 5. 模块拆分

| 模块 | 责任 | 输入 | 输出 |
| --- | --- | --- | --- |
| QueryFacade | 提供前端查询入口 | 多域只读摘要 | 查询响应 |
| ViewAssembler | 组装 UiTaskSummary、UiSituationSnapshot 等视图对象 | 多域只读摘要 | UI 聚合对象 |
| PushGateway | 输出统一 UiPushEnvelope | UI 聚合对象 | dashboard, alert_stream 等推送 |
| SessionRecoveryService | 处理订阅恢复与重连恢复 | 会话状态, 最新视图快照 | 恢复推送 |
| ReadModelProjector | 维护只读聚合视图缓存 | 多域事件流 | 查询与推送读模型 |

## 6. 实施步骤

1. 先打通 dashboard 的多域聚合查询与推送主链。
2. 实现 alert_stream、task_panel、situation_panel 的只读推送。
3. 接入 SessionRecoveryService，完成重连恢复路径。
4. 对齐 BFF 视图契约清单，固化 view_type 和对象边界。
5. 最后与 HMI 和 MonitorLog 完成联合验收。

## 7. 测试与验收

### 7.1 必备样例

1. 正常样例：dashboard 多域聚合推送。
2. 异常样例：alert_stream 推送和前端重连恢复。
3. 边界样例：BFF 只读聚合，不反写业务主对象。

### 7.2 契约测试

1. UiDashboardResponse、UiPushEnvelope 和 view_type 必须符合 Formal 11。
2. Dashboard、Task Panel、Situation Panel 的对象边界必须符合视图契约清单。
3. HMI 不得直接消费后端 DDS 业务 topic。
4. 同一 trace_id 下多视图联动时，视图对象仍必须保持只读语义。

### 7.3 完成定义

1. BFF 读模型与推送主链已形成实现骨架。
2. dashboard 与 alert_stream 两条主链可验证。
3. 与 TaskMgmt、SitMgmt、BattleCtrl、ResMgmt、MonitorLog 的联调项已映射到联调矩阵。
4. 已准备 Formal 11 所需样例与验收记录。

## 8. 风险与待决项

1. 风险：多域刷新节奏不一致时，容易出现前端聚合视图短时不一致。
2. 风险：如果未严格控制只读边界，BFF 很容易演变成业务逻辑承载层。
3. 待决项：dashboard 增量刷新与全量刷新策略是否需要进一步量化阈值。
