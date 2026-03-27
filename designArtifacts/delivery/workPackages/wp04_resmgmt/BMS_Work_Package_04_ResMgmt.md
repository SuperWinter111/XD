# BMS 工作包 04 ResMgmt

本文档是资源管理分系统的可执行工作包，供软件工程师或 agent 直接领取并进入实现。

## 1. 基本信息

1. 分系统名称：ResMgmt。
2. 负责人类型：软件工程师或 agent。
3. 对应 Container：plantumlC4/C4_L2_Container.puml 中资源管理分系统。
4. 对应 Component 图：plantumlC4/C4_L3_Component_06_ResMgmt.puml。
5. 对应 Code 图：plantumlC4/Code_05_ResMgmt.puml。
6. 对应正式 ICD：BMS_ICD_Formal_03、07。

## 2. 目标范围

1. 汇聚平台注册、在线状态、能力、载荷和武器状态，形成 ResourceStateSnapshot 与 CapabilityProfile。
2. 接收 AllocationRequest，给出唯一权威的 AllocationDecision。
3. 支持部分满足、预留、拒绝与释放场景的资源裁定。
4. 将链路质量与降级告警纳入资源可用性判断。
5. 向 TaskMgmt 和 BattleCtrl 提供可追踪的资源裁定与状态结果。

不包含：

1. 任务分解与交战计划生成。
2. 平台底层协议适配实现。
3. 网络链路检测算法本体实现。

## 3. 对象边界

### 3.1 主拥有对象

1. ResourceRegistration。
2. ResourceDescriptor。
3. ResourceStateSnapshot。
4. CapabilityProfile。
5. AllocationDecision。
6. ReservationTicket。

### 3.2 只读消费对象

1. AllocationRequest。
2. FlightState。
3. SensorState。
4. WeaponState。
5. LinkQualitySnapshot。
6. DegradationAlert。

### 3.3 禁止越权修改

1. 不得直接生成 TaskPackage。
2. 不得直接生成 BattlePlan。
3. 不得让申请方自裁资源结果。
4. 不得把链路事件直接当作持续资源状态对象落权威结果。

## 4. topic 责任

### 4.1 发布 topic

| topic | payload | 触发条件 | 下游 |
| --- | --- | --- | --- |
| bms/core/resource/state_snapshot | ResourceStateSnapshot | 资源注册、状态变更或周期汇总 | TaskMgmt, BattleCtrl |
| bms/core/command/resource/allocation_committed | AllocationDecision | 完成资源裁定 | TaskMgmt, BattleCtrl |
| bms/core/resource/reservation_updated | ReservationTicket | 进入预留或释放场景 | TaskMgmt, BattleCtrl |

### 4.2 订阅 topic

| topic | payload | 上游 | 消费动作 |
| --- | --- | --- | --- |
| bms/core/command/resource/allocation_requested | AllocationRequest | TaskMgmt, BattleCtrl | 启动资源裁定流程 |
| bms/edge/platform/event/platform_registered | ResourceRegistration | EnhanceUnit | 记录平台注册与上线 |
| bms/edge/platform/event/flight_state | FlightState | EnhanceUnit | 刷新飞行状态 |
| bms/edge/platform/event/sensor_state | SensorState | EnhanceUnit | 刷新载荷状态 |
| bms/edge/platform/event/weapon_state | WeaponState | EnhanceUnit | 刷新武器状态 |
| bms/core/ops/comm/link_quality | LinkQualitySnapshot | CommNet | 刷新链路质量评分 |
| bms/core/ops/comm/link_degraded | DegradationAlert | CommNet | 在裁定中考虑降级影响 |

## 5. 模块拆分

| 模块 | 责任 | 输入 | 输出 |
| --- | --- | --- | --- |
| ResourceRegistry | 管理平台注册、分类与在线状态 | ResourceRegistration, FlightState | ResourceDescriptor |
| CapabilityAggregator | 聚合平台、载荷、武器能力 | SensorState, WeaponState | CapabilityProfile |
| ResourceSchedulingService | 执行资源分配策略 | AllocationRequest, CapabilityProfile | AllocationDecision |
| ConflictArbitrationService | 处理冲突、部分满足与拒绝 | AllocationRequest, 当前占用状态 | 仲裁原因 |
| ReservationManager | 管理预留、释放与时间窗 | AllocationDecision | ReservationTicket |
| LinkImpactEvaluator | 把链路质量纳入资源可用性 | LinkQualitySnapshot, DegradationAlert | 可用性修正结果 |

## 6. 实施步骤

1. 先实现 ResourceRegistry，打通平台注册与状态快照主链。
2. 接入 CapabilityAggregator，形成 CapabilityProfile。
3. 实现 ResourceSchedulingService，完成 allocation_requested 到 allocation_committed 主链。
4. 补齐 ConflictArbitrationService 与 ReservationManager，支持部分满足与预留场景。
5. 接入链路质量输入，完成通信约束下的资源裁定。

## 7. 测试与验收

### 7.1 必备样例

1. 正常样例：AllocationRequest -> AllocationDecision.accepted。
2. 异常样例：accepted = false 或仅部分满足的裁定场景。
3. 边界样例：reserve_only 与即时分配明确区分，AllocationRequest 不冒充 AllocationDecision。

### 7.2 契约测试

1. AllocationDecision、ReservationTicket 与理由字段必须符合 Formal 03。
2. ResourceStateSnapshot 与 CapabilityProfile 的消费边界必须稳定。
3. LinkQualitySnapshot 与 DegradationAlert 的使用边界必须符合 Formal 07。
4. trace_id 必须贯穿 allocation_requested、allocation_committed 与 reservation_updated。

### 7.3 完成定义

1. Code_05_ResMgmt 的关键模块已形成实现骨架。
2. state_snapshot 与 allocation_committed 两条主链可验证。
3. 与 TaskMgmt、BattleCtrl、EnhanceUnit、CommNet 的联调项已映射到联调矩阵。
4. 已准备主业务闭环场景 A、B、C 所需资源样例与验收记录。

## 8. 风险与待决项

1. 风险：平台能力模型与链路约束同时变化时，裁定规则可能快速复杂化。
2. 风险：部分满足与预留策略若未明确优先级，容易导致下游误判 accepted 含义。
3. 待决项：ReservationTicket 的生命周期事件是否需要补充更细粒度 topic。
