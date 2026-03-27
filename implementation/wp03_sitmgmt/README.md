# WP03 SitMgmt 实现工程

本目录是 wp03_sitmgmt 的独立实现工程。

## 1. 对应设计输入

1. ../../designArtifacts/delivery/workPackages/wp03_sitmgmt/BMS_Work_Package_03_SitMgmt.md
2. ../../designArtifacts/delivery/workPackages/wp03_sitmgmt/Payload_Checklist.md
3. ../../designArtifacts/delivery/workPackages/wp03_sitmgmt/TODO.md
4. ../../designArtifacts/delivery/workPackages/wp03_sitmgmt/STATUS.md

## 2. 当前工程范围

1. RawTargetInput 归一为 StandardizedObservation。
2. StandardizedObservation 关联并融合为 FusedTrack。
3. FusedTrack 结合 RecommendationItem 形成 ThreatAssessment。
4. ThreatAssessment 与 FusedTrack 汇总为 SituationSnapshot、SituationSummaryReport、CriticalAlert。
5. TargetTruth 仅作为辅助引用，不替代真实融合结果。

## 3. 当前实现原则

1. SitMgmt 只输出权威态势对象，不越权改写任务和计划对象。
2. RecommendationItem 只作为 ThreatAssessment 的辅助 reason 输入。
3. TargetTruth 以 simulation_truth_ref 方式入链，不冒充 FusedTrack。