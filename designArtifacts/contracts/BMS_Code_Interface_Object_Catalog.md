# BMS Code Diagram 跨分系统接口对象清单

本文档用于约束 Code Diagram 阶段的跨分系统对象边界，避免任务对象、计划对象、态势对象、执行反馈对象在代码实现时再次混用。

## 1. 使用原则

1. 对象命名优先反映语义边界，而不是传输介质。
2. 一个对象只能有一个主拥有者分系统。
3. 对象跨分系统流转时，可以做适配或裁剪，但不得改变其原始语义层级。
4. TaskMgmt 不直接生成平台级执行对象。
5. BattleCtrl 不直接修改任务目标、MOE、任务时窗等任务语义对象。
6. SitMgmt 不直接输出任务包或交战计划。
7. EnhanceUnit 只消费计划语义和平台控制语义，不消费上级原始任务文书语义。

## 2. 核心对象分层

| 语义层 | 核心对象 | 主拥有者 | 下游消费者 | 说明 |
| --- | --- | --- | --- | --- |
| 指令语义 | MissionCommand | TaskMgmt | TaskMgmt | 原始任务文书、上级命令、人工录入指令 |
| 任务语义 | TaskIntent | TaskMgmt | TaskMgmt | 归一化后的任务意图 |
| 任务语义 | TaskConstraint | TaskMgmt | BattleCtrl | 任务目标、时窗、MOE、依赖、覆盖等约束 |
| 任务语义 | TaskGraph | TaskMgmt | TaskMgmt | 任务分解结果与任务网络 |
| 任务语义 | TaskScheme | TaskMgmt | HMI, TaskMgmt | 候选任务方案，用于方案比选 |
| 任务语义 | TaskPackage | TaskMgmt | BattleCtrl | 经确认的任务包，是任务层对计划层的正式输入 |
| 态势语义 | FusedTrack | SitMgmt | BattleCtrl, HMI | 融合航迹 |
| 态势语义 | ThreatAssessment | SitMgmt | BattleCtrl, HMI | 威胁等级、优先级、危险区域 |
| 态势语义 | TargetFeatureSnapshot | SitMgmt | BattleCtrl, HMI, KnowledgeRule | 目标观察特征快照，不等于知识域目标画像 |
| 态势语义 | TargetStatus | SitMgmt | BattleCtrl, HMI | 目标位置、坐标系与毁伤状态快照 |
| 态势语义 | ThreatReasonRef | SitMgmt, KnowledgeRule | BattleCtrl, HMI | 威胁理由引用与证据摘要 |
| 态势语义 | SituationPicture | SitMgmt | BattleCtrl, HMI | 态势全景 |
| 态势语义 | InferenceResult | SitMgmt | BattleCtrl, HMI | 意图预测、趋势推演、置信度 |
| 资源语义 | ResourceStateSnapshot | ResMgmt | TaskMgmt, BattleCtrl, HMI | 平台、载荷、链路、能源的统一状态快照 |
| 资源语义 | CapabilityProfile | ResMgmt | TaskMgmt, BattleCtrl | 平台/载荷/武器/链路能力模型 |
| 资源语义 | TaskCapabilityMatrix | ResMgmt | TaskMgmt, BattleCtrl | 任务类型到资源能力的匹配矩阵 |
| 资源语义 | AllocationRequest | TaskMgmt, BattleCtrl | ResMgmt | 资源申请对象 |
| 资源语义 | AllocationDecision | ResMgmt | TaskMgmt, BattleCtrl, HMI | 资源分配、冲突仲裁、预留结果 |
| 资源语义 | ReservationTicket | ResMgmt | TaskMgmt, BattleCtrl | 资源预留与释放凭证 |
| 消息契约语义 | TopicDefinition | MsgService | 全部分系统 | 主题、QoS、路由与访问策略定义 |
| 消息契约语义 | EndpointBinding | MsgService | 全部分系统 | 主题端点绑定对象，描述发布者/订阅者的结构化登记信息 |
| 消息契约语义 | SchemaDescriptor | MsgService | 全部分系统 | 消息结构、版本与字段映射描述 |
| 消息契约语义 | MessageEnvelope | MsgService | 全部分系统 | 统一消息包络，携带 trace_id、event_time 等公共字段 |
| 消息契约语义 | SubscriptionBinding | MsgService | 全部分系统 | 订阅关系与分发绑定 |
| 消息契约语义 | DeliveryReceipt | MsgService | 发布者、监控分系统 | 投递确认与重发依据 |
| 消息契约语义 | DeadLetterRecord | MsgService | MsgService, 监控分系统 | 无法成功投递的死信记录 |
| 知识规则语义 | CombatRuleSet | KnowledgeRule | TaskMgmt, BattleCtrl | 已发布的交战规则集合 |
| 知识规则语义 | TacticTemplate | KnowledgeRule | BattleCtrl | 战术模板主对象 |
| 知识规则语义 | TaskTemplate | KnowledgeRule | TaskMgmt | 任务模板主对象 |
| 知识规则语义 | TargetFeatureProfile | KnowledgeRule | SitMgmt | 目标特征知识对象 |
| 知识规则语义 | DoctrineEntry | KnowledgeRule | TaskMgmt, BattleCtrl, SitMgmt | 条令条目与场景约束 |
| 知识规则语义 | InferenceRequest | TaskMgmt, BattleCtrl, SitMgmt | KnowledgeRule | 规则推理请求对象 |
| 知识规则语义 | RecommendationItem | KnowledgeRule | TaskMgmt, BattleCtrl, SitMgmt | 推理后的推荐项或解释结果 |
| 通信语义 | LinkSession | CommNet | EnhanceUnit, ExtInterface | 通信链路会话对象 |
| 通信语义 | LinkProfile | CommNet | ResMgmt, MonitorLog | 带宽、冗余、优先级等链路配置画像 |
| 通信语义 | TopologySnapshot | CommNet | MonitorLog, OpsMgmt | 当前网络拓扑快照 |
| 通信语义 | RoutePath | CommNet | CommNet | 组网路由路径对象 |
| 通信语义 | LinkQualitySnapshot | CommNet | ResMgmt, BattleCtrl, MonitorLog | 丢包、时延、带宽、链路等级等质量快照 |
| 通信语义 | DegradationAlert | CommNet | BattleCtrl, MonitorLog | 链路降级与通信异常告警 |
| 通信语义 | SecurityEvent | CommNet | AuthAudit, MonitorLog | 认证失败、干扰、保密异常等通信安全事件 |
| 持久化语义 | DataOwnershipPolicy | DbMgmt | 全部分系统 | ownership 到存储边界的映射策略 |
| 持久化语义 | StorageShardKey | DbMgmt | DbMgmt | 分库、分区、索引路由键 |
| 持久化语义 | RealtimeRecord | DbMgmt | TaskMgmt, SitMgmt, ResMgmt | 实时态、缓存态、短保留记录 |
| 持久化语义 | ArchiveRecord | DbMgmt | TaskMgmt, BattleCtrl, ResMgmt | 历史归档记录 |
| 持久化语义 | SpatialTrackRecord | DbMgmt | SitMgmt, HMI | 时空轨迹记录 |
| 持久化语义 | TargetFeatureRecord | DbMgmt | KnowledgeRule | 目标特征持久化记录 |
| 持久化语义 | GisTileRecord | DbMgmt | HMI | GIS 瓦片与空间底图记录 |
| 持久化语义 | IntelRecord | DbMgmt | SitMgmt | 情报持久化记录 |
| 持久化语义 | BackupSnapshot | DbMgmt | DbMgmt, MonitorLog | 备份快照与恢复点 |
| 持久化语义 | DbMetricSnapshot | DbMgmt | MonitorLog, OpsMgmt | 数据库性能与容量指标快照 |
| 仿真语义 | ScenarioLoadCommand | Simulation | 仿真器集群 | 仿真场景加载命令 |
| 仿真语义 | ScenarioControlCommand | Simulation | 仿真器集群 | 仿真开始、暂停、停止控制命令 |
| 仿真语义 | ClockTick | Simulation | 仿真器集群, EnhanceUnit | 仿真时钟推进事件 |
| 仿真语义 | SimFlightState | Simulation | EnhanceUnit, Replay | 仿真飞行状态 |
| 仿真语义 | SimSensorState | Simulation | EnhanceUnit, Replay | 仿真传感器状态 |
| 仿真语义 | SimWeaponState | Simulation | EnhanceUnit, Replay | 仿真武器状态 |
| 仿真语义 | TargetTruth | Simulation | SitMgmt, Replay, Eval | 真值目标对象 |
| 仿真语义 | WeaponAdjudication | Simulation | BattleCtrl, Replay | 仿真裁决结果 |
| 审计语义 | AuditEvent | AuthAudit | MonitorLog, OpsMgmt | 审计事件对象 |
| 审计语义 | SecurityAlert | AuthAudit | MonitorLog, OpsMgmt | 安全告警对象 |
| 监控语义 | MonitorMetric | MonitorLog | OpsMgmt, HMI | 统一监控指标对象 |
| 监控语义 | MonitorAlert | MonitorLog | OpsMgmt, HMI | 统一监控告警对象 |
| 聚合视图语义 | UiDashboardResponse | BFF | HMI | 前端总览聚合响应对象 |
| 聚合视图语义 | UiPushEnvelope | BFF | HMI | 前端推送包络对象 |
| 计划语义 | BattlePlan | BattleCtrl | EnhanceUnit, HMI | 交战计划总对象 |
| 计划语义 | FormationScheme | BattleCtrl | BattleCtrl | 编队构型与协同关系 |
| 计划语义 | RouteSegment | BattleCtrl | EnhanceUnit | 航路/航段 |
| 计划语义 | SensorProfile | BattleCtrl | EnhanceUnit | 载荷模式 |
| 计划语义 | WeaponProfile | BattleCtrl | EnhanceUnit | 武器动作与用法 |
| 执行语义 | ExecutionStateSnapshot | EnhanceUnit, BattleCtrl | BattleCtrl, TaskMgmt, HMI | 执行状态快照 |
| 执行语义 | ExecutionException | EnhanceUnit, BattleCtrl | BattleCtrl, TaskMgmt | 计划执行异常 |
| 任务闭环语义 | TaskExecutionSnapshot | TaskMgmt | HMI, TaskMgmt | 任务执行进度与闭环态 |
| 评估语义 | EngagementEffectReport | BattleCtrl | TaskMgmt, HMI | 打击效果评估 |
| 评估语义 | EffectivenessReport | TaskMgmt | HMI, 上级系统 | 任务效能评估 |

