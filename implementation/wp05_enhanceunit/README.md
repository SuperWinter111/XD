# WP05 EnhanceUnit 实现工程

本目录是 wp05_enhanceunit 的独立实现工程。

## 1. 对应设计输入

1. ../../designArtifacts/delivery/workPackages/wp05_enhanceunit/BMS_Work_Package_05_EnhanceUnit.md
2. ../../designArtifacts/delivery/workPackages/wp05_enhanceunit/ICD_Package.md
3. ../../designArtifacts/delivery/workPackages/wp05_enhanceunit/Payload_Checklist.md
4. ../../designArtifacts/delivery/workPackages/wp05_enhanceunit/AGENT_HANDOFF.md

## 2. 当前工程范围

1. BattlePlan 到 PlatformCommand 的翻译主链。
2. PlatformCommandService 产生 CommandAck。
3. ExecutionFeedbackBridge 产生 MissionProgress 和 PlatformAlert。
4. CapabilityReporter 输出 ResourceRegistration。
5. PerceptionBridge 输出 RawTargetInput。
6. SimulationBridge 输出仿真 MissionProgress。
7. BattlePlan、反馈、注册、仿真四类测试。

## 3. 当前实现原则

1. EnhanceUnit 不越权改写 BattlePlan。
2. CommandAck 仅表示平台受理结果，不表示任务完成。
3. RawTargetInput 只表示边缘原始输入，不表示 SitMgmt 权威结果。
4. 仿真输入与真实平台输入保持语义分离。