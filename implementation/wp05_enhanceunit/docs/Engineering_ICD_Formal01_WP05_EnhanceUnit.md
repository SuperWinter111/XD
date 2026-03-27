# WP05 EnhanceUnit 工程级 ICD 初版

本文档是 wp05_enhanceunit 在工程实现阶段的工程级接口约束。

## 1. 当前阶段

1. 当前版本：v0.2。
2. 当前用途：首版平台命令桥接、执行反馈、能力上报与仿真桥接实现约束。
3. 冻结程度：模块完成待审核，可用于后续联调前置开发。

## 2. 当前冻结项

1. BattlePlan 只读消费，不在本模块内被改写。
2. PlatformCommand 是平台执行层 owner 对象。
3. CommandAck 只表达平台受理结果。
4. RawTargetInput 不冒充 SitMgmt 权威态势对象。
5. 仿真进度与真实平台执行反馈分开建模。

## 3. 当前实现映射

1. CommandTranslator：BattlePlan -> PlatformCommand。
2. PlatformCommandService：PlatformCommand -> CommandAck。
3. ExecutionFeedbackBridge：CommandAck -> MissionProgress 或 PlatformAlert。
4. CapabilityReporter：PlatformState/PayloadState/WeaponState -> ResourceRegistration。
5. PerceptionBridge：传感器原始输入 -> RawTargetInput。
6. SimulationBridge：ClockTick/SimFlightState -> 模拟 MissionProgress。

## 4. 当前验证状态

1. command_chain_test：验证 BattlePlan 到 PlatformCommand/CommandAck 主链。
2. feedback_test：验证 accepted/rejected 反馈分流。
3. registration_test：验证平台注册与原始感知桥接输出。
4. simulation_test：验证仿真飞行状态到 MissionProgress 的映射。