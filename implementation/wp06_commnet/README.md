# WP06 CommNet 实现工程

本目录是 wp06_commnet 的独立实现工程。

## 1. 对应设计输入

1. ../../designArtifacts/delivery/workPackages/wp06_commnet/BMS_Work_Package_06_CommNet.md
2. ../../designArtifacts/delivery/workPackages/wp06_commnet/Payload_Checklist.md
3. ../../designArtifacts/delivery/workPackages/wp06_commnet/TODO.md
4. ../../designArtifacts/delivery/workPackages/wp06_commnet/STATUS.md

## 2. 当前工程范围

1. link_state 遥测标准化为 LinkObservation。
2. LinkObservation 评分为 LinkQualitySnapshot。
3. 链路评分低于阈值时输出 DegradationAlert。
4. 原始安全信号标准化为 SecurityEvent。
5. 平台注册和链路观测刷新为 CommTopologySnapshot。

## 3. 当前实现原则

1. CommNet 只输出通信权威对象，不替代 MsgService 的投递治理对象。
2. DegradationAlert 是事件，不表示持续资源状态。
3. SecurityEvent 保持通信安全语义，不直接解释为业务结果。