## 3. 关键对象边界说明

### MissionCommand

1. 来源：上级系统、HMI。
2. 语义：原始命令与文书。
3. 终点：只在 TaskMgmt 内部被解析与归一化。
4. 禁止：直接传入 BattleCtrl 或 EnhanceUnit。

### TaskConstraint

1. 来源：TaskMgmt。
2. 内容：任务目标、任务起止时间、MOE、任务依赖、结构化资源前提、结构化覆盖约束。
3. 下游：BattleCtrl 只能消费，不拥有定义权。
4. 禁止：BattleCtrl 擅自改写 TaskConstraint 后继续视为原任务。

### TaskPackage

1. 来源：TaskMgmt。
2. 内容：任务约束、任务类型、任务网络摘要、资源前提、确认后的任务方案标识。
3. 作用：作为 BattleCtrl 的唯一正式任务输入对象。
4. 禁止：HMI 绕过 TaskMgmt 直接构造 TaskPackage。

### FusedTrack

1. 来源：SitMgmt。
2. 内容：融合后的航迹、目标属性、可信度、关联来源。
3. 下游：BattleCtrl 用于目标分配和战术匹配，HMI 用于展示。
4. 禁止：TaskMgmt 直接以 FusedTrack 替代任务对象。

### ResourceStateSnapshot

