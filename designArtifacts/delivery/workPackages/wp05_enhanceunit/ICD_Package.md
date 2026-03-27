# WP05 EnhanceUnit ICD 设计包

## 1. 适用小组

1. 协同增强单元实现小组。
2. 负责平台命令翻译、执行反馈桥接、平台注册与边缘感知桥接的工程师或 agent。

## 2. 主工作包入口

1. [BMS_Work_Package_05_EnhanceUnit.md](BMS_Work_Package_05_EnhanceUnit.md)

## 3. 必读 Formal ICD

1. [BMS_ICD_Formal_01_Platform_Execution_Chain.md](../../../icd/BMS_ICD_Formal_01_Platform_Execution_Chain.md)
2. [BMS_ICD_Formal_09_Simulation_And_Training_Integration.md](../../../icd/BMS_ICD_Formal_09_Simulation_And_Training_Integration.md)

## 4. 必读补充设计文档

1. [BMS_Integration_Matrix.md](../../BMS_Integration_Matrix.md)
2. [BMS_Core_Battle_Loop_Integration_Scenarios.md](../../BMS_Core_Battle_Loop_Integration_Scenarios.md)
3. [BMS_Execution_Index.md](../../BMS_Execution_Index.md)

## 5. 本组重点确认项

1. BattlePlan 到平台命令的翻译边界。
2. command_ack 与 mission_progress 的反馈语义。
3. 真实平台与仿真平台状态必须分离。
4. 原始感知输入不得冒充 SitMgmt 权威对象。

## 6. 交付前核对清单

1. 平台命令受理与回传样例已准备。
2. 仿真输入与真实平台输入已分开验证。
3. 对 BattleCtrl、SitMgmt、ResMgmt 的上报边界已核对。

## 7. 重点 topic 清单

1. 发布：bms/edge/platform/event/command_ack。
2. 发布：bms/edge/platform/event/mission_progress。
3. 发布：bms/edge/platform/event/platform_alert。
4. 发布：bms/edge/platform/event/platform_registered。
5. 发布：edge.payload/perception/*。
6. 订阅：bms/core/command/battle/plan_created。
7. 订阅：bms/core/command/battle/plan_updated。
8. 订阅：bms/simulation/*。

## 8. 重点 payload 清单

1. BattlePlan。
2. PlatformCommand。
3. CommandAck。
4. MissionProgress。
5. PlatformAlert。
6. ResourceRegistration。
7. RawTargetInput。
8. ClockTick。
9. SimFlightState。

## 9. 样例与测试入口

1. [WP05 测试说明](../../../testAssets/workPackages/wp05_enhanceunit/README.md)
2. [Formal 01 样例目录](../../../testAssets/contract/formal01_platform_execution_chain)
3. [主业务闭环追踪说明](../../../testAssets/integration/core_battle_loop/trace_scenario_a_normal.md)

## 10. 小组签收清单

1. 已签收平台命令翻译边界。
2. 已签收执行反馈和平台注册边界。
3. 已确认仿真输入和真实输入完全分离。

## 11. 字段级核对表

1. [Payload_Checklist.md](Payload_Checklist.md)
