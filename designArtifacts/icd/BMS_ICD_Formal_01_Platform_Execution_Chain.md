# BMS 正式 ICD 专题 01 平台执行链

本文档是字段级 ICD 样板之上的正式 ICD 专题文档，面向平台执行链的关键接口进行系统化说明。

本文档覆盖的平台执行链范围包括：

1. 平台控制命令下发。
2. 平台命令受理应答。
3. 平台执行进度回传。
4. 平台飞行状态与导航状态上报。
5. 平台运行异常与安全告警上报。

## 1. 文档定位

本文档与其它文档的关系如下：

1. 需求来源：sysFunctionalRequirements/sysFunctionalRequirements.md。
2. 架构来源：plantumlC4/C4_L2_Container.puml 与 plantumlC4/C4_L3_Component_11_EnhanceUnit.puml。
3. 契约来源：designArtifacts/contracts/BMS_DDS_Topic_Catalog.md 与 designArtifacts/contracts/BMS_Container_Contract_Matrix.md。
4. schema 来源：proto/bms/schema/platform.proto 与 proto/bms/schema/platform_command.proto。
5. 工程交付映射：designArtifacts/delivery/BMS_Subsystem_Design_Traceability_Matrix.md。

本文档重点补充的是：

1. topic 绑定。
2. 发布方与订阅方。
3. 时序关系。
4. 前置条件。
5. 命令受理语义。
6. 进度和异常联动关系。

## 2. 平台执行链范围

### 2.1 命令类接口

1. bms/edge/platform/command/flight_plan_upload
2. bms/edge/platform/command/flight_mode_set
3. bms/edge/platform/command/takeoff
4. bms/edge/platform/command/rtl
5. bms/edge/platform/command/loiter
6. bms/edge/platform/command/time_sync

### 2.2 状态与事件类接口

1. bms/edge/platform/telemetry/flight_state
2. bms/edge/platform/telemetry/navigation_state
3. bms/edge/platform/event/platform_alert
4. bms/edge/platform/event/command_ack
5. bms/edge/platform/event/mission_progress

## 3. 角色与职责

### 3.1 发布方

1. 交战管控分系统：发布 flight_plan_upload、flight_mode_set、takeoff、rtl、loiter。
2. 任务管理或仿真时钟：发布 time_sync。
3. 协同增强单元：发布 flight_state、navigation_state、platform_alert、command_ack、mission_progress。

### 3.2 订阅方

1. 协同增强单元：订阅全部平台控制命令。
2. 交战管控分系统：订阅 command_ack、platform_alert、mission_progress。
3. 任务管理分系统：订阅 mission_progress。
4. 资源管理分系统：订阅 flight_state、navigation_state。
5. 态势管理分系统：订阅 flight_state。
6. 回放服务：订阅 flight_state、navigation_state。
7. 运维监控与 HMI-BFF：按主题订阅 platform_alert。

## 4. payload 绑定

| topic | payload | 发布方 | 订阅方 |
| --- | --- | --- | --- |
| bms/edge/platform/command/flight_plan_upload | bms.schema.platformcmd.FlightPlanUploadCommand | BattleCtrl | EnhanceUnit |
| bms/edge/platform/command/flight_mode_set | bms.schema.platformcmd.FlightModeSetCommand | BattleCtrl | EnhanceUnit |
| bms/edge/platform/command/takeoff | bms.schema.platformcmd.TakeoffCommand | BattleCtrl | EnhanceUnit |
| bms/edge/platform/command/rtl | bms.schema.platformcmd.RtlCommand | BattleCtrl | EnhanceUnit |
| bms/edge/platform/command/loiter | bms.schema.platformcmd.LoiterCommand | BattleCtrl | EnhanceUnit |
| bms/edge/platform/command/time_sync | bms.schema.platformcmd.TimeSyncCommand | TaskMgmt 或 Simulation | EnhanceUnit |
| bms/edge/platform/telemetry/flight_state | bms.schema.platform.FlightState | EnhanceUnit | ResMgmt, SitMgmt, Replay |
| bms/edge/platform/telemetry/navigation_state | bms.schema.platform.NavigationState | EnhanceUnit | ResMgmt, Replay |
| bms/edge/platform/event/platform_alert | bms.schema.platform.PlatformAlert | EnhanceUnit | BattleCtrl, Monitor, HMI-BFF |
| bms/edge/platform/event/command_ack | bms.schema.platform.CommandAck | EnhanceUnit | BattleCtrl |
| bms/edge/platform/event/mission_progress | bms.schema.platform.MissionProgress | EnhanceUnit | BattleCtrl, TaskMgmt |

## 5. 时序与生命周期

### 5.1 命令下发主时序

命令主路径如下：

1. BattleCtrl 基于 BattlePlan 生成平台控制命令。
2. EnhanceUnit 接收命令并完成平台协议映射。
3. EnhanceUnit 返回 CommandAck 表示是否受理。
4. 命令一旦进入执行，EnhanceUnit 通过 MissionProgress 持续上报执行进度。
5. 执行中若出现飞行安全、链路、导航、平台故障等问题，则额外通过 PlatformAlert 上报异常。

### 5.2 命令受理与执行的区分

必须严格区分以下三个层次：

