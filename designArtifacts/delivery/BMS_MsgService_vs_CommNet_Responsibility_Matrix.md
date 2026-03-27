# BMS MsgService 与 CommNet 职责对照矩阵

本文档用于专门澄清 MsgService 与 CommNet 的职责边界，避免在实现阶段把“消息治理”和“通信承载”混成同一层责任。

## 1. 核心结论

1. MsgService 负责消息治理，不负责链路承载。
2. CommNet 负责通信承载，不负责系统级消息治理。
3. 两者可以协同，但不得互相替代对方的 owner 对象和权威结论。

## 2. owner 对象对照

| 维度 | MsgService | CommNet |
| --- | --- | --- |
| 主对象 | TopicDefinition, EndpointBinding, SchemaDescriptor, MessageEnvelope, SubscriptionBinding, DeliveryReceipt, DeadLetterRecord | LinkSession, LinkProfile, TopologySnapshot, RoutePath, RelayFrame, CommSecurityContext, LinkQualitySnapshot, DegradationAlert, SecurityEvent |
| owner 角色 | 消息治理 owner | 通信语义 owner |
| 禁止替代 | 不替代链路质量、建链、安全事件结论 | 不替代 topic、schema、消息包络、回执、死信治理 |

## 3. 责任边界对照

| 场景 | MsgService 负责什么 | CommNet 负责什么 |
| --- | --- | --- |
| topic 定义 | 主题登记、QoS、发布者/订阅者关系 | 不负责 |
| schema 与包络 | MessageEnvelope、版本兼容、字段映射 | 不负责 |
| 投递治理 | 回执、重试、死信、幂等、顺序、流控 | 不负责 |
| 建链与切换 | 不负责 | 建链、切换、冗余、带宽、路由 |
| 链路质量 | 不负责权威定义 | 负责 LinkQualitySnapshot、DegradationAlert |
| 安全事件 | 只消费必要的系统消息治理告警 | 负责通信层 SecurityEvent |
| 总线协同 | 基于已建立承载做消息治理 | 为中继和承载提供链路能力 |

## 4. 典型误用与纠正

1. 误用：在 CommNet 中定义 TopicDefinition 或私有 topic registry。
   纠正：topic、schema、发布订阅关系统一回到 MsgService。
2. 误用：在 MsgService 中根据链路质量直接定义 DegradationAlert。
   纠正：链路质量和降级事件统一回到 CommNet。
3. 误用：把 DeliveryReceipt 当作网络传输健康状态。
   纠正：DeliveryReceipt 只表达消息投递结果，网络健康由 LinkQualitySnapshot 表达。
4. 误用：把 CommNet 当作通用消息总线实现替代 MsgService。
   纠正：CommNet 只提供承载和转发能力，系统级消息治理仍在 MsgService。

## 5. 联调与测试分工

1. MsgService 的重点样例：topic_defined、delivery_receipt、dead_letter、版本兼容、背压与重试。
2. CommNet 的重点样例：topology_changed、link_quality、link_degraded、security_event、链路切换。
3. 联调时若出现“消息到了但业务没处理”，先看 MsgService 的 DeliveryReceipt 和 DeadLetterRecord。
4. 联调时若出现“链路抖动、时延异常、带宽不足、认证失败”，先看 CommNet 的 LinkQualitySnapshot、DegradationAlert、SecurityEvent。

## 6. 文档映射

1. MsgService 设计依据：[BMS_ICD_Formal_08_Message_Governance_And_Delivery.md](../icd/BMS_ICD_Formal_08_Message_Governance_And_Delivery.md)、[BMS_Work_Package_07_MsgService.md](workPackages/wp07_msgservice/BMS_Work_Package_07_MsgService.md)、[BMS_Owner_Rule_Baseline.md](BMS_Owner_Rule_Baseline.md)。
2. CommNet 设计依据：[BMS_ICD_Formal_07_Comm_Link_And_Security.md](../icd/BMS_ICD_Formal_07_Comm_Link_And_Security.md)、[BMS_Work_Package_06_CommNet.md](workPackages/wp06_commnet/BMS_Work_Package_06_CommNet.md)、[BMS_Owner_Rule_Baseline.md](BMS_Owner_Rule_Baseline.md)。
3. 若需要调整两者边界，必须先走 [BMS_Change_Governance.md](BMS_Change_Governance.md)。
