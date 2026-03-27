# BMS Proto 反向收敛优先级清单

本文档用于在现有 schema/IDL 基线和字段级 ICD 样板基础上，识别当前 proto 中最值得优先收敛的弱类型字段与占位字段。

目标不是一次性重写所有 proto，而是给后续演进提供清晰优先级，避免接口越来越多后再集中返工。

当前状态：

1. 第一阶段 P0 收敛已完成落地：TaskType、ExecutionPhase、ExecutionExceptionType、RouteAction、CommSecurityEventType 已进入 proto 主干。
2. 本文档后续主要用于跟踪剩余 P1、P2 收敛项。

## 1. 收敛原则

1. 优先收敛跨分系统主链对象，而不是只在单一模块内部使用的对象。
2. 优先收敛会影响主流程判断、调度、裁定、联调一致性的字段。
3. 优先把自由字符串收敛为枚举、标准码或结构化对象。
4. 对平台/UAV 工程细节保持克制，未与用户确认前，不提前展开过细的设备级字段。
5. 若字段暂时无法稳定为强类型，至少先定义受控词表和标准码表。

## 2. 优先级定义

### P0

必须优先收敛，否则会直接影响任务闭环、计划执行、跨系统联调一致性。

### P1

建议尽快收敛，当前可先运行，但会持续制造解释歧义、兼容负担或前后端口径不一致。

### P2

可延后收敛，当前问题主要是扩展性、可维护性或可观测性不足，而非立即阻断实现。

## 3. P0 收敛项状态

### 3.1 TaskConstraint.task_type

当前状态：

1. 文件：proto/bms/schema/task.proto
2. 类型：已收敛为 bms.schema.common.TaskType

问题：

1. 任务类型是任务分解、资源匹配、计划生成的入口字段，不能长期自由文本化。
2. 如果不同分系统使用不同命名，将直接导致规则、模板、统计和 UI 分类不一致。

落地结果：

1. 已新增 TaskType 枚举。
2. 正式 ICD 仍需继续建立任务类型码表与扩展值策略。

### 3.2 ExecutionStateSnapshot.current_phase

当前状态：

1. 文件：proto/bms/schema/execution.proto
2. 类型：已收敛为 bms.schema.common.ExecutionPhase

问题：

1. 执行阶段会被 BattleCtrl、TaskMgmt、HMI、回放链路共同消费。
2. 若 current_phase 自由文本化，状态机判断、统计口径、异常恢复都会失真。

落地结果：

1. 已新增 ExecutionPhase 枚举。
2. 如需要兼容平台差异，可在后续增加 phase_detail 作为补充文本，而不是回退为自由文本。

### 3.3 ExecutionException.exception_type

当前状态：

1. 文件：proto/bms/schema/execution.proto
2. 类型：已收敛为 bms.schema.common.ExecutionExceptionType

问题：

1. 它直接决定是计划内调整、任务重构还是人工干预。
2. 若异常类型不标准化，就无法把异常与处置策略绑定。

落地结果：

1. 已新增 ExecutionExceptionType 枚举。
2. reason 继续保留为补充解释，不再承担异常分类职责。

### 3.4 RouteSegment.action 与 Waypoint.action

当前状态：

1. 文件：proto/bms/schema/battle.proto, proto/bms/schema/platform_command.proto
2. 类型：已统一收敛为 bms.schema.common.RouteAction

问题：

1. 航段动作和航点动作是计划到边缘执行层最直接的控制语义。
2. 若两处定义不一致，会导致 BattlePlan 与 PlatformCommand 之间失配。

落地结果：

1. 已建立统一的 RouteAction 枚举。
2. 若后续确认航段动作与航点动作需要分层，再在共享枚举之外增补映射关系，不回退为字符串。

### 3.5 SecurityEvent.event_type

当前状态：

1. 文件：proto/bms/schema/comm.proto
2. 类型：已收敛为 bms.schema.common.CommSecurityEventType

问题：

1. 通信安全事件会进入审计、监控、告警聚合链。
2. 若 event_type 仅为自由文本，跨系统订阅与规则触发难以标准化。

落地结果：

1. 已新增 CommSecurityEventType 枚举。
2. detail 继续作为补充描述，不替代事件类型。

## 4. P1 收敛项

### 4.1 TaskConstraint.resource_prerequisites

当前状态：

1. 文件：proto/bms/schema/task.proto
2. 类型：已收敛为 repeated ResourcePrerequisite

问题：

1. 当前只能表达“文字化前提”，无法稳定表达数量、能力门槛、必选/可选等规则。
2. 会影响 TaskMgmt 到 ResMgmt 的精确匹配。

落地结果：

1. 已新增 ResourcePrerequisite message。
2. 当前最小字段已包含 requirement_type、target_type、min_count、required_capabilities、is_mandatory。

### 4.2 TaskConstraint.coverage_constraints

当前状态：

1. 文件：proto/bms/schema/task.proto
2. 类型：已收敛为 repeated CoverageConstraint

问题：

1. 无法区分时间覆盖、空间覆盖、连续覆盖、重访间隔等不同约束类型。
2. 会影响任务评估与计划可执行性校核。