1. 来源：ResMgmt。
2. 内容：平台在线状态、健康度、能源余量、载荷状态、链路质量、可用性结论。
3. 下游：TaskMgmt 用于资源前提判断，BattleCtrl 用于计划可执行性校核，HMI 用于资源总览。
4. 禁止：BattleCtrl 或 TaskMgmt 私自拼装新的全局资源状态并覆盖 ResMgmt 的主状态语义。

### CapabilityProfile

1. 来源：ResMgmt。
2. 内容：平台、传感器、武器、链路的能力属性与差异化标签。
3. 下游：TaskMgmt 用于任务分解与资源前提匹配，BattleCtrl 用于计划生成与成员选择。
4. 禁止：EnhanceUnit 直接把边缘原始参数结构当作核心 CapabilityProfile 对外发布。

### AllocationRequest

1. 来源：TaskMgmt 或 BattleCtrl。
2. 内容：资源需求项、期望时间窗、触发模式、申请策略、偏好与排除资源集合。
3. 下游：ResMgmt 作为唯一裁定者接收并生成 AllocationDecision。
4. 禁止：申请方把 AllocationRequest 直接解释为已确认分配结果。

### AllocationDecision

1. 来源：ResMgmt。
2. 内容：资源分配结果、冲突仲裁结果、预留状态、释放策略、优先级裁决。
3. 下游：TaskMgmt 和 BattleCtrl 只能消费 AllocationDecision，不拥有最终裁定权。
4. 禁止：TaskMgmt 或 BattleCtrl 在未经过 ResMgmt 的情况下单方面确认资源分配结果。

