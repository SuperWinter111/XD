# BMS 对象拥有权基线

本文档用于把跨分系统对象的 owner rule 固化为统一基线，避免多 agent 或多人并行开发时出现主对象越权写入、语义漂移和责任不清。

## 1. 文档定位

本文档不替代对象目录，而是把对象目录中的 owner 规则转成实施约束。

主要依据如下：

1. designArtifacts/contracts/BMS_Code_Interface_Object_Catalog.md。
2. designArtifacts/contracts/BMS_Container_Contract_Matrix.md。
3. designArtifacts/delivery/BMS_Subsystem_Design_Traceability_Matrix.md。
4. 各正式 ICD 专题文档。

## 2. 核心原则

1. 一个主对象只能有一个主拥有者分系统。
2. 主拥有者负责对象定义、权威写入、版本演进和对外权威发布。
3. 非主拥有者只能读取、缓存、裁剪、引用或生成派生视图，不能反向覆盖主对象。
4. 跨分系统写入只能通过正式 ICD、登记 topic 或明确同步接口完成，禁止私有旁路。
5. 聚合视图对象不获得业务主对象 ownership。
6. 仿真对象不冒充真实业务主对象。
7. 边缘原始状态映射不等于核心主数据 ownership。

## 3. 主对象 owner 总表

| 对象域 | 主对象或对象族 | 主拥有者 | 非 owner 可做什么 | 禁止事项 |
| --- | --- | --- | --- | --- |
| 任务域 | MissionCommand, TaskIntent, TaskConstraint, TaskGraph, TaskScheme, TaskPackage | TaskMgmt | 消费、引用、基于约束生成下游计划 | BattleCtrl 或 HMI 直接构造 TaskPackage |
| 计划与交战域 | BattlePlan, FormationScheme, RouteSegment, SensorProfile, WeaponProfile, AdjustmentOption, EngagementEffectReport | BattleCtrl | EnhanceUnit 读取并翻译为边缘动作 | TaskMgmt 直接生成 BattlePlan |
| 资源域 | ResourceRegistration, ResourceDescriptor, ResourceStateSnapshot, CapabilityProfile, AllocationDecision, ReservationTicket | ResMgmt | TaskMgmt、BattleCtrl 发起申请并消费裁定结果 | EnhanceUnit 直接发布核心 CapabilityProfile，申请方把请求当裁定 |
| 态势域 | FusedTrack, ThreatAssessment, TargetFeatureSnapshot, TargetStatus, SituationPicture | SitMgmt | BattleCtrl、HMI、KnowledgeRule 读取和引用 | TaskMgmt 以态势对象替代任务对象 |
| 知识规则域 | CombatRuleSet, TacticTemplate, TaskTemplate, DoctrineEntry, InferenceResult, RecommendationItem | KnowledgeRule | TaskMgmt、BattleCtrl、SitMgmt 读取或发起推理请求 | 推荐项直接覆盖任务、计划、态势主对象 |
| 边缘执行域 | PlatformCommand, PlatformState, PayloadState, WeaponState, TargetTrack, ExecutionStateSnapshot 的边缘原始映射 | EnhanceUnit | BattleCtrl 下发计划/命令，ResMgmt 与 SitMgmt 消费边缘上报 | EnhanceUnit 直接裁定任务、计划、资源结果 |
| 通信域 | LinkSession, LinkProfile, TopologySnapshot, LinkQualitySnapshot, DegradationAlert, SecurityEvent | CommNet | BattleCtrl、ResMgmt、MonitorLog 消费链路与安全结果 | 业务分系统自行定义链路质量权威结论 |
| 消息治理域 | TopicDefinition, EndpointBinding, SchemaDescriptor, MessageEnvelope, SubscriptionBinding, DeliveryReceipt, DeadLetterRecord | MsgService | 业务分系统按登记关系发布订阅 | 私自建立未登记 topic 或私有包络 |
| 仿真域 | ScenarioLoadCommand, ScenarioControlCommand, ClockTick, SimFlightState, SimSensorState, SimWeaponState, TargetTruth, WeaponAdjudication | Simulation | EnhanceUnit、SitMgmt、BattleCtrl 消费仿真输入 | 把仿真对象直接当真实对象写回主业务域 |
| 审计与监控域 | AuditEvent, SecurityAlert, MonitorMetric, MonitorAlert | AuthAudit, MonitorLog | OpsMgmt、HMI 读取展示 | 业务分系统绕过审计直接改写审计结论 |
| 前端聚合域 | UiDashboardResponse, UiPushEnvelope | BFF | HMI 读取展示 | BFF 反写业务主对象 |

## 4. 判定规则

当对象 ownership 存在争议时，按以下顺序判定：

1. 谁定义该对象的业务语义边界。
2. 谁对该对象承担最终裁定责任。
3. 谁负责该对象对外的权威发布。
4. 谁负责该对象的版本升级兼容。

如果四项答案不一致，优先以“最终裁定责任”和“权威发布责任”为准。

## 5. 常见边界澄清

1. EnhanceUnit 可以上报原始平台、载荷、武器状态，但不能把边缘原始能力参数直接提升为核心 CapabilityProfile。
2. BattleCtrl 可以根据 TaskPackage 生成 BattlePlan，但不能改写 TaskConstraint 后仍宣称其为原任务。
3. TaskMgmt 可以发起 AllocationRequest，但不能把 AllocationRequest 解释为 AllocationDecision。
4. SitMgmt 可以融合真实观测形成 FusedTrack，但不能把仿真 TargetTruth 冒充为实测融合态势。
5. KnowledgeRule 可以生成 RecommendationItem，但不能直接替代 BattlePlan、TaskPackage 或 FusedTrack。
6. BFF 可以聚合展示，但只能形成只读视图对象，不能获得业务主对象 ownership。

## 6. 落地要求

1. 每个工作包必须显式列出主拥有对象、只读消费对象和禁止事项。
2. 每条跨分系统 topic 必须能映射到 owner、publisher、consumer。
3. 契约测试必须至少覆盖 1 条 owner 不越权的负样例。
4. 如果需要调整 ownership，必须先走 designArtifacts/delivery/BMS_Change_Governance.md。
