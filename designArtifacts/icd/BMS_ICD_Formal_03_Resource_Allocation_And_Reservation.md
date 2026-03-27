# BMS 正式 ICD 专题 03 资源申请分配与预留

本文档定义任务层与计划层向资源管理分系统发起资源申请，以及资源管理分系统输出分配、预留、拒绝与冲突裁定结果的正式 ICD 约束。

## 1. 文档定位

本文档重点覆盖以下内容：

1. AllocationRequest 的正式 payload。
2. AllocationDecision 的正式 payload 使用规则。
3. 资源申请、资源预留、资源确认的 topic 绑定。
4. 任务层申请与计划层申请的差异。
5. 资源冲突、部分满足、预留占位的裁定规则。

本文档的基础来源包括：

1. designArtifacts/contracts/BMS_DDS_Topic_Catalog.md
2. designArtifacts/contracts/BMS_Code_Interface_Object_Catalog.md
3. designArtifacts/contracts/BMS_Container_Contract_Matrix.md
4. designArtifacts/delivery/BMS_Integration_Matrix.md
5. proto/bms/schema/resource.proto

## 2. 闭环范围

本专题覆盖以下主链：

1. TaskMgmt 基于任务约束发起资源申请。
2. BattleCtrl 基于计划生成或计划调整发起资源申请。
3. ResMgmt 输出 AllocationDecision。
4. TaskMgmt 或 BattleCtrl 基于裁定结果继续任务生成、计划生成或计划调整。

本专题不覆盖：

1. 平台原始注册与能力上报细节。
2. 设备级健康评分算法。
3. 底层链路拓扑推导算法。

## 3. Topic 绑定

| topic | payload | 发布方 | 订阅方 | QoS |
| --- | --- | --- | --- | --- |
| bms/core/command/resource/allocation_requested | bms.schema.resource.AllocationRequest | TaskMgmt 或 BattleCtrl | ResMgmt | QOS-CMD |
| bms/core/command/resource/allocation_committed | bms.schema.resource.AllocationDecision | ResMgmt | TaskMgmt, BattleCtrl | QOS-PLAN |
| bms/core/resource/state_snapshot | bms.schema.resource.ResourceStateSnapshot | ResMgmt | TaskMgmt, BattleCtrl, HMI | QOS-STATE |

说明：

1. allocation_requested 是资源申请 topic，不代表资源已被锁定。
2. allocation_committed 是资源主拥有者给出的正式裁定输出。
3. ResourceStateSnapshot 用于资源可用性观察，不替代 AllocationDecision。

## 4. 核心对象语义

### 4.1 AllocationRequest

AllocationRequest 是申请对象，不是结果对象。

它至少表达以下信息：

1. 由谁申请。
2. 为哪个 task 或 battle plan 申请。
3. 申请的资源需求项。
4. 期望的生效时间窗。
5. 偏好、排除、降级容忍与预留策略。

正式 payload 结构如下：

```proto
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

### 4.2 AllocationDemand

AllocationDemand 是申请中的单项需求。

每个 demand 用于表达：

1. 需要什么资源类型。
2. 需要多少个。
3. 能力约束。
4. 偏好资源与排除资源。
5. 是否允许降级资源。
6. 是否只申请预留而非立即占用。

### 4.3 AllocationDecision

AllocationDecision 是 ResMgmt 的唯一权威输出。

它至少表达：

1. 该 request 是否被接受。
2. 哪些资源被立即分配。
3. 哪些资源只被预留。
4. 仲裁原因是什么。

正式 payload 如下：

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

## 5. 任务层申请与计划层申请区别

### 5.1 TaskMgmt 发起申请

适用场景：

1. 任务分解阶段需要验证资源前提是否满足。
2. 候选任务方案比选前需要检查关键资源可获得性。
3. 任务重构时需要重新判断约束可满足性。

特点：

1. 关注任务可达成性。
2. 更强调资源前提与时间窗满足。
3. 可接受 reserve_only 申请，用于先占位后确认。

### 5.2 BattleCtrl 发起申请

适用场景：

1. 交战计划生成时需要落到具体成员。
2. 计划调整时需要替换平台、载荷或武器。
3. 执行异常后需要在计划约束内局部换装或换员。

特点：

1. 关注计划可执行性。
2. 更强调成员匹配、即时可调度性和局部替换。
3. 通常要求更强的即时性。

## 6. 裁定规则

### 6.1 accepted 语义

1. accepted = true 表示当前裁定结果被 ResMgmt 正式确认。
2. accepted = true 不等于需求百分之百完全满足。
3. accepted = false 表示当前申请无法形成可接受分配结果。

### 6.2 部分满足

允许出现以下情况：

1. 只分配了部分 demanded count。
2. 只给出 reserved_resource_ids 而未给出 allocated_resource_ids。
3. 使用 allow_degraded = true 的降级资源满足当前申请。

当出现部分满足时：

1. TaskMgmt 需要判断任务约束是否仍成立。
2. BattleCtrl 需要判断计划是否仍可执行。

### 6.3 冲突仲裁

仲裁必须由 ResMgmt 输出，不得由申请方自裁。

arbitration_reason 至少应能解释：

1. 为什么接受或拒绝。
2. 为什么分配这些资源而不是其它资源。
3. 是否存在高优先级冲突占用。

## 7. 时间窗与预留语义

AllocationTimeWindow 用于表达：

1. not_before_utc_ms：最早可生效时间。
2. not_after_utc_ms：最晚必须满足时间。
3. hold_duration_ms：若预留成功，可占位多久。

规则：

1. reserve_only = true 时，ResMgmt 可只返回 reserved_resource_ids。
2. 若预留超时未转实占，后续应由资源管理策略释放。
3. BattleCtrl 不得把预留资源直接当作已可执行资源使用，除非后续策略明确允许。

## 8. 失败与回退

### 8.1 TaskMgmt 侧回退

当 accepted = false 或者部分满足已破坏任务约束时：

1. TaskMgmt 应触发任务方案重构。
2. 必要时回退到新的 TaskConstraint 生成。

### 8.2 BattleCtrl 侧回退

当 accepted = false 但任务约束仍未破坏时：

1. BattleCtrl 可在当前任务约束内重算 BattlePlan。
2. 若重算仍失败，则回退 TaskMgmt 发起任务级重构。

## 9. HMI 解释规则

HMI 或 BFF 消费 AllocationDecision 时必须区分：

1. 已分配。
2. 已预留。
3. 部分满足。
4. 拒绝。

禁止仅以 accepted 一个布尔值向操作者展示“申请成功”。

## 10. 仍待下一阶段细化的内容

1. arbitration_reason 结构化码表。
2. resource_type 标准枚举。
3. 预留释放 topic 与 release ticket 对象。
4. 冲突优先级来源与可解释字段。
