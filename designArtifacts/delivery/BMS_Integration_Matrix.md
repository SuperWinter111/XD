# BMS 联调矩阵

本文档用于定义系统对系统的联调关系、关键 topic、mock 需求与验收口径。

## 1. 联调矩阵

| 上游 | 下游 | 关键 topic / 接口 | 关键 payload | mock 要求 | 验收重点 |
| --- | --- | --- | --- | --- | --- |
| 外部接口管理 | TaskMgmt | bms/core/command/task/command_received | MissionCommand | 任务指令样例集 | 指令入域、trace_id 传递、任务归一 |
| TaskMgmt | BattleCtrl | task/decomposed, task/plan_created | TaskConstraint, TaskPackage | 任务方案与约束样例 | 任务边界不被计划层改写 |
| BattleCtrl | EnhanceUnit | bms/edge/platform/command/* | 平台命令对象 | 航路、模式、起降、返航 mock | 命令翻译、应答、进度回传 |
| EnhanceUnit | BattleCtrl / TaskMgmt | mission_progress, command_ack, platform_alert | MissionProgress, CommandAck, PlatformAlert | 平台状态事件流 | 执行反馈、异常回退判断 |
| SitMgmt | BattleCtrl | fused_track, threat/assessed, target/* | FusedTrack, ThreatAssessment, TargetFeatureSnapshot, TargetStatus | 目标态势样例 | 观测层、特征层、威胁层不混用 |
| TaskMgmt / BattleCtrl | ResMgmt | allocation_requested | AllocationRequest | 资源申请样例 | 资源裁定、部分满足、预留占位 |
| ResMgmt | TaskMgmt / BattleCtrl | allocation_committed, resource/state_snapshot | AllocationDecision, ResourceStateSnapshot | 资源状态与分配样例 | owner 裁定权、生效时间窗 |
| CommNet | ResMgmt / BattleCtrl / MonitorLog | comm/link_quality, link_degraded, security_event | LinkQualitySnapshot, DegradationAlert, SecurityEvent | 链路劣化与安全事件样例 | 链路质量与异常解释一致 |
| SitMgmt / TaskMgmt / BattleCtrl | KnowledgeRule | knowledge/inference/requested | InferenceRequest | 推理输入引用样例 | 规则推理请求格式一致 |
| KnowledgeRule | SitMgmt / TaskMgmt / BattleCtrl | knowledge/inference/recommended | RecommendationItem | 推荐结果样例 | 推荐不越权直接发布业务主对象 |
| Simulation | EnhanceUnit / SitMgmt / BattleCtrl | bms/simulation/* | SimFlightState, TargetTruth, WeaponAdjudication | 仿真场景、时钟、裁决样例 | 仿真输入不冒充真实数据 |
| AuthAudit | MonitorLog | audit_event | AuditEvent | 操作与审计样例 | 审计可追溯 |
| MonitorLog | OpsMgmt / BFF | monitor/metric, monitor/alert | MonitorMetric, MonitorAlert | 指标与告警样例 | 运维展示与只读边界 |
| BFF | HMI | bms/ui/push/* | UiDashboardResponse, UiPushEnvelope | 推送样例与订阅恢复样例 | 前端只读聚合，不反写业务主域 |

## 2. 联调要求

1. 每条联调链必须至少准备 1 套正常样例和 1 套异常样例。
2. 所有联调样例都必须带 trace_id。
3. 上下游对同一 payload 的版本必须一致。
4. 联调通过标准必须写到各分系统验收清单中。