### SensorProfile

1. 来源：BattleCtrl。
2. 内容：载荷模式与结构化参数列表。
3. 下游：EnhanceUnit 用于平台侧载荷模式装载与适配。
4. 禁止：将 parameters 重新退化为无约束字符串列表后作为权威对象对外发布。

### WeaponProfile

1. 来源：BattleCtrl。
2. 内容：武器动作模式与结构化参数列表。
3. 下游：EnhanceUnit 用于平台侧武器动作装载与适配。
4. 禁止：将 parameters 重新退化为无约束字符串列表后作为权威对象对外发布。

### MessageEnvelope

1. 来源：MsgService。
2. 内容：业务 payload 的统一包络，至少包含 trace_id、event_time、source_id、schema_version 与标准化 QosProfile 等公共字段。
3. 下游：全部分系统都可消费，但不得越过包络直接约定私有链路格式。
4. 禁止：业务分系统各自定义互不兼容的消息包络。

### TopicDefinition

1. 来源：MsgService。
2. 内容：主题名、标准化 QoS 档位、结构化发布/订阅端点绑定、路由策略、优先级策略。
3. 下游：业务分系统只能基于 TopicDefinition 声明发布与订阅关系。
4. 禁止：业务分系统绕过 TopicDefinition 私下建立未登记主题。

### EndpointBinding

1. 来源：MsgService。
2. 内容：端点标识、端点类型、归属域、内外部属性等主题参与者登记信息。
3. 下游：TopicDefinition、消息治理、访问控制、订阅关系校验。
4. 禁止：业务分系统继续以自由字符串私下维护发布者/订阅者名单。

### DeadLetterRecord

1. 来源：MsgService。
2. 内容：失败消息摘要、失败原因、重试次数、最后投递时间、原主题信息。
3. 下游：监控与日志分系统、消息服务自身恢复流程。
4. 禁止：将 DeadLetterRecord 当作业务事件重新投递给业务分系统处理。

### CombatRuleSet

1. 来源：KnowledgeRule。
2. 内容：已生效的交战规则、约束条件、版本信息、冲突校验结果。
3. 下游：BattleCtrl 用于交战规则装载，TaskMgmt 可用于任务约束解释。
4. 禁止：BattleCtrl 私自缓存修改后继续作为权威 CombatRuleSet 对外传播。

### TaskTemplate

1. 来源：KnowledgeRule。
2. 内容：任务类型模板、参数化配置、适用条件、版本信息。
3. 下游：TaskMgmt 用于任务识别、任务分解和任务方案构造。
4. 禁止：TaskMgmt 自行派生未注册的长期 TaskTemplate 主版本。

### DoctrineEntry

1. 来源：KnowledgeRule。
2. 内容：条令条款、适用场景、优先级、版本和生效范围。
3. 下游：TaskMgmt、BattleCtrl、SitMgmt 在推理或校验时引用。
4. 禁止：把 DoctrineEntry 直接当作可执行任务或交战计划对象使用。

### InferenceRequest

1. 来源：TaskMgmt、BattleCtrl、SitMgmt。
2. 内容：推理上下文、输入对象引用、请求目标、解释级别。
3. 下游：KnowledgeRule 接收并返回推理结果与推荐项。
4. 禁止：业务分系统绕过 InferenceRequest 直接拼接规则引擎内部输入结构。

### LinkQualitySnapshot

1. 来源：CommNet。
2. 内容：链路丢包率、时延、带宽占用、抖动、标准化链路等级、可用性判定。
3. 下游：ResMgmt 用于资源健康判断，BattleCtrl 用于交战执行风险感知，MonitorLog 用于监控展示。
4. 禁止：其他业务分系统私自汇总链路底层指标后覆盖 CommNet 的权威质量结论。

### TopologySnapshot

1. 来源：CommNet。
2. 内容：节点、邻接关系、路由结构、拓扑版本、重构时间。
3. 下游：MonitorLog、OpsMgmt 用于网络观察与运维分析。
4. 禁止：将 TopologySnapshot 误当作资源编组或作战编队对象使用。

### SecurityEvent

