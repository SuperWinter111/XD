# WP03 SitMgmt 工程级 ICD 初版

## 1. 当前阶段

1. 当前版本：v0.2。
2. 当前用途：事实观测、态势融合、威胁评估与摘要输出的模块完成版工程实现约束。
3. 冻结程度：模块完成待审核，可继续联调前置开发。

## 2. 当前冻结项

1. FusedTrack 必须保留 trackId、sources、confidence。
2. ThreatAssessment 必须保留 threatLevel 和 reasons。
3. RecommendationItem 只能作为辅助输入，不替代 ThreatAssessment。
4. TargetTruth 只能作为仿真引用来源，不替代真实态势对象。

## 3. 当前实现映射

1. PerceptionIngestService：RawTargetInput/ExternalObservation/TargetTruth -> StandardizedObservation。
2. TrackAssociationService：StandardizedObservation -> TrackCandidate。
3. AttributeFusionService：TrackCandidate -> FusedTrack。
4. ThreatAssessmentService：FusedTrack + RecommendationItem -> ThreatAssessment。
5. SituationSummaryService：FusedTrack + ThreatAssessment -> SituationSnapshot/SituationSummaryReport/CriticalAlert。

## 4. 当前验证状态

1. fused_track_test：验证 RawTargetInput 到 FusedTrack 主链。
2. threat_test：验证 RecommendationItem 作为辅助输入参与 ThreatAssessment。
3. boundary_test：验证 TargetTruth 与 RecommendationItem 的边界输入语义。
4. summary_test：验证快照、摘要和关键告警输出。