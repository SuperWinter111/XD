# WP01 BattleCtrl 实现工程

本目录是 wp01_battlectrl 的独立实现工程。

## 1. 对应设计输入

1. ../../designArtifacts/delivery/workPackages/wp01_battlectrl/BMS_Work_Package_01_BattleCtrl.md
2. ../../designArtifacts/delivery/workPackages/wp01_battlectrl/Payload_Checklist.md
3. ../../designArtifacts/delivery/workPackages/wp01_battlectrl/TODO.md
4. ../../designArtifacts/delivery/workPackages/wp01_battlectrl/STATUS.md

## 2. 当前工程范围

1. TaskConstraint 和 TaskPackage 适配为交战输入上下文。
2. AllocationDecision 与 ThreatAssessment 驱动 BattlePlan 生成。
3. PlatformAlert、MissionProgress、DegradationAlert 驱动 plan_updated 或任务回退判定。
4. MissionProgress 与 ThreatAssessment 汇总为 EngagementEffectReport。
5. ThreatAssessment 与交战上下文生成 InferenceRequest。

## 3. 当前实现原则

1. BattleCtrl 只读消费 TaskPackage、AllocationDecision、ThreatAssessment。
2. CommandAck 不表示任务完成，effect_report 仍由 BattleCtrl 单独判定。
3. 越出任务约束时不继续 plan_updated，而是输出回退判定。