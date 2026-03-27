# BMS Schema / IDL 基线文档

本文档用于把当前 Code Diagram 与对象清单收敛为后续可实现的 schema/IDL 设计基线。

适用范围：

1. DDS topic payload 结构定义。
2. 容器间同步 API 的请求/响应对象。
3. 持久化事件与回放事件的统一对象边界。
4. 多 agent 并行开发时的公共对象契约。

配套工程交付文档：

1. ../delivery/BMS_Subsystem_Design_Traceability_Matrix.md：分系统设计追踪矩阵。
2. ../delivery/BMS_Subsystem_Development_Handoff_Packages.md：分系统开发交付包清单。
3. ../delivery/BMS_Integration_Matrix.md：系统间联调矩阵。

配套 schema 收敛清单：

1. BMS_Proto_Refinement_Priority.md：现有 proto 的反向收敛优先级与演进顺序。

总导航文档：

1. ../../BMS_Design_Artifact_Guide.md：当前需求、架构图稿、契约文档、proto/ICD 文档的定义与关系总览。

## 1. 基线原则

1. schema 命名优先体现语义层，而不是传输协议。
2. 所有跨分系统消息必须使用统一公共头。
3. 任何对象一旦跨分系统传输，必须带 schema_version。
4. TaskPackage 是任务层到计划层的唯一正式输入对象。
5. BattlePlan 是计划层到边缘执行层的唯一正式输入对象。
6. MessageEnvelope 只负责传输包络，不改写业务 payload 语义。
7. 业务分系统不得绕过主拥有者定义共享对象字段。

## 2. IDL 分包建议

建议采用以下包结构，无论最终落地到 Protobuf、IDL、Avro 还是 JSON Schema，都保持相同分包语义。

```text
bms.schema.common
bms.schema.task
bms.schema.situation
bms.schema.resource
bms.schema.battle
bms.schema.execution
bms.schema.message
bms.schema.knowledge
bms.schema.comm
bms.schema.persistence
bms.schema.ops
```

## 3. 公共头定义

所有事件类、状态类、计划类、任务类对象都应嵌入统一公共头。

```proto
message CommonHeader {
  string trace_id = 1;
  string schema_version = 2;
  string source_id = 3;
  string platform_id = 4;
  string mission_id = 5;
  string scenario_id = 6;
  int64 event_time_utc_ms = 7;
}
```

约束：

1. event_time_utc_ms 统一使用 UTC 毫秒时间戳。
2. 不适用的字段允许为空，但字段位置保留。
3. trace_id 在跨容器链路中不得被重置。

## 4. 标识与枚举约定

### 标识规则

1. command_id：单次指令唯一标识。
2. mission_id：任务级唯一标识。
3. plan_id 或 battle_plan_id：计划级唯一标识。
4. platform_id：平台唯一标识。
5. track_id：融合航迹唯一标识。
6. allocation_id：资源分配唯一标识。
7. alert_id：告警唯一标识。

### 推荐基础枚举