1. 来源：CommNet。
2. 内容：链路认证失败、抗干扰告警、频谱异常、通信保密等级异常。
3. 下游：AuthAudit、MonitorLog。
4. 禁止：把通信安全事件直接解释为任务失败或交战失败结论。

### DataOwnershipPolicy

1. 来源：DbMgmt。
2. 内容：对象 ownership 到存储引擎、读写路径、生命周期策略的映射规则。
3. 下游：各业务分系统通过数据库管理分系统间接遵守该策略。
4. 禁止：业务分系统绕过 DataOwnershipPolicy 直接跨域写入不属于自己的主数据。

### RealtimeRecord

1. 来源：DbMgmt。
2. 内容：任务进度、态势快照、资源状态等短保留实时记录。
3. 下游：TaskMgmt、SitMgmt、ResMgmt 按权限读取或更新各自拥有的数据。
4. 禁止：把 RealtimeRecord 直接当作长期业务归档主记录。

### ArchiveRecord

1. 来源：DbMgmt。
2. 内容：任务、交战、资源等经过归档后的历史记录。
3. 下游：TaskMgmt、BattleCtrl、ResMgmt、HMI 查询历史分析与复盘。
4. 禁止：用 ArchiveRecord 回写实时业务状态。

### SpatialTrackRecord

1. 来源：DbMgmt。
2. 内容：航迹、轨迹、时空索引、关联空间属性。
3. 下游：SitMgmt、HMI。
4. 禁止：将 SpatialTrackRecord 视为任务对象或交战计划对象。

### TargetTruth

1. 来源：Simulation。
2. 内容：目标真值位置、速度、航向、高度与目标类型。
3. 下游：SitMgmt、回放、评估模块。
4. 禁止：把 TargetTruth 直接当成实测融合航迹对外冒充真实态势。

### WeaponAdjudication

1. 来源：Simulation。
2. 内容：交战裁决结果、毁伤评分、裁决说明。
3. 下游：BattleCtrl、回放。
4. 禁止：把 WeaponAdjudication 直接当作真实战场毁伤确认结果。

### AuditEvent

1. 来源：AuthAudit。
2. 内容：操作者、动作、目标对象、处理结果、详细说明。
3. 下游：MonitorLog、OpsMgmt。
4. 禁止：将 AuditEvent 当作业务命令对象重新驱动业务流程。

### MonitorMetric

1. 来源：MonitorLog。
2. 内容：组件级指标点集合、单位、采集时间。
3. 下游：OpsMgmt、HMI。
4. 禁止：把 MonitorMetric 当作业务状态主数据写回各业务域。

### UiDashboardResponse

1. 来源：BFF。
2. 内容：任务、态势、交战、资源、告警的聚合只读视图。
3. 下游：HMI。
4. 禁止：把 UiDashboardResponse 当作业务主对象回写 TaskMgmt、BattleCtrl、SitMgmt、ResMgmt。

### UiAlertItem

1. 来源：BFF。
2. 内容：跨态势、执行、资源、通信、安全、监控、审计的统一告警项，使用标准化 UiAlertType 与 ExceptionSeverity。
3. 下游：UiDashboardResponse、UiPushEnvelope、HMI。
4. 禁止：在 BFF 外部重新定义不兼容的前端告警类型或严重等级文本体系。

### BattlePlan

1. 来源：BattleCtrl。
2. 内容：航路、编队、传感器模式、武器动作、执行窗口、协同关系。
3. 下游：EnhanceUnit 负责把 BattlePlan 翻译为平台级控制动作。
4. 禁止：TaskMgmt 直接生产 BattlePlan。

### ExecutionException

1. 来源：EnhanceUnit 或 BattleCtrl。
2. 内容：资源、航路、链路、威胁、载荷、天气、禁飞区、敌情突变、平台失联等异常。
3. 流向：先进入 BattleCtrl 判断是否可做计划级调整，再决定是否回退 TaskMgmt。
4. 禁止：EnhanceUnit 直接做任务级重构决策。

## 4. 典型流转关系

### 任务主链

MissionCommand -> TaskIntent -> TaskConstraint -> TaskGraph -> TaskScheme -> TaskPackage -> BattlePlan

### 资源支撑链

ResourceRegistration -> ResourceIdentity -> ResourceDescriptor -> ResourceStateSnapshot -> CapabilityProfile -> AllocationDecision

### 消息契约链

TopicDefinition -> SchemaDescriptor -> MessageEnvelope -> SubscriptionBinding -> DeliveryReceipt 或 DeadLetterRecord

