# BMS DDS Topic 目录与工程化约束

本文档用于支撑 BMS 各容器基于 DDS 解耦，并尽可能贴近现有地面站无人机接口。

## 当前边界说明

1. 当前仓库未包含现有地面站 ICD、报文字段表或控制接口定义。
2. 因此本文档可以做到接口类别、命令方向、状态类型、时序语义、QoS 级别上的严格对齐。
3. 但无法做到字段级 1:1 映射。字段级严格对齐需要补充现有地面站接口定义文件。
4. 建议后续新增一份 地面站接口映射表，将本文 topic 与实际报文 ID、字段、单位、枚举逐项绑定。

## 设计原则

1. 现有地面站报文先进入边缘协议桥，转换为统一内部标准模型后再入 DDS。
2. 核心业务只消费内部标准主题，不直接消费地面站私有报文。
3. 高速遥测、感知数据、任务事件、告警事件分域处理，避免互相干扰。
4. 命令主题与状态主题严格分离，避免双向混杂。
5. 所有主题必须包含 source_id、platform_id、mission_id、event_time、trace_id 中的适用字段。

## 域划分建议

| Domain | 名称 | 用途 |
| --- | --- | --- |
| 0 | core.ops | 运维、部署、配置、审计 |
| 1 | core.command | 任务、交战、资源主业务 |
| 2 | core.situation | 态势、融合、告警、回放 |
| 3 | edge.platform | 边缘平台控制、遥测、链路 |
| 4 | edge.payload | 传感器、图像、目标、武器 |
| 5 | simulation | 仿真、真值、时钟、导演控制 |

## Topic 命名规则

命名规则统一为：

`bms/<domain>/<subdomain>/<entity>/<message>`

示例：

- bms/edge/platform/uav/flight_state
- bms/core/command/task/plan_created
- bms/edge/payload/eo/target_report

## QoS 预置档

| QoS 档 | Reliability | Durability | History | Deadline | 适用场景 |
| --- | --- | --- | --- | --- | --- |
| QOS-CMD | Reliable | Volatile | KeepLast(10) | 200ms | 控制命令、确认、应答 |
| QOS-STATE | BestEffort | Volatile | KeepLast(5) | 100ms | 高频状态、姿态、链路指标 |
| QOS-TRACK | Reliable | Volatile | KeepLast(20) | 500ms | 目标航迹、融合结果 |
| QOS-ALERT | Reliable | TransientLocal | KeepLast(50) | 1s | 告警、事件、审计 |
| QOS-PLAN | Reliable | TransientLocal | KeepLast(20) | 1s | 任务方案、交战计划 |
| QOS-REPLAY | Reliable | TransientLocal | KeepAll | 无 | 回放、复盘、取证 |
| QOS-VIDEO-META | BestEffort | Volatile | KeepLast(3) | 100ms | 视频关键帧元数据 |

## 现有地面站接口对齐策略

### 上行控制类接口对齐

| 地面站接口类别 | 对应 DDS 主题族 | 说明 |
| --- | --- | --- |
| 飞行控制指令下发 | edge.platform.command.flight_* | 航点、航线、模式、起降、返航、盘旋 |
| 吊舱控制指令下发 | edge.payload.command.gimbal_* | 指向、俯仰、变焦、跟踪开关 |
| 武器控制指令下发 | edge.payload.command.weapon_* | 挂载选择、解锁、发射、中止 |
| 协同任务/航路下发 | core.command.battle_*、edge.platform.command.mission_* | 核心计划到边缘执行转换 |
| 授时/同步控制 | edge.platform.command.time_sync | 时间同步与执行窗口控制 |

### 下行状态类接口对齐