```proto
enum ResourceAvailability {
  RESOURCE_UNKNOWN = 0;
  RESOURCE_AVAILABLE = 1;
  RESOURCE_DEGRADED = 2;
  RESOURCE_UNAVAILABLE = 3;
}

enum ExceptionSeverity {
  EXCEPTION_INFO = 0;
  EXCEPTION_WARN = 1;
  EXCEPTION_ERROR = 2;
  EXCEPTION_FATAL = 3;
}

enum TriggerMode {
  TRIGGER_UNKNOWN = 0;
  TRIGGER_AUTOMATIC = 1;
  TRIGGER_MANUAL_CONFIRM = 2;
}

enum TaskType {
  TASK_TYPE_UNKNOWN = 0;
  TASK_TYPE_RECON = 1;
  TASK_TYPE_TRACK = 2;
  TASK_TYPE_STRIKE = 3;
  TASK_TYPE_SUPPORT = 4;
  TASK_TYPE_ESCORT = 5;
  TASK_TYPE_ASSESS = 6;
}

enum ExecutionPhase {
  EXECUTION_PHASE_UNKNOWN = 0;
  EXECUTION_PHASE_PREPARING = 1;
  EXECUTION_PHASE_EN_ROUTE = 2;
  EXECUTION_PHASE_ON_STATION = 3;
  EXECUTION_PHASE_EXECUTING = 4;
  EXECUTION_PHASE_EGRESS = 5;
  EXECUTION_PHASE_COMPLETED = 6;
  EXECUTION_PHASE_ABORTED = 7;
}

enum ExecutionExceptionType {
  EXECUTION_EXCEPTION_UNKNOWN = 0;
  EXECUTION_EXCEPTION_LINK_INTERRUPTED = 1;
  EXECUTION_EXCEPTION_RESOURCE_FAILURE = 2;
  EXECUTION_EXCEPTION_ROUTE_UNREACHABLE = 3;
  EXECUTION_EXCEPTION_SENSOR_DEGRADED = 4;
  EXECUTION_EXCEPTION_WEAPON_UNAVAILABLE = 5;
  EXECUTION_EXCEPTION_COMMAND_REJECTED = 6;
  EXECUTION_EXCEPTION_TIMEOUT = 7;
}

enum RouteAction {
  ROUTE_ACTION_UNKNOWN = 0;
  ROUTE_ACTION_FLYOVER = 1;
  ROUTE_ACTION_LOITER = 2;
  ROUTE_ACTION_HOVER = 3;
  ROUTE_ACTION_DROP = 4;
  ROUTE_ACTION_TURN = 5;
  ROUTE_ACTION_HOLD = 6;
  ROUTE_ACTION_RETURN = 7;
}

enum CommSecurityEventType {
  COMM_SECURITY_EVENT_UNKNOWN = 0;
  COMM_SECURITY_EVENT_AUTH_FAILURE = 1;
  COMM_SECURITY_EVENT_JAMMING_ALERT = 2;
  COMM_SECURITY_EVENT_SPECTRUM_ANOMALY = 3;
  COMM_SECURITY_EVENT_ENCRYPTION_ERROR = 4;
  COMM_SECURITY_EVENT_LINK_HIJACK_ALERT = 5;
}

enum LinkGrade {
  LINK_GRADE_UNKNOWN = 0;
  LINK_GRADE_EXCELLENT = 1;
  LINK_GRADE_GOOD = 2;
  LINK_GRADE_DEGRADED = 3;
  LINK_GRADE_POOR = 4;
  LINK_GRADE_UNAVAILABLE = 5;
}

enum QosProfile {
  QOS_PROFILE_UNKNOWN = 0;
  QOS_PROFILE_CMD = 1;
  QOS_PROFILE_STATE = 2;
  QOS_PROFILE_TRACK = 3;
  QOS_PROFILE_ALERT = 4;
  QOS_PROFILE_PLAN = 5;
  QOS_PROFILE_REPLAY = 6;
  QOS_PROFILE_VIDEO_META = 7;
}

enum UiAlertType {
  UI_ALERT_TYPE_UNKNOWN = 0;
  UI_ALERT_TYPE_SITUATION = 1;
  UI_ALERT_TYPE_EXECUTION = 2;
  UI_ALERT_TYPE_RESOURCE = 3;
  UI_ALERT_TYPE_COMM = 4;
  UI_ALERT_TYPE_SECURITY = 5;
  UI_ALERT_TYPE_MONITOR = 6;
  UI_ALERT_TYPE_AUDIT = 7;
}
```

## 5. 任务语义 schema 基线

### MissionCommand

```proto
message MissionCommand {
  CommonHeader header = 1;
  string command_id = 2;
  string command_source = 3;
  string command_text = 4;
  map<string, string> raw_params = 5;
}
```

### TaskConstraint

