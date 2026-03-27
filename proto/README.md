# BMS Proto 目录说明

当前目录用于承接 BMS 的分批公共 schema/IDL 定义。

## 当前已落地文件

1. bms/schema/common.proto
   公共头与基础枚举，包括任务类型、执行阶段、执行异常类型、航路动作、通信安全事件类型、链路等级、QoS 档位。
2. bms/schema/task.proto
   MissionCommand、ResourcePrerequisite、CoverageConstraint、TaskConstraint、TaskPackage。
3. bms/schema/battle.proto
   RouteSegment、KeyValueParameter、SensorProfile、WeaponProfile、BattlePlan。
4. bms/schema/execution.proto
   ExecutionStateSnapshot、ExecutionException。
5. bms/schema/situation.proto
   FusedTrack、ThreatAssessment、ThreatReasonRef、TargetFeatureSnapshot、TargetStatus，以及态势扩展枚举。
6. bms/schema/resource.proto
   AllocationRequest、AllocationDemand、AllocationTimeWindow、ResourceStateSnapshot、AllocationDecision。
7. bms/schema/message.proto
   MessageEnvelope、SchemaDescriptor、SubscriptionBinding、DeliveryReceipt、DeadLetterRecord、EndpointBinding、TopicDefinition，以及标准化 QoS 档位引用。
8. bms/schema/knowledge.proto
   InferenceRequest、RecommendationItem。
9. bms/schema/comm.proto
   TopologySnapshot、LinkQualitySnapshot、DegradationAlert、SecurityEvent，其中 LinkQualitySnapshot 已引用标准化链路等级。
10. bms/schema/persistence.proto
   DataOwnershipPolicy、StorageShardKey、RealtimeRecord、ArchiveRecord、SpatialTrackRecord、TargetFeatureRecord、GisTileRecord、IntelRecord。
11. bms/schema/ops.proto
   BackupSnapshot、DbMetricSnapshot。
12. bms/schema/simulation.proto
   ScenarioLoadCommand、ScenarioControlCommand、ClockTick、SimFlightState、SimSensorState、SimWeaponState、TargetTruth、WeaponAdjudication，以及仿真控制与裁决结果枚举。
13. bms/schema/platform.proto
   FlightState、NavigationState、PlatformAlert、CommandAck、MissionProgress，以及平台工程化子结构。
14. bms/schema/platform_command.proto
   FlightPlanUploadCommand、FlightModeSetCommand、TakeoffCommand、RtlCommand、LoiterCommand、TimeSyncCommand。
15. bms/schema/audit.proto
   AuditEvent、SecurityAlert。
16. bms/schema/monitor.proto
   MetricPoint、MonitorMetric、MonitorAlert。
17. bms/schema/bff.proto
   QueryFilter、UiTaskSummary、UiSituationSnapshot、UiBattleOverview、UiResourceOverview、UiAlertItem、UiDashboardRequest、UiDashboardResponse、UiPushEnvelope，以及标准化 UiViewType，其中 UiAlertItem 已引用标准化告警类型与严重等级。

## 当前范围

当前已覆盖三批对象：

1. 任务入域。
2. 任务包向计划层传递。
3. 交战计划向执行层传递。
4. 执行状态与执行异常回传。
5. 融合航迹与威胁评估对象。
6. 资源状态与资源分配对象。
7. 消息包络与主题定义对象。
8. 规则推理请求与推荐项对象。
9. 链路质量与通信安全事件对象。
10. ownership 到存储边界的持久化对象。
11. 数据库备份与指标快照对象。
12. 仿真控制、仿真状态、真值与裁决对象。
13. 无人机平台工程化状态与事件对象。
14. 平台控制命令骨架对象。
15. 审计与安全告警对象。
16. 监控指标与监控告警对象。
17. 前端聚合查询与推送视图对象。

## 下一批建议

1. 如需增强平台命令表达，再细化航路约束、起降参数、盘旋模式、授时语义。
2. 如需支撑部署发布，再补 deploy.proto 或 release.proto。
3. 如需把 BFF 进一步工程化，再补分页、排序、订阅恢复、增量推送语义。

## 维护规则

1. 公共对象字段变更，先更新 designArtifacts/schema/BMS_Schema_IDL_Baseline.md。
2. 跨分系统对象字段变更，先更新 designArtifacts/contracts/BMS_Code_Interface_Object_Catalog.md。
3. 不在业务 proto 中重复定义 CommonHeader。
4. 不在非 owner 包中复制 owner 对象定义。
