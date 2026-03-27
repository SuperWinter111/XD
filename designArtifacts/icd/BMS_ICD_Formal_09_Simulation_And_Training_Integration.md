# BMS 正式 ICD 专题 09 仿真训练接口

本文档定义 BMS 与仿真训练环境之间的场景控制、时钟推进、仿真状态、目标真值与裁决结果接口约束。

## 1. 文档定位

本文档覆盖以下对象：

1. ScenarioLoadCommand。
2. ScenarioControlCommand。
3. ClockTick。
4. SimFlightState、SimSensorState、SimWeaponState。
5. TargetTruth。
6. WeaponAdjudication。

## 2. Topic 绑定

| topic | payload | 发布方 | 订阅方 | QoS |
| --- | --- | --- | --- | --- |
| bms/simulation/control/scenario_load | bms.schema.simulation.ScenarioLoadCommand | 场景编排器 | 仿真器集群 | QOS-CMD |
| bms/simulation/control/scenario_start | bms.schema.simulation.ScenarioControlCommand | 场景编排器 | 仿真器集群 | QOS-CMD |
| bms/simulation/control/scenario_pause | bms.schema.simulation.ScenarioControlCommand | 场景编排器 | 仿真器集群 | QOS-CMD |
| bms/simulation/control/clock_tick | bms.schema.simulation.ClockTick | 仿真时钟 | 仿真器集群, EnhanceUnit | QOS-STATE |
| bms/simulation/platform/flight_state | bms.schema.simulation.SimFlightState | 飞行仿真器 | EnhanceUnit, 回放服务 | QOS-STATE |
| bms/simulation/payload/sensor_state | bms.schema.simulation.SimSensorState | 传感器仿真器 | EnhanceUnit, 回放服务 | QOS-STATE |
| bms/simulation/payload/weapon_state | bms.schema.simulation.SimWeaponState | 武器仿真器 | EnhanceUnit, 回放服务 | QOS-STATE |
| bms/simulation/payload/target_truth | bms.schema.simulation.TargetTruth | 真值服务 | SitMgmt, 回放服务, 评估模块 | QOS-REPLAY |
| bms/simulation/payload/weapon_adjudication | bms.schema.simulation.WeaponAdjudication | 真值服务 | BattleCtrl, 回放服务 | QOS-ALERT |

## 3. 关键边界

1. 仿真器优先复用真实接口契约，不形成第二套业务语义。
2. TargetTruth 不得冒充真实融合态势。
3. WeaponAdjudication 不得直接冒充真实战场毁伤确认。
4. EnhanceUnit 是仿真状态进入核心系统前的适配边界之一。

## 4. 工程收敛

### 4.1 ScenarioControlCommand

ScenarioControlCommand 已收敛为枚举控制动作：

1. START。
2. PAUSE。
3. STOP。

### 4.2 WeaponAdjudication

WeaponAdjudication 已收敛为标准裁决结果枚举：

1. MISS。
2. SUPPRESSION。
3. DAMAGE。
4. DESTROY。

## 5. 时钟与时间原则

1. ClockTick 用于推进仿真时间，不等同于真实时间同步命令。
2. 仿真时间与真实 UTC 时间可以共存，必须通过 CommonHeader 与 sim_time_utc_ms 区分。

## 6. 下一阶段建议

1. 如需更细，可继续补场景暂停原因、重置语义与裁决证据引用。
2. 如需更细，可为 TargetTruth 补充目标阵营、机动特征等真值字段，但必须保持与实测态势对象分离。