```proto
enum ResourceRequirementType {
  RESOURCE_REQUIREMENT_UNKNOWN = 0;
  RESOURCE_REQUIREMENT_PLATFORM = 1;
  RESOURCE_REQUIREMENT_PAYLOAD = 2;
  RESOURCE_REQUIREMENT_WEAPON = 3;
  RESOURCE_REQUIREMENT_LINK = 4;
  RESOURCE_REQUIREMENT_CAPABILITY = 5;
}

enum CoverageConstraintType {
  COVERAGE_CONSTRAINT_UNKNOWN = 0;
  COVERAGE_CONSTRAINT_SPATIAL = 1;
  COVERAGE_CONSTRAINT_TEMPORAL = 2;
  COVERAGE_CONSTRAINT_CONTINUITY = 3;
  COVERAGE_CONSTRAINT_REVISIT = 4;
}

message ResourcePrerequisite {
  string requirement_id = 1;
  ResourceRequirementType requirement_type = 2;
  string target_type = 3;
  uint32 min_count = 4;
  repeated string required_capabilities = 5;
  bool is_mandatory = 6;
}

message CoverageConstraint {
  string constraint_id = 1;
  CoverageConstraintType constraint_type = 2;
  string region_ref = 3;
  int64 min_duration_ms = 4;
  int64 revisit_interval_ms = 5;
  double min_coverage_ratio = 6;
  bool continuous_required = 7;
}

message TaskConstraint {
  CommonHeader header = 1;
  string task_id = 2;
  TaskType task_type = 3;
  int64 start_time_utc_ms = 4;
  int64 end_time_utc_ms = 5;
  repeated string dependency_task_ids = 6;
  repeated string moe_targets = 7;
  repeated ResourcePrerequisite resource_prerequisites = 8;
  repeated CoverageConstraint coverage_constraints = 9;
}
```

### TaskPackage

```proto
message TaskPackage {
  CommonHeader header = 1;
  string task_package_id = 2;
  string task_scheme_id = 3;
  TaskConstraint constraint = 4;
  repeated string task_node_ids = 5;
  repeated string allocation_ids = 6;
  TriggerMode trigger_mode = 7;
}
```

## 6. 态势语义 schema 基线

### FusedTrack

```proto
message FusedTrack {
  CommonHeader header = 1;
  string track_id = 2;
  string target_type = 3;
  double latitude = 4;
  double longitude = 5;
  double altitude_m = 6;
  double speed_mps = 7;
  double heading_deg = 8;
  double confidence = 9;
  repeated string source_refs = 10;
}
```

### ThreatAssessment

```proto
enum ThreatReasonCode {
  THREAT_REASON_CODE_UNKNOWN = 0;
  THREAT_REASON_CODE_HIGH_PRIORITY_TARGET = 1;
  THREAT_REASON_CODE_TIME_SENSITIVE_TARGET = 2;
  THREAT_REASON_CODE_HIGH_MOBILITY_TARGET = 3;
  THREAT_REASON_CODE_HIGH_THREAT_WEAPON = 4;
  THREAT_REASON_CODE_AIR_DEFENSE_THREAT = 5;
  THREAT_REASON_CODE_LINKED_TO_MISSION_OBJECTIVE = 6;
  THREAT_REASON_CODE_ENTERING_PROTECTED_AREA = 7;
  THREAT_REASON_CODE_ESCALATING_BEHAVIOR = 8;
}

message ThreatReasonRef {
  ThreatReasonCode reason_code = 1;
  string source_rule_or_template_id = 2;
  string evidence_ref = 3;
  double confidence = 4;
}

message ThreatAssessment {
  CommonHeader header = 1;
  string threat_id = 2;
  string track_id = 3;
  int32 threat_level = 4;
  int32 priority_rank = 5;
  string threat_reason = 6;
  repeated ThreatReasonRef reasons = 7;
}
```

### TargetFeatureSnapshot