| 地面站接口类别 | 对应 DDS 主题族 | 说明 |
| --- | --- | --- |
| 无人机飞行状态采集与上报 | edge.platform.telemetry.flight_state | 位置、速度、航向、姿态、模式、航点执行状态 |
| 传感器状态采集与上报 | edge.payload.telemetry.sensor_state | EO/IR/雷达在线状态、模式、工作参数 |
| 武器状态采集与上报 | edge.payload.telemetry.weapon_state | 挂载、余量、保险、发射状态、故障 |
| 通信链路状态采集 | edge.platform.telemetry.link_state | RSSI、丢包、时延、带宽、链路等级 |
| 告警/故障上报 | edge.platform.event.platform_alert | 飞行安全、载荷故障、链路异常 |

## Topic 目录

### A. 核心任务与交战域

| Topic | 发布者 | 订阅者 | QoS | Key 字段 | 说明 |
| --- | --- | --- | --- | --- | --- |
| bms/core/command/task/command_received | 外部接口管理 | 任务管理 | QOS-CMD | command_id | 上级或人工任务指令入域 |
| bms/core/command/task/decomposed | 任务管理 | 交战管控, 资源管理 | QOS-PLAN | mission_id | 任务分解结果 |
| bms/core/command/task/plan_created | 任务管理 | HMI-BFF, 交战管控 | QOS-PLAN | plan_id | 候选方案生成 |
| bms/core/command/task/plan_confirmed | HMI-BFF | 任务管理, 交战管控 | QOS-CMD | plan_id | 指挥员确认方案 |
| bms/core/command/battle/plan_created | 交战管控 | 边缘执行, HMI-BFF | QOS-PLAN | battle_plan_id | 交战计划创建 |
| bms/core/command/battle/plan_updated | 交战管控 | 边缘执行, HMI-BFF | QOS-PLAN | battle_plan_id | 计划调整 |
| bms/core/command/battle/fire_authorized | HMI-BFF | 交战管控, 边缘执行 | QOS-CMD | engagement_id | 发射授权 |
| bms/core/command/battle/abort | 交战管控 | 边缘执行 | QOS-CMD | engagement_id | 中止交战 |
| bms/core/command/battle/effect_report | 交战管控 | 任务管理, HMI-BFF | QOS-ALERT | engagement_id | 打击效果评估 |
| bms/core/command/resource/allocation_requested | 任务管理, 交战管控 | 资源管理 | QOS-CMD | request_id | 资源匹配请求 |
| bms/core/command/resource/allocation_committed | 资源管理 | 任务管理, 交战管控 | QOS-PLAN | allocation_id | 资源分配结果 |

### B. 态势与融合域

| Topic | 发布者 | 订阅者 | QoS | Key 字段 | 说明 |
| --- | --- | --- | --- | --- | --- |
| bms/core/situation/track/raw_target_ingested | 协同增强单元, 外部接口管理 | 态势管理 | QOS-TRACK | raw_track_id | 标准化原始目标输入 |
| bms/core/situation/track/fused_track | 态势管理 | 交战管控, HMI-BFF | QOS-TRACK | track_id | 融合航迹 |
| bms/core/situation/track/track_lost | 态势管理 | HMI-BFF, 交战管控 | QOS-ALERT | track_id | 航迹丢失 |
| bms/core/situation/target/feature_snapshot | 态势管理 | HMI-BFF, 交战管控, 知识规则 | QOS-ALERT | feature_id | 目标观察特征快照 |
| bms/core/situation/target/status_updated | 态势管理 | HMI-BFF, 交战管控 | QOS-ALERT | status_id | 目标状态与毁伤状态更新 |
| bms/core/situation/threat/assessed | 态势管理 | HMI-BFF, 交战管控 | QOS-ALERT | threat_id | 威胁评估结果 |
| bms/core/knowledge/inference/requested | 态势管理, 任务管理, 交战管控 | 知识规则 | QOS-CMD | request_id | 规则推理请求 |
| bms/core/knowledge/inference/recommended | 知识规则 | 态势管理, 任务管理, 交战管控 | QOS-ALERT | recommendation_id | 推理推荐与解释输出 |
| bms/core/situation/alert/critical_event | 态势管理 | HMI-BFF, 运维监控 | QOS-ALERT | alert_id | 关键事件告警 |
| bms/core/situation/report/summary_generated | 态势管理 | 外部接口管理, HMI-BFF | QOS-ALERT | report_id | 态势简报 |
| bms/core/situation/replay/frame | 回放服务 | HMI-BFF | QOS-REPLAY | replay_id | 态势回放帧 |

