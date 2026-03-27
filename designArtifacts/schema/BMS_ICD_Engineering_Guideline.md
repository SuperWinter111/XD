# BMS ICD 工程化约束说明

本文档用于明确 proto 与 ICD 的关系，并给出后续工程化接口设计的落地方向。

## 1. proto 与 ICD 的关系

结论：proto 不是完整 ICD，但 proto 是后续 ICD 中最核心、最稳定、最适合机器执行的一层。

更准确地说：

1. proto 定义的是接口 payload 的结构化数据模型。
2. DDS topic、REST API、gRPC、文件回放都可以复用同一套 proto 对象。
3. 完整 ICD 除了 payload 结构，还必须包含时序、单位、范围、精度、异常码、重试、前置条件等工程信息。

所以后续建议采用二层结构：

1. proto/IDL：定义字段结构、对象关系、枚举、版本兼容。
2. ICD 文档：定义接口方向、主题名、更新率、量纲、精度、阈值、异常处理、状态机、样例报文。

## 2. 一个完整 ICD 至少应包含的内容

建议每个接口条目至少包括以下 12 项：

1. 接口标识：接口名称、topic 或 API 名称、方向。
2. 发布方与订阅方：谁发、谁收、谁拥有定义权。
3. payload 类型：对应 proto 的 message 名。
4. 字段表：字段名、类型、单位、精度、取值范围、必填性。
5. 时序约束：刷新率、超时、心跳周期、重试策略。
6. QoS 约束：可靠性、持久性、历史缓存、deadline。
7. 触发条件：周期触发、事件触发、人工触发。
8. 前置条件：链路状态、授权状态、飞行模式、载荷状态等。
9. 异常码与返回码：拒绝原因、降级原因、错误码。
10. 状态机约束：状态流转、合法动作、禁止动作。
11. 版本策略：schema_version、向后兼容规则、废弃字段。
12. 示例报文：正常样例、异常样例、边界样例。

## 3. 对当前工程的建议分层

结合你当前这套 BMS，我建议把接口分成三层：

1. 业务层 ICD：TaskPackage、BattlePlan、FusedTrack、AllocationDecision 等。
2. 平台层 ICD：FlightState、NavigationState、PlatformAlert、CommandAck、MissionProgress 等。
3. 仿真层 ICD：ScenarioLoadCommand、ClockTick、TargetTruth、WeaponAdjudication 等。

其中：

1. 业务层 ICD 更关注任务/计划/态势语义。
2. 平台层 ICD 更关注航空电子、飞控、载荷、武器、链路等工程字段。
3. 仿真层 ICD 更关注场景控制、真值、裁决、回放一致性。

## 4. 无人机状态接口应如何工程化

你提到的这个方向是对的。无人机状态接口不能只做一个抽象的 platform_state，而应该至少拆成下列维度：

1. 位置：经度、纬度、高度。
2. 姿态：滚转角、俯仰角、航向角。
3. 速度：北东地速度、地速、垂速。
4. 空气数据：指示空速、真空速、马赫数、攻角、侧滑角、气压高度。
5. 动力系统：油门、转速、发动机温度、燃油流量。
6. 能源系统：油量、油量百分比、电压、电流、电量百分比。
7. 导航质量：GNSS 定位类型、星数、HDOP、VDOP、位置误差。
8. 飞行模式：AUTO、GUIDED、RTL、LOITER、LAND 等。
9. 安全状态：是否解锁、是否在空、告警、故障、禁飞约束。

也就是说，后续真正工程化的接口，不应该只有一句“飞行状态采集与上报”，而应该形成：

1. FlightState
2. NavigationState
3. PlatformAlert
4. CommandAck
5. MissionProgress

这些对象再分别绑定到 topic。

## 5. 当前已落实的工程动作

为了顺着这个方向推进，当前已经新增了：

1. proto/bms/schema/platform.proto

其中包含：

1. FlightState
2. NavigationState
3. PlatformAlert
4. CommandAck
5. MissionProgress
6. 以及子结构：GeoPointLla、AttitudeEuler、VelocityNed、AirDataState、PropulsionState、PowerState

这意味着后续你可以把：

1. bms/edge/platform/telemetry/flight_state
2. bms/edge/platform/telemetry/navigation_state
3. bms/edge/platform/event/platform_alert
4. bms/edge/platform/event/command_ack
5. bms/edge/platform/event/mission_progress

逐步绑定到更工程化的 payload，而不再停留在粗粒度平台状态。

## 6. 后续推荐做法

建议你后续按这个顺序推进：

1. 先把 edge/platform 相关 topic 全部绑定到 platform.proto 中的具体 message。
2. 为每个 message 补字段表：单位、范围、精度、是否必填。
3. 再补命令类 message，例如起飞、返航、航路上传、模式切换、授时同步。
4. 最后再做地面站真实报文到 proto 的映射表。

## 7. 最关键的一条判断

如果你的目标是“后续各个分系统的 ICD 尽可能工程化完备”，那么正确路线不是“只写文档”或者“只写 proto”，而是：

1. 用 proto 固定数据结构。
2. 用 ICD 文档固定工程语义。
3. 用 topic/API 绑定表固定系统接线关系。

这三者一起，才是完整可执行的 ICD 体系。