```proto
enum TargetCamp {
  TARGET_CAMP_UNKNOWN = 0;
  TARGET_CAMP_FOE = 1;
  TARGET_CAMP_FRIEND = 2;
  TARGET_CAMP_NEUTRAL = 3;
  TARGET_CAMP_UNIDENTIFIED = 4;
}

enum TimeSensitivity {
  TIME_SENSITIVITY_UNKNOWN = 0;
  TIME_SENSITIVITY_NON_TIME_SENSITIVE = 1;
  TIME_SENSITIVITY_TIME_SENSITIVE = 2;
}

enum TargetMobility {
  TARGET_MOBILITY_UNKNOWN = 0;
  TARGET_MOBILITY_FIXED = 1;
  TARGET_MOBILITY_MOBILE = 2;
}

enum ProtectionCapability {
  PROTECTION_CAPABILITY_UNKNOWN = 0;
  PROTECTION_CAPABILITY_NONE = 1;
  PROTECTION_CAPABILITY_ARMORED = 2;
  PROTECTION_CAPABILITY_CONCRETE_FORTIFIED = 3;
}

message TargetFeatureSnapshot {
  CommonHeader header = 1;
  string feature_id = 2;
  string track_id = 3;
  string target_name = 4;
  string target_type = 5;
  string target_source = 6;
  TargetCamp camp = 7;
  TimeSensitivity time_sensitivity = 8;
  TargetMobility mobility = 9;
  ProtectionCapability protection_capability = 10;
  string country_code = 11;
  string detection_method = 12;
  double detection_range_km = 13;
  double horizontal_detection_angle_deg = 14;
  double vertical_detection_angle_deg = 15;
  double weapon_attack_height_m = 16;
  double weapon_attack_distance_km = 17;
  double length_m = 18;
  double width_m = 19;
  double height_m = 20;
}
```

### TargetStatus

```proto
enum CoordinateSystemType {
  COORDINATE_SYSTEM_UNKNOWN = 0;
  COORDINATE_SYSTEM_GEODETIC = 1;
}

enum DamageStatus {
  DAMAGE_STATUS_UNKNOWN = 0;
  DAMAGE_STATUS_INTACT = 1;
  DAMAGE_STATUS_LIGHT = 2;
  DAMAGE_STATUS_MEDIUM = 3;
  DAMAGE_STATUS_HEAVY = 4;
  DAMAGE_STATUS_DESTROYED = 5;
}

message TargetStatus {
  CommonHeader header = 1;
  string status_id = 2;
  string track_id = 3;
  string target_source = 4;
  CoordinateSystemType coordinate_system = 5;
  double latitude = 6;
  double longitude = 7;
  double altitude_m = 8;
  DamageStatus damage_status = 9;
}
```

## 7. 资源语义 schema 基线

### AllocationRequest

```proto
enum AllocationRequester {
  ALLOCATION_REQUESTER_UNKNOWN = 0;
  ALLOCATION_REQUESTER_TASK_MGMT = 1;
  ALLOCATION_REQUESTER_BATTLE_CTRL = 2;
  ALLOCATION_REQUESTER_HMI = 3;
  ALLOCATION_REQUESTER_AUTOMATION = 4;
}

enum AllocationPolicy {
  ALLOCATION_POLICY_UNKNOWN = 0;
  ALLOCATION_POLICY_IMMEDIATE = 1;
  ALLOCATION_POLICY_RESERVE_FIRST = 2;
  ALLOCATION_POLICY_BEST_EFFORT = 3;
  ALLOCATION_POLICY_REPLACE_ALLOWED = 4;
}

message AllocationTimeWindow {
  int64 not_before_utc_ms = 1;
  int64 not_after_utc_ms = 2;
  int64 hold_duration_ms = 3;
}

message AllocationDemand {
  string demand_id = 1;
  string resource_type = 2;
  uint32 required_count = 3;
  repeated string required_capabilities = 4;
  repeated string preferred_resource_ids = 5;
  repeated string excluded_resource_ids = 6;
  bool allow_degraded = 7;
  bool reserve_only = 8;
}

message AllocationRequest {
  CommonHeader header = 1;
  string request_id = 2;
  AllocationRequester requester = 3;
  string task_id = 4;
  string battle_plan_id = 5;
  TriggerMode trigger_mode = 6;
  repeated AllocationDemand demands = 7;
  AllocationTimeWindow time_window = 8;
  repeated AllocationPolicy policies = 9;
}
```