1. 命令已接收：消息已到达 EnhanceUnit。
2. 命令已受理：CommandAck.accepted = true。
3. 命令已执行或执行中：通过 MissionProgress 或 PlatformAlert 体现。

CommandAck 不代表执行完成，只代表受理结果。

### 5.3 进度与异常联动

1. MissionProgress 用于表达执行阶段、执行位置与执行比例。
2. PlatformAlert 用于表达安全风险、平台故障、禁飞区、导航降级等运行事件。
3. 若平台异常已导致计划无法继续，应进一步在核心业务侧转化为 ExecutionException，而不是由平台层直接输出任务结论。

## 6. 接口前置条件

### 6.1 FlightPlanUploadCommand

前置条件：

1. 平台在线。
2. 当前链路可用。
3. 平台具备航路上传能力。
4. 任务或计划已获得执行授权。

拒绝场景示例：

1. 平台离线。
2. 航点数量超限。
3. 航点动作不在平台支持集合内。
4. 航线穿越禁飞区且未获得豁免。

### 6.2 FlightModeSetCommand

前置条件：

1. 平台处于可切换模式状态。
2. 目标模式允许从当前模式切换。
3. 若目标模式需要特定导航能力，则 NavigationState 必须满足最小质量要求。

### 6.3 TakeoffCommand

前置条件：

1. 平台已解锁或允许自动解锁。
2. 起飞区域满足安全条件。
3. 平台未处于 airborne 状态。

### 6.4 RtlCommand

前置条件：

1. 平台具备返航点或返航逻辑。
2. 当前飞行模式允许进入 RTL。

### 6.5 LoiterCommand

前置条件：

1. 平台支持盘旋模式。
2. loiter_center 合法。
3. radius_m 与 duration_s 满足平台能力限制。

### 6.6 TimeSyncCommand

前置条件：

1. 平台支持时间同步或执行窗口同步。
2. target_time_utc_ms 合法且不晚于系统可接受漂移窗口。

## 7. QoS 与刷新率建议

| 接口 | QoS | 刷新率或触发方式 | 备注 |
| --- | --- | --- | --- |
| flight_plan_upload | QOS-CMD | 事件触发 | 控制命令 |
| flight_mode_set | QOS-CMD | 事件触发 | 控制命令 |
| takeoff | QOS-CMD | 事件触发 | 控制命令 |
| rtl | QOS-CMD | 事件触发 | 控制命令 |
| loiter | QOS-CMD | 事件触发 | 控制命令 |
| time_sync | QOS-CMD | 事件触发或时钟触发 | 同步命令 |
| flight_state | QOS-STATE | 5Hz 到 20Hz | 高频飞行遥测 |
| navigation_state | QOS-STATE | 1Hz 到 5Hz | 导航质量状态 |
| platform_alert | QOS-ALERT | 事件触发 | 风险与故障告警 |
| command_ack | QOS-CMD | 事件触发 | 命令受理应答 |
| mission_progress | QOS-ALERT | 1Hz 到 5Hz 或状态变化触发 | 平台执行进度 |

## 8. 关键状态约束

### 8.1 CommandAck 约束

1. command_id 必须回溯到原始命令。
2. accepted = false 时，reason 必须给出可诊断原因。
3. accepted = true 后，仍允许后续执行失败，失败信息应通过 MissionProgress 异常停滞或 PlatformAlert 体现。

### 8.2 MissionProgress 约束

1. mission_id 与 platform_id 共同标识平台上的任务执行上下文。
2. progress_ratio 必须统一归一到 [0, 1]。
3. current_phase 与 current_waypoint_id 必须与平台执行状态保持一致，不得仅按 UI 展示需要臆造。

### 8.3 FlightState 与 NavigationState 约束

1. FlightState 负责飞行本体状态，不替代导航可信度判断。
2. NavigationState 负责定位质量与健康度，不替代飞行姿态状态。
3. 若导航质量退化，允许同时出现 NavigationState 降级与 PlatformAlert 告警。

## 9. 平台执行链与业务执行链的关系

平台执行链不直接等于业务执行链。

两者关系如下：

1. BattlePlan 是平台执行链的上游业务输入。
2. 平台执行链输出 CommandAck、MissionProgress、PlatformAlert。
3. 核心业务侧再把这些平台层信号吸收为 ExecutionStateSnapshot 或 ExecutionException。
4. TaskMgmt 基于业务执行对象形成更高层任务闭环结论。

因此：

1. 平台层对象不能直接充当任务级结论。
2. 平台层告警不能直接等于任务失败。
3. 平台层进度不能直接替代任务效能评估。

## 10. 正式 ICD 仍待补充的内容

虽然本专题已经比字段样板更接近正式 ICD，但仍有 5 类内容后续应继续补齐：

1. 标准错误码表。
2. FlightMode 切换合法状态表。
3. RouteAction 到真实平台动作集的映射表。
4. PlatformAlert.alert_type 标准码表。
5. MissionProgress.current_phase 标准枚举表与状态迁移图。

## 11. 建议的后续专题

完成平台执行链后，建议下一批正式 ICD 专题按以下顺序推进：

1. 任务-计划-执行闭环专题。
2. 态势与威胁专题。
3. 资源调度专题。
4. BFF 聚合查询与推送专题。
