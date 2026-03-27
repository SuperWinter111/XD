# WP06 CommNet 工程级 ICD 初版

## 1. 当前阶段

1. 当前版本：v0.2。
2. 当前用途：链路质量、降级事件、安全事件和拓扑视图的模块完成版工程实现约束。
3. 冻结程度：模块完成待审核，可继续联调前置开发。

## 2. 当前冻结项

1. LinkQualitySnapshot 必须保留 linkId、评分来源和时间点。
2. DegradationAlert 必须保留阈值、影响范围和事件时间。
3. SecurityEvent 必须保留来源节点、严重级别和审计关联字段。
4. CommTopologySnapshot 必须能追溯到节点与链路变化来源。

## 3. 当前实现映射

1. LinkTelemetryCollector：RawLinkTelemetry -> LinkObservation。
2. QualityScoringService：LinkObservation -> LinkQualitySnapshot。
3. DegradationPolicyEngine：LinkQualitySnapshot -> DegradationAlert。
4. SecurityEventBridge：RawSecuritySignal -> SecurityEvent。
5. TopologyViewService：ResourceRegistration + LinkObservation -> CommTopologySnapshot。

## 4. 当前验证状态

1. link_quality_test：验证 LinkQualitySnapshot 正常输出。
2. degradation_test：验证质量评分越阈时产生 DegradationAlert。
3. security_test：验证 RawSecuritySignal 到 SecurityEvent 的归一映射。
4. topology_test：验证平台注册与链路观测驱动的拓扑变化输出。