### C. 边缘平台控制域

| Topic | 发布者 | 订阅者 | QoS | Key 字段 | 对齐地面站接口 |
| --- | --- | --- | --- | --- | --- |
| bms/edge/platform/command/flight_plan_upload | 交战管控 | 协同增强单元 | QOS-CMD | plan_id | 航路/航点上传 |
| bms/edge/platform/command/flight_mode_set | 交战管控 | 协同增强单元 | QOS-CMD | command_id | 飞行模式切换 |
| bms/edge/platform/command/takeoff | 交战管控 | 协同增强单元 | QOS-CMD | command_id | 起飞 |
| bms/edge/platform/command/rtl | 交战管控 | 协同增强单元 | QOS-CMD | command_id | 返航 |
| bms/edge/platform/command/loiter | 交战管控 | 协同增强单元 | QOS-CMD | command_id | 盘旋 |
| bms/edge/platform/command/time_sync | 任务管理, 仿真时钟 | 协同增强单元 | QOS-CMD | sync_id | 授时/执行窗口 |
| bms/edge/platform/telemetry/flight_state | 协同增强单元 | 资源管理, 态势管理, 回放服务 | QOS-STATE | platform_id | 飞行状态采集与上报 |
| bms/edge/platform/telemetry/navigation_state | 协同增强单元 | 资源管理, 回放服务 | QOS-STATE | platform_id | 导航/定位质量 |
| bms/edge/platform/telemetry/link_state | 通信组网, 协同增强单元 | 资源管理, 运维监控 | QOS-STATE | platform_id | 通信链路状态 |
| bms/edge/platform/event/platform_alert | 协同增强单元 | 交战管控, 运维监控, HMI-BFF | QOS-ALERT | alert_id | 飞行安全/故障/禁飞告警 |
| bms/edge/platform/event/command_ack | 协同增强单元 | 交战管控 | QOS-CMD | command_id | 控制命令应答 |
| bms/edge/platform/event/mission_progress | 协同增强单元 | 交战管控, 任务管理 | QOS-ALERT | mission_id | 执行进度 |

### D. 边缘载荷与传感器域

| Topic | 发布者 | 订阅者 | QoS | Key 字段 | 对齐地面站接口 |
| --- | --- | --- | --- | --- | --- |
| bms/edge/payload/command/gimbal_point | 交战管控 | 协同增强单元 | QOS-CMD | command_id | 吊舱指向 |
| bms/edge/payload/command/gimbal_track_start | 交战管控 | 协同增强单元 | QOS-CMD | command_id | 吊舱跟踪开启 |
| bms/edge/payload/command/radar_mode_set | 交战管控 | 协同增强单元 | QOS-CMD | command_id | 雷达模式设置 |
| bms/edge/payload/telemetry/sensor_state | 协同增强单元 | 资源管理, HMI-BFF | QOS-STATE | sensor_id | 传感器状态采集 |
| bms/edge/payload/telemetry/gimbal_state | 协同增强单元 | HMI-BFF, 回放服务 | QOS-STATE | sensor_id | 吊舱姿态与模式 |
| bms/edge/payload/telemetry/radar_state | 协同增强单元 | HMI-BFF, 回放服务 | QOS-STATE | sensor_id | 雷达状态 |
| bms/edge/payload/perception/eo_target_report | 协同增强单元 | 态势管理 | QOS-TRACK | target_id | 光电目标报告 |
| bms/edge/payload/perception/radar_plot_report | 协同增强单元 | 态势管理 | QOS-TRACK | plot_id | 雷达点迹 |
| bms/edge/payload/perception/radar_track_report | 协同增强单元 | 态势管理 | QOS-TRACK | track_id | 雷达航迹 |
| bms/edge/payload/perception/video_keyframe_meta | 协同增强单元 | 态势管理, 回放服务 | QOS-VIDEO-META | frame_id | 视频关键帧元数据 |
| bms/edge/payload/perception/image_mosaic_meta | 协同增强单元 | 态势管理, 回放服务 | QOS-REPLAY | mosaic_id | 拼接图元数据 |

