# BMS 正式 ICD 专题 07 通信链路与安全事件

本文档定义 CommNet 对外发布的网络拓扑、链路质量、链路降级与通信安全事件接口约束。

## 1. 文档定位

本文档覆盖以下对象：

1. TopologySnapshot。
2. LinkQualitySnapshot。
3. DegradationAlert。
4. SecurityEvent。

## 2. Topic 绑定

| topic | payload | 发布方 | 订阅方 | QoS |
| --- | --- | --- | --- | --- |
| bms/core/ops/comm/topology_changed | bms.schema.comm.TopologySnapshot | CommNet | MonitorLog | QOS-ALERT |
| bms/core/ops/comm/link_quality | bms.schema.comm.LinkQualitySnapshot | CommNet | MonitorLog, ResMgmt | QOS-STATE |
| bms/core/ops/comm/link_degraded | bms.schema.comm.DegradationAlert | CommNet | MonitorLog, BattleCtrl | QOS-ALERT |
| bms/core/ops/comm/security_event | bms.schema.comm.SecurityEvent | CommNet | AuthAudit, MonitorLog | QOS-ALERT |

## 3. 对象边界

### 3.1 TopologySnapshot

TopologySnapshot 用于表达当前网络拓扑快照，不用于表达作战编组或资源编组。

### 3.2 LinkQualitySnapshot

LinkQualitySnapshot 用于表达链路质量测量值与标准化等级。

### 3.3 DegradationAlert

DegradationAlert 用于表达链路质量降级事件，是事件对象，不是持续状态对象。

### 3.4 SecurityEvent

SecurityEvent 用于表达通信安全事件，不得直接当作任务失败结论。

## 4. 工程约束

1. latency_ms 需要明确为约定统计口径，不能混用 RTT 与单向时延。
2. packet_loss_ratio 必须保持 [0, 1] 归一口径。
3. topology_changed 应只在拓扑版本变化时触发，不应周期滥发。
4. link_degraded 应由 LinkQualitySnapshot 阈值判定结果触发。

## 5. BattleCtrl 与 ResMgmt 消费原则

1. BattleCtrl 可消费 DegradationAlert 与 LinkQualitySnapshot 做执行风险判断。
2. ResMgmt 可消费 LinkQualitySnapshot 做资源健康校核。
3. 两者都不得反向发布权威链路质量结论覆盖 CommNet。

## 6. 下一阶段建议

1. 如需更细化，可为 SecurityEvent 增加证据引用与受影响节点列表。
2. 如需更细化，可为 DegradationAlert 增加阈值来源与恢复判据。