### ResourceStateSnapshot

```proto
message ResourceStateSnapshot {
  CommonHeader header = 1;
  string resource_id = 2;
  string resource_type = 3;
  ResourceAvailability availability = 4;
  double health_score = 5;
  double energy_ratio = 6;
  double link_quality_score = 7;
  repeated string active_payloads = 8;
  repeated string active_weapons = 9;
}
```

### AllocationDecision

```proto
message AllocationDecision {
  CommonHeader header = 1;
  string allocation_id = 2;
  string request_id = 3;
  repeated string allocated_resource_ids = 4;
  repeated string reserved_resource_ids = 5;
  string arbitration_reason = 6;
  bool accepted = 7;
}
```

## 8. 计划语义 schema 基线

### BattlePlan

```proto
message KeyValueParameter {
  string key = 1;
  string value = 2;
  string unit = 3;
}

message SensorProfile {
  string sensor_id = 1;
  string sensor_mode = 2;
  repeated KeyValueParameter parameters = 3;
}

message WeaponProfile {
  string weapon_id = 1;
  string action_mode = 2;
  repeated KeyValueParameter parameters = 3;
}

message BattlePlan {
  CommonHeader header = 1;
  string battle_plan_id = 2;
  string task_package_id = 3;
  repeated RouteSegment route_segments = 4;
  repeated string formation_member_ids = 5;
  repeated SensorProfile sensor_profiles = 6;
  repeated WeaponProfile weapon_profiles = 7;
  int64 execute_not_before_utc_ms = 8;
  int64 execute_not_after_utc_ms = 9;
}
```

### RouteSegment

```proto
message RouteSegment {
  string route_segment_id = 1;
  double latitude = 2;
  double longitude = 3;
  double altitude_m = 4;
  double speed_mps = 5;
  RouteAction action = 6;
}
```

## 8A. 平台命令语义 schema 基线

本层用于承接 edge/platform/command 下的工程命令对象。
当前先固定命令骨架，字段细化在正式 ICD 阶段再确认。

### FlightPlanUploadCommand

```proto
message FlightPlanUploadCommand {
  CommonHeader header = 1;
  string command_id = 2;
  string platform_id = 3;
  string plan_id = 4;
  repeated Waypoint waypoints = 5;
}

message Waypoint {
  string waypoint_id = 1;
  double latitude_deg = 2;
  double longitude_deg = 3;
  double altitude_m = 4;
  double speed_mps = 5;
  RouteAction action = 6;
}
```

### FlightModeSetCommand

```proto
message FlightModeSetCommand {
  CommonHeader header = 1;
  string command_id = 2;
  string platform_id = 3;
  FlightMode target_mode = 4;
}
```

### TakeoffCommand / RtlCommand / LoiterCommand / TimeSyncCommand

这些命令当前只固定消息骨架与标识字段，后续在 ICD 阶段按真实平台能力细化参数、前置条件、拒绝码和执行时序。

## 9. 执行语义 schema 基线

### ExecutionStateSnapshot

```proto
message ExecutionStateSnapshot {
  CommonHeader header = 1;
  string execution_id = 2;
  string battle_plan_id = 3;
  string platform_id = 4;
  ExecutionPhase current_phase = 5;
  string current_waypoint_id = 6;
  double progress_ratio = 7;
  repeated string acked_command_ids = 8;
}
```

### ExecutionException