### E. 边缘武器域

| Topic | 发布者 | 订阅者 | QoS | Key 字段 | 对齐地面站接口 |
| --- | --- | --- | --- | --- | --- |
| bms/edge/payload/command/weapon_select | 交战管控 | 协同增强单元 | QOS-CMD | command_id | 挂载选择 |
| bms/edge/payload/command/weapon_arm | 交战管控 | 协同增强单元 | QOS-CMD | command_id | 解保/预备 |
| bms/edge/payload/command/weapon_release | 交战管控 | 协同增强单元 | QOS-CMD | command_id | 发射/投放 |
| bms/edge/payload/command/weapon_abort | 交战管控 | 协同增强单元 | QOS-CMD | command_id | 中止投放 |
| bms/edge/payload/telemetry/weapon_state | 协同增强单元 | 资源管理, HMI-BFF, 回放服务 | QOS-STATE | weapon_id | 武器状态采集 |
| bms/edge/payload/event/weapon_release_ack | 协同增强单元 | 交战管控 | QOS-CMD | command_id | 发射应答 |
| bms/edge/payload/event/weapon_effect_raw | 协同增强单元 | 交战管控, 仿真裁决 | QOS-ALERT | engagement_id | 原始毁伤结果 |

### F. 资源与注册域

| Topic | 发布者 | 订阅者 | QoS | Key 字段 | 说明 |
| --- | --- | --- | --- | --- | --- |
| bms/core/resource/state_snapshot | 资源管理 | HMI-BFF, 任务管理, 交战管控 | QOS-STATE | resource_id | 资源统一状态快照 |
| bms/core/command/resource/platform_registered | 协同增强单元 | 资源管理 | QOS-ALERT | platform_id | 平台注册 |
| bms/core/command/resource/platform_unregistered | 协同增强单元 | 资源管理 | QOS-ALERT | platform_id | 平台下线 |
| bms/core/command/resource/capability_reported | 协同增强单元 | 资源管理 | QOS-ALERT | platform_id | 平台/传感器/武器能力模型 |
| bms/core/command/resource/state_changed | 资源管理 | HMI-BFF, 任务管理, 交战管控 | QOS-ALERT | platform_id | 可用性变化 |
| bms/core/command/resource/health_changed | 资源管理 | HMI-BFF, 运维监控 | QOS-ALERT | platform_id | 健康度变化 |

### G. 通信与网络域

| Topic | 发布者 | 订阅者 | QoS | Key 字段 | 说明 |
| --- | --- | --- | --- | --- | --- |
| bms/core/ops/comm/link_quality | 通信组网 | 运维监控, 资源管理 | QOS-STATE | link_id | 丢包/时延/带宽 |
| bms/core/ops/comm/topology_changed | 通信组网 | 运维监控 | QOS-ALERT | topology_id | 拓扑变化 |
| bms/core/ops/comm/link_degraded | 通信组网 | 运维监控, 交战管控 | QOS-ALERT | link_id | 链路降级 |
| bms/core/ops/comm/security_event | 通信组网 | 安全审计, 运维监控 | QOS-ALERT | event_id | 认证失败/干扰告警 |

### H. 仿真域