### 知识推理链

InferenceRequest -> CombatRuleSet 或 TaskTemplate 或 TacticTemplate 或 DoctrineEntry -> InferenceResult -> RecommendationItem

### 通信保障链

LinkSession -> LinkProfile -> TopologySnapshot -> RoutePath -> LinkQualitySnapshot -> DegradationAlert 或 SecurityEvent

### 持久化支撑链

DataOwnershipPolicy -> StorageShardKey -> RealtimeRecord -> ArchiveRecord

### 仿真支撑链

ScenarioLoadCommand -> ScenarioControlCommand -> ClockTick -> SimFlightState 或 SimSensorState 或 SimWeaponState -> TargetTruth 或 WeaponAdjudication

### 审计监控链

AuditEvent 或 SecurityAlert -> MonitorMetric 或 MonitorAlert

### 前端聚合链

UiTaskSummary 或 UiSituationSnapshot 或 UiBattleOverview 或 UiResourceOverview 或 UiAlertItem -> UiDashboardResponse -> UiPushEnvelope

### 感知主链

RawTargetInput -> FusedTrack -> ThreatAssessment -> SituationPicture -> InferenceResult

### 执行闭环链

BattlePlan -> ExecutionStateSnapshot -> ExecutionException -> AdjustmentOption 或 ReconstructionRequest

### 评估闭环链

ExecutionStateSnapshot -> EngagementEffectReport -> EffectivenessReport

## 5. 对象 ownership 约束

1. TaskMgmt 拥有：MissionCommand、TaskIntent、TaskConstraint、TaskGraph、TaskScheme、TaskPackage、TaskExecutionSnapshot、EffectivenessReport。
2. SitMgmt 拥有：RawTargetInput、FusedTrack、ThreatAssessment、SituationPicture、InferenceResult、CriticalAlert、SituationSummaryReport。
3. ResMgmt 拥有：ResourceRegistration、ResourceIdentity、ResourceDescriptor、ResourceStateSnapshot、HealthScore、CapabilityProfile、TaskCapabilityMatrix、AllocationDecision、ReservationTicket、QualityAssessment。
4. MsgService 拥有：TopicDefinition、SchemaDescriptor、MessageEnvelope、SubscriptionBinding、DeliveryReceipt、RetryTask、DeadLetterRecord、FlowControlPolicy、MessageMetricSnapshot。
5. KnowledgeRule 拥有：CombatRuleSet、RuleVersion、TacticTemplate、TaskTemplate、TemplateParameterProfile、TargetFeatureProfile、ThreatFeatureProfile、BehaviorPattern、DoctrineEntry、InferenceResult、RecommendationItem。
6. CommNet 拥有：LinkSession、LinkProfile、TopologySnapshot、RoutePath、RelayFrame、CommSecurityContext、LinkQualitySnapshot、DegradationAlert、SecurityEvent。
7. DbMgmt 拥有：DataOwnershipPolicy、StorageShardKey、RealtimeRecord、ArchiveRecord、SpatialTrackRecord、TargetFeatureRecord、GisTileRecord、IntelRecord、BackupSnapshot、DbMetricSnapshot。
8. Simulation 拥有：ScenarioLoadCommand、ScenarioControlCommand、ClockTick、SimFlightState、SimSensorState、SimWeaponState、TargetTruth、WeaponAdjudication。
9. AuthAudit 拥有：AuditEvent、SecurityAlert。
10. MonitorLog 拥有：MonitorMetric、MonitorAlert。
11. BFF 拥有：UiTaskSummary、UiSituationSnapshot、UiBattleOverview、UiResourceOverview、UiAlertItem、UiDashboardResponse、UiPushEnvelope。
12. BattleCtrl 拥有：BattlePlan、FormationScheme、RouteSegment、SensorProfile、WeaponProfile、AdjustmentOption、EngagementEffectReport。
13. EnhanceUnit 拥有：PlatformCommand、PlatformState、PayloadState、WeaponState、TargetTrack、ExecutionStateSnapshot 的边缘原始映射。

## 6. 后续落地建议

1. 后续可将本清单继续扩展为统一 schema/IDL 对象目录。
2. 若开始数据库设计，可基于 ownership 约束拆分表与事件 schema。
3. 若开始接口设计，可为每个对象补充字段表、状态机和版本策略。
4. 若开始多 agent 并行开发，可把本清单作为跨仓契约基线。