```proto
message ExecutionException {
  CommonHeader header = 1;
  string exception_id = 2;
  string battle_plan_id = 3;
  ExecutionExceptionType exception_type = 4;
  ExceptionSeverity severity = 5;
  bool in_task_constraint = 6;
  string reason = 7;
  repeated string impacted_resource_ids = 8;
}
```

约束：

1. in_task_constraint = true 表示 BattleCtrl 可以先尝试计划级调整。
2. in_task_constraint = false 表示需要回退 TaskMgmt 发起任务重构。

## 10. 消息契约 schema 基线

### MessageEnvelope

```proto
message MessageEnvelope {
  CommonHeader header = 1;
  string topic = 2;
  string payload_type = 3;
  bytes payload_bytes = 4;
  QosProfile qos_profile = 5;
}
```

### SchemaDescriptor

```proto
message SchemaDescriptor {
  string payload_type = 1;
  string schema_version = 2;
  string schema_uri = 3;
}
```

### SubscriptionBinding

```proto
message SubscriptionBinding {
  string subscription_id = 1;
  string topic = 2;
  EndpointBinding subscriber = 3;
}
```

### DeliveryReceipt

```proto
message DeliveryReceipt {
  string receipt_id = 1;
  string topic = 2;
  string message_trace_id = 3;
  string subscriber_endpoint_id = 4;
  bool delivered = 5;
  int64 delivered_at_utc_ms = 6;
}
```

### DeadLetterRecord

```proto
message DeadLetterRecord {
  string dead_letter_id = 1;
  string original_topic = 2;
  string payload_type = 3;
  string message_trace_id = 4;
  string failure_reason = 5;
  uint32 retry_count = 6;
  int64 last_attempt_utc_ms = 7;
}
```

### TopicDefinition

```proto
enum EndpointType {
  ENDPOINT_TYPE_UNKNOWN = 0;
  ENDPOINT_TYPE_CONTAINER = 1;
  ENDPOINT_TYPE_BFF = 2;
  ENDPOINT_TYPE_EDGE = 3;
  ENDPOINT_TYPE_EXTERNAL_SYSTEM = 4;
  ENDPOINT_TYPE_SIMULATION = 5;
  ENDPOINT_TYPE_MONITOR = 6;
}

message EndpointBinding {
  string endpoint_id = 1;
  EndpointType endpoint_type = 2;
  string owner_domain = 3;
  bool is_external = 4;
}

message TopicDefinition {
  string topic = 1;
  string domain = 2;
  string payload_type = 3;
  QosProfile qos_profile = 4;
  repeated EndpointBinding publishers = 5;
  repeated EndpointBinding subscribers = 6;
}
```

## 11. 知识规则 schema 基线

### InferenceRequest

```proto
message InferenceRequest {
  CommonHeader header = 1;
  string request_id = 2;
  string requester = 3;
  string target_object_type = 4;
  repeated string input_refs = 5;
  string purpose = 6;
  bool need_explanation = 7;
}
```

### RecommendationItem

```proto
message RecommendationItem {
  CommonHeader header = 1;
  string recommendation_id = 2;
  string recommendation_type = 3;
  string source_rule_or_template_id = 4;
  string summary = 5;
  double confidence = 6;
}
```

## 12. 通信语义 schema 基线

### TopologySnapshot

```proto
message TopologyNode {
  string node_id = 1;
  string node_type = 2;
  ResourceAvailability availability = 3;
}

message TopologyLink {
  string link_id = 1;
  string from_node_id = 2;
  string to_node_id = 3;
  LinkGrade link_grade = 4;
}

message TopologySnapshot {
  CommonHeader header = 1;
  string topology_id = 2;
  repeated TopologyNode nodes = 3;
  repeated TopologyLink links = 4;
  int64 changed_at_utc_ms = 5;
}
```

### LinkQualitySnapshot

```proto
message LinkQualitySnapshot {
  CommonHeader header = 1;
  string link_id = 2;
  double latency_ms = 3;
  double jitter_ms = 4;
  double packet_loss_ratio = 5;
  double bandwidth_kbps = 6;
  LinkGrade link_grade = 7;
}
```