| Topic | 发布者 | 订阅者 | QoS | Key 字段 | 说明 |
| --- | --- | --- | --- | --- | --- |
| bms/simulation/control/scenario_load | 场景编排器 | 飞行仿真器, 传感器仿真器, 武器仿真器, 真值服务 | QOS-CMD | scenario_id | 加载场景 |
| bms/simulation/control/scenario_start | 场景编排器 | 全部仿真器 | QOS-CMD | scenario_id | 启动仿真 |
| bms/simulation/control/scenario_pause | 场景编排器 | 全部仿真器 | QOS-CMD | scenario_id | 暂停仿真 |
| bms/simulation/control/clock_tick | 仿真时钟 | 全部仿真器, 协同增强单元 | QOS-STATE | tick_id | 仿真时间推进 |
| bms/simulation/platform/flight_state | 飞行仿真器 | 协同增强单元, 回放服务 | QOS-STATE | platform_id | 仿真飞行状态 |
| bms/simulation/payload/sensor_state | 传感器仿真器 | 协同增强单元, 回放服务 | QOS-STATE | sensor_id | 仿真传感器状态 |
| bms/simulation/payload/weapon_state | 武器仿真器 | 协同增强单元, 回放服务 | QOS-STATE | weapon_id | 仿真武器状态 |
| bms/simulation/payload/target_truth | 真值服务 | 态势管理, 回放服务, 评估模块 | QOS-REPLAY | target_id | 真值目标 |
| bms/simulation/payload/weapon_adjudication | 真值服务 | 交战管控, 回放服务 | QOS-ALERT | engagement_id | 裁决结果 |

### I. 运维与安全域

| Topic | 发布者 | 订阅者 | QoS | Key 字段 | 说明 |
| --- | --- | --- | --- | --- | --- |
| bms/core/ops/msg/topic_defined | 消息服务 | 运维监控 | QOS-ALERT | topic | TopicDefinition 变更事件 |
| bms/core/ops/msg/delivery_receipt | 消息服务 | 运维监控, 发布者 | QOS-STATE | receipt_id | 投递回执 |
| bms/core/ops/msg/dead_letter | 消息服务 | 运维监控 | QOS-ALERT | dead_letter_id | 死信记录 |
| bms/core/ops/sec/audit_event | 安全审计 | 运维监控 | QOS-ALERT | audit_id | 审计事件 |
| bms/core/ops/monitor/metric | 监控与日志 | 运维管理 | QOS-STATE | metric_id | 统一指标流 |
| bms/core/ops/monitor/alert | 监控与日志 | 运维管理, HMI-BFF | QOS-ALERT | alert_id | 统一监控告警 |
| bms/core/ops/deploy/release_event | 版本部署 | 运维监控, 运维管理 | QOS-ALERT | release_id | 发布与回滚事件 |
| bms/core/ops/config/config_changed | 运维管理 | 全部相关服务 | QOS-ALERT | config_id | 配置变更 |

### J. 前端聚合与推送域

| Topic | 发布者 | 订阅者 | QoS | Key 字段 | 说明 |
| --- | --- | --- | --- | --- | --- |
| bms/ui/push/dashboard | API Gateway / BFF | HMI 前端 | QOS-ALERT | trace_id | 总览聚合推送 |
| bms/ui/push/alert_stream | API Gateway / BFF | HMI 前端 | QOS-ALERT | alert_id | 告警流推送 |

## 必备公共字段

| 字段 | 含义 |
| --- | --- |
| trace_id | 跨容器全链路追踪标识 |
| event_time | 事件时间，统一使用 UTC |
| source_id | 发布源容器或设备 |
| platform_id | 平台唯一标识 |
| mission_id | 任务唯一标识 |
| scenario_id | 仿真场景唯一标识 |
| schema_version | 消息结构版本 |

## 下一步落地建议

1. 将本目录转换为统一 IDL 或 schema 仓库。
2. 新增 地面站接口映射表，逐条绑定真实报文 ID、字段、量纲、字节序与枚举。
3. 为每个 topic 补充示例报文、错误码、超时与重试策略。
4. 在双 Nano 部署中引入 DDS Router 或 Discovery Server，明确跨板 topic 白名单。
