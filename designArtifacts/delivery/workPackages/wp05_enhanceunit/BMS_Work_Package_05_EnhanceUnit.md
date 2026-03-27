# BMS 工作包 05 EnhanceUnit

本文档是协同增强单元分系统的可执行工作包，供软件工程师或 agent 直接领取并进入实现。

## 1. 基本信息

1. 分系统名称：EnhanceUnit。
2. 负责人类型：软件工程师或 agent。
3. 对应 Container：plantumlC4/C4_L2_Container.puml 中协同增强单元分系统。
4. 对应 Component 图：plantumlC4/C4_L3_Component_11_EnhanceUnit.puml。
5. 对应 Code 图：plantumlC4/Code_01_EnhanceUnit.puml。
6. 对应正式 ICD：BMS_ICD_Formal_01、09。

## 2. 目标范围

1. 接收 BattleCtrl 下发的 BattlePlan，并翻译为平台与载荷侧可执行命令。
2. 统一接入真实平台和仿真平台的飞行、载荷、武器与执行状态流。
3. 向 BattleCtrl、TaskMgmt 回传 command_ack、mission_progress 与 platform_alert。
4. 向 SitMgmt 提供边缘感知原始输入，向 ResMgmt 提供平台注册与能力上报。
5. 作为核心业务域与边缘平台之间的桥接层，保持语义边界稳定。

不包含：

1. 任务语义建模与交战计划生成。
2. 资源权威裁定。
3. 态势融合与规则推理本体实现。

## 3. 对象边界

### 3.1 主拥有对象

1. PlatformCommand。
2. CommandAck。
3. MissionProgress。
4. PlatformAlert。
5. PlatformState。
6. PayloadState。
7. WeaponState。

### 3.2 只读消费对象

1. BattlePlan。
2. RouteSegment。
3. ClockTick。
4. SimFlightState。
5. SimSensorState。
6. SimWeaponState。
7. TargetTruth。

### 3.3 禁止越权修改

1. 不得直接生成或改写 TaskPackage。
2. 不得直接生成或改写 BattlePlan。
3. 不得把仿真真值冒充为真实融合态势对象。
4. 不得让边缘原始状态直接对外宣称为 CapabilityProfile 权威结果。

## 4. topic 责任

### 4.1 发布 topic

| topic | payload | 触发条件 | 下游 |
| --- | --- | --- | --- |
| bms/edge/platform/event/command_ack | CommandAck | 平台受理或拒绝指令 | BattleCtrl, TaskMgmt |
| bms/edge/platform/event/mission_progress | MissionProgress | 平台执行状态变化 | BattleCtrl, TaskMgmt |
| bms/edge/platform/event/platform_alert | PlatformAlert | 平台告警或异常触发 | BattleCtrl, MonitorLog |
| bms/edge/platform/event/platform_registered | ResourceRegistration | 平台注册、上线或能力刷新 | ResMgmt |
| edge.payload/perception/* | RawTargetInput | 边缘感知上报 | SitMgmt |

### 4.2 订阅 topic

| topic | payload | 上游 | 消费动作 |
| --- | --- | --- | --- |
| bms/core/command/battle/plan_created | BattlePlan | BattleCtrl | 生成首轮平台命令 |
| bms/core/command/battle/plan_updated | BattlePlan | BattleCtrl | 更新执行命令 |
| bms/simulation/* | ClockTick, SimFlightState 等 | Simulation | 驱动仿真模式执行 |

## 5. 模块拆分

| 模块 | 责任 | 输入 | 输出 |
| --- | --- | --- | --- |
| CommandTranslator | 将 BattlePlan 转换为平台命令 | BattlePlan | PlatformCommand |
| PlatformCommandService | 下发飞行、载荷和武器命令 | PlatformCommand | 平台调用结果 |
| ExecutionFeedbackBridge | 汇总 command_ack、mission_progress 和 platform_alert | 平台状态流 | 执行反馈事件 |
| CapabilityReporter | 整理平台注册与能力上报 | PlatformState, PayloadState, WeaponState | ResourceRegistration |
| SimulationBridge | 接入仿真时钟与仿真平台状态 | ClockTick, SimFlightState | 仿真执行反馈 |
| PerceptionBridge | 输出边缘感知上报 | 传感器原始输出 | RawTargetInput |

## 6. 实施步骤

1. 先实现 CommandTranslator，打通 BattlePlan 到平台命令主链。
2. 实现 PlatformCommandService，覆盖命令下发与受理回执。
3. 接入 mission_progress 与 platform_alert，补齐执行反馈路径。
4. 接入平台注册与能力上报，补齐对 ResMgmt 的状态供给。
5. 最后接入 SimulationBridge 与 PerceptionBridge，形成仿真和感知输入支撑。

## 7. 测试与验收

### 7.1 必备样例

1. 正常样例：flight_plan_upload -> command_ack.accepted -> mission_progress。
2. 异常样例：平台拒绝命令或任务中断触发 platform_alert。
3. 边界样例：仿真状态流与真实平台状态流保持语义分离。

### 7.2 契约测试

1. 平台命令、回执与进度对象必须符合 Formal 01。
2. 仿真时钟与仿真状态接入边界必须符合 Formal 09。
3. CommandAck 仅表示受理结果，不代表任务完成。
4. 原始感知输入不得越权代替 SitMgmt 的融合结果。

### 7.3 完成定义

1. Code_01_EnhanceUnit 的主模块已形成实现骨架。
2. BattlePlan 到 command_ack 的主链可验证。
3. 与 BattleCtrl、SitMgmt、ResMgmt 的主要联调项已映射到联调矩阵。
4. 已准备主业务闭环场景 A、C 与仿真相关样例。

## 8. 风险与待决项

1. 风险：多平台协议差异可能使命令翻译层快速膨胀。
2. 风险：真实平台与仿真平台的状态刷新节奏差异会影响反馈一致性。
3. 待决项：边缘感知对象的最小归一化粒度是否需要在后续样例中继续收敛。