### DegradationAlert

```proto
message DegradationAlert {
  CommonHeader header = 1;
  string alert_id = 2;
  string link_id = 3;
  LinkGrade current_grade = 4;
  ExceptionSeverity severity = 5;
  string reason = 6;
}
```

### SecurityEvent

```proto
message SecurityEvent {
  CommonHeader header = 1;
  string event_id = 2;
  CommSecurityEventType event_type = 3;
  ExceptionSeverity severity = 4;
  string detail = 5;
}
```

## 13. 持久化语义 schema 基线

### RealtimeRecord

```proto
message RealtimeRecord {
  CommonHeader header = 1;
  string record_id = 2;
  string owner_domain = 3;
  string object_type = 4;
  string object_id = 5;
  bytes snapshot_bytes = 6;
  int64 ttl_ms = 7;
}
```

### ArchiveRecord

```proto
message ArchiveRecord {
  CommonHeader header = 1;
  string archive_id = 2;
  string owner_domain = 3;
  string object_type = 4;
  string object_id = 5;
  bytes snapshot_bytes = 6;
  int64 archived_at_utc_ms = 7;
}
```

## 14. 仿真语义 schema 基线

```proto
enum ScenarioControlAction {
  SCENARIO_CONTROL_ACTION_UNKNOWN = 0;
  SCENARIO_CONTROL_ACTION_START = 1;
  SCENARIO_CONTROL_ACTION_PAUSE = 2;
  SCENARIO_CONTROL_ACTION_STOP = 3;
}

enum AdjudicationResult {
  ADJUDICATION_RESULT_UNKNOWN = 0;
  ADJUDICATION_RESULT_MISS = 1;
  ADJUDICATION_RESULT_SUPPRESSION = 2;
  ADJUDICATION_RESULT_DAMAGE = 3;
  ADJUDICATION_RESULT_DESTROY = 4;
}
```

### ScenarioLoadCommand

```proto
message ScenarioLoadCommand {
  CommonHeader header = 1;
  string scenario_id = 2;
  string scenario_name = 3;
  string scenario_uri = 4;
}
```

### ScenarioControlCommand

```proto
message ScenarioControlCommand {
  CommonHeader header = 1;
  string scenario_id = 2;
  ScenarioControlAction control_action = 3;
}
```

### ClockTick

```proto
message ClockTick {
  CommonHeader header = 1;
  string tick_id = 2;
  int64 sim_time_utc_ms = 3;
  double sim_time_scale = 4;
}
```

### TargetTruth

```proto
message TargetTruth {
  CommonHeader header = 1;
  string target_id = 2;
  string target_type = 3;
  double latitude = 4;
  double longitude = 5;
  double altitude_m = 6;
  double speed_mps = 7;
  double heading_deg = 8;
}
```

### WeaponAdjudication

```proto
message WeaponAdjudication {
  CommonHeader header = 1;
  string engagement_id = 2;
  AdjudicationResult adjudication_result = 3;
  double damage_score = 4;
  string detail = 5;
}
```

## 15. 审计与监控语义 schema 基线

### AuditEvent

```proto
message AuditEvent {
  CommonHeader header = 1;
  string audit_id = 2;
  string actor_id = 3;
  string actor_type = 4;
  string action = 5;
  string target_type = 6;
  string target_id = 7;
  string result = 8;
  string detail = 9;
}
```

### SecurityAlert

```proto
message SecurityAlert {
  CommonHeader header = 1;
  string alert_id = 2;
  string alert_type = 3;
  ExceptionSeverity severity = 4;
  string source_component = 5;
  string detail = 6;
}
```

### MonitorMetric

```proto
message MonitorMetric {
  CommonHeader header = 1;
  string metric_id = 2;
  string component_id = 3;
  repeated MetricPoint points = 4;
}
```

### MonitorAlert