落地结果：

1. 已新增 CoverageConstraint message。
2. 当前已按 spatial、temporal、continuity、revisit 四类定义 CoverageConstraintType。

### 4.3 SensorProfile.parameters 与 WeaponProfile.parameters

当前状态：

1. 文件：proto/bms/schema/battle.proto
2. 类型：已收敛为 repeated KeyValueParameter

问题：

1. 参数语义不明确，后续平台适配层很难稳定解析。
2. 不利于形成正式的模板、校验和默认值策略。

落地结果：

1. 已改为 repeated KeyValueParameter。
2. 下一步如果需要更强约束，可再按传感器类型或武器类型提炼专有参数对象。

### 4.4 LinkQualitySnapshot.link_grade

当前状态：

1. 文件：proto/bms/schema/comm.proto
2. 类型：已收敛为 bms.schema.common.LinkGrade

问题：

1. 它本质上是阈值裁定结果，不宜长期自由文本化。
2. 若与 BattleCtrl 的执行风险等级映射不稳定，会影响策略联动。

落地结果：

1. 已新增 LinkGrade 枚举。
2. 正式 ICD 仍需补充由 latency、loss、bandwidth 推导 grade 的裁定规则。

### 4.5 MessageEnvelope.qos_profile 与 TopicDefinition.qos_profile

当前状态：

1. 文件：proto/bms/schema/message.proto
2. 类型：已收敛为 bms.schema.common.QosProfile

问题：

1. QoS profile 是系统级契约，不应长期依赖自由文本。
2. 容易造成主题定义与运行时封装口径不一致。

落地结果：

1. 已新增 QosProfile 枚举。
2. 运行时若存在供应商特定扩展，应通过配置映射处理，而不是回退为自由字符串。

### 4.6 UiAlertItem.severity 与 UiAlertItem.alert_type

当前状态：

1. 文件：proto/bms/schema/bff.proto
2. 类型：已收敛为 UiAlertType 与 ExceptionSeverity

问题：

1. 前端聚合层若长期用自由文本，会出现监控、审计、链路、安全多源告警难以统一的问题。
2. UI 排序、过滤、颜色映射都依赖这些字段稳定化。

落地结果：

1. severity 已复用统一 ExceptionSeverity 枚举。
2. alert_type 已建立跨域 UiAlertType 枚举。

## 5. P2 收敛项

### 5.1 MissionCommand.command_source

当前定义：

1. 文件：proto/bms/schema/task.proto
2. 类型：string

建议收敛：

1. 建立 CommandSource 枚举或码表。
2. 当前可以先保留字符串，但应开始收集真实来源集合。

### 5.2 ThreatAssessment.threat_reason

当前定义：

1. 文件：proto/bms/schema/situation.proto
2. 类型：string

建议收敛：

1. 增加 rule_refs 或 reason_codes。
2. 保留 threat_reason 作为解释文本。

落地结果：

1. 已增加 ThreatReasonCode 与 ThreatReasonRef。
2. ThreatAssessment 已增加 repeated reasons。
3. threat_reason 继续保留为人工可读解释文本。

### 5.3 AllocationDecision.arbitration_reason

当前定义：

1. 文件：proto/bms/schema/resource.proto
2. 类型：string

建议收敛：

1. 增加 arbitration_rule_id、conflict_resource_ids、priority_basis。
2. arbitration_reason 保留为补充文本即可。

### 5.4 TopicDefinition.publishers 与 subscribers

当前状态：

1. 文件：proto/bms/schema/message.proto
2. 类型：已收敛为 repeated EndpointBinding

落地结果：

1. 已升级为 EndpointBinding 对象。
2. 当前最小字段包含 endpoint_id、endpoint_type、owner_domain、is_external，可支撑主题治理与端点登记。

### 5.5 QueryFilter.types 与 UiTaskSummary.status

当前定义：

1. 文件：proto/bms/schema/bff.proto
2. 类型：string 或 repeated string

建议收敛：

1. 在前端域逐步建立 view 枚举与状态码表。
2. 该项优先级低于主业务链和执行链。

## 6. 建议的演进顺序

### 第一阶段

1. TaskType
2. ExecutionPhase
3. ExecutionExceptionType
4. RouteAction 或相关动作枚举
5. CommSecurityEventType

### 第二阶段

1. ResourcePrerequisite
2. CoverageConstraint
3. SensorProfile 或 WeaponProfile 参数结构化
4. LinkGrade
5. QosProfile

### 第三阶段

1. CommandSource
2. Threat reason 标准码
3. Arbitration reason 结构化
4. EndpointBinding
5. UI 视图枚举与状态码表

## 7. 当前建议

如果下一步要开始真正修改 proto，建议只做第一阶段，不要一次性动到平台细粒度接口和全部聚合视图。

原因：

1. 第一阶段都属于跨系统主流程关键字段。
2. 收益高，且不会提前锁死你还不想现在细化的平台工程粒度。
3. 改完之后，前三份字段级 ICD 样板就能与 proto 主干更一致。