```proto
message MonitorAlert {
  CommonHeader header = 1;
  string alert_id = 2;
  string component_id = 3;
  string alert_type = 4;
  ExceptionSeverity severity = 5;
  string detail = 6;
}
```

## 16. 前端聚合语义 schema 基线

本层用于承接 API Gateway / BFF 对前端的聚合查询与推送出口。
这些对象是只读视图对象，不是业务主数据对象。

### UiAlertItem

```proto
message UiAlertItem {
  string alert_id = 1;
  UiAlertType alert_type = 2;
  ExceptionSeverity severity = 3;
  string source_component = 4;
  string summary = 5;
  int64 event_time_utc_ms = 6;
}
```

### UiDashboardResponse

```proto
message UiDashboardResponse {
  CommonHeader header = 1;
  repeated UiTaskSummary tasks = 2;
  UiSituationSnapshot situation = 3;
  UiBattleOverview battle = 4;
  UiResourceOverview resource = 5;
  repeated UiAlertItem alerts = 6;
}
```

### UiPushEnvelope

```proto
message UiPushEnvelope {
  CommonHeader header = 1;
  string channel = 2;
  UiViewType view_type = 3;
  bytes payload_bytes = 4;
}
```

## 17. Topic 到 payload 绑定基线

| Topic | payload_type | 说明 |
| --- | --- | --- |
| bms/core/command/task/command_received | MissionCommand | 原始任务指令入域 |
| bms/core/command/task/decomposed | TaskPackage | 任务分解后下发到计划层 |
| bms/core/command/battle/plan_created | BattlePlan | 交战计划创建 |
| bms/core/situation/track/fused_track | FusedTrack | 融合航迹 |
| bms/core/situation/threat/assessed | ThreatAssessment | 威胁评估结果 |
| bms/core/command/resource/allocation_committed | AllocationDecision | 资源分配结果 |
| bms/edge/platform/event/mission_progress | ExecutionStateSnapshot | 执行进度 |
| bms/core/ops/comm/link_quality | LinkQualitySnapshot | 链路质量快照 |
| bms/core/ops/comm/security_event | SecurityEvent | 通信安全事件 |
| bms/simulation/control/scenario_load | ScenarioLoadCommand | 仿真场景加载 |
| bms/simulation/control/scenario_start | ScenarioControlCommand | 仿真启动 |
| bms/simulation/control/scenario_pause | ScenarioControlCommand | 仿真暂停 |
| bms/simulation/control/clock_tick | ClockTick | 仿真时钟推进 |
| bms/simulation/payload/target_truth | TargetTruth | 真值目标 |
| bms/simulation/payload/weapon_adjudication | WeaponAdjudication | 仿真裁决结果 |
| bms/core/ops/sec/audit_event | AuditEvent | 审计事件 |
| bms/core/ops/monitor/metric | MonitorMetric | 统一指标流 |
| ui.push.dashboard | UiDashboardResponse 或 UiPushEnvelope | 前端总览推送 |

## 18. 版本演进规则

1. 字段新增：只允许向后兼容新增，不删除既有字段编号。
2. 字段废弃：标记 deprecated，不立即复用编号。
3. 重大语义变更：提升 schema_version 主版本。
4. Topic payload_type 不允许在同一 topic 下无版本策略地替换。
5. 跨分系统公共对象变更，必须先更新对象清单与本基线文档。

## 19. 实施顺序建议

1. 先从 CommonHeader、MissionCommand、TaskPackage、BattlePlan、ExecutionStateSnapshot 五个对象开始建第一批 IDL。
2. 第二批补 FusedTrack、ThreatAssessment、ResourceStateSnapshot、AllocationDecision。
3. 第三批补 InferenceRequest、RecommendationItem、LinkQualitySnapshot、SecurityEvent。
4. 第四批补持久化对象、运维对象与仿真对象。
5. 第五批补审计与监控对象。
6. 第六批补前端聚合视图对象。
