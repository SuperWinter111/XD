# WP06 CommNet ICD 设计包

## 1. 适用小组

1. 通信组网实现小组。
2. 负责链路质量、降级告警、安全事件和拓扑变化的工程师或 agent。

## 2. 主工作包入口

1. [BMS_Work_Package_06_CommNet.md](BMS_Work_Package_06_CommNet.md)

## 3. 必读 Formal ICD

1. [BMS_ICD_Formal_07_Comm_Link_And_Security.md](../../../icd/BMS_ICD_Formal_07_Comm_Link_And_Security.md)

## 4. 必读补充设计文档

1. [BMS_MsgService_vs_CommNet_Responsibility_Matrix.md](../../BMS_MsgService_vs_CommNet_Responsibility_Matrix.md)
2. [BMS_Integration_Matrix.md](../../BMS_Integration_Matrix.md)
3. [BMS_Execution_Index.md](../../BMS_Execution_Index.md)

## 5. 本组重点确认项

1. LinkQualitySnapshot、DegradationAlert、SecurityEvent 的语义边界。
2. 通信承载与消息治理职责分离。
3. topology_changed、link_quality 与 security_event 的触发条件。

## 6. 交付前核对清单

1. link_quality、link_degraded、security_event 样例已准备。
2. 与 MsgService 的职责边界已核对。
3. 对 ResMgmt、BattleCtrl、MonitorLog 的下游影响已确认。

## 7. 重点 topic 清单

1. 发布：bms/core/ops/comm/link_quality。
2. 发布：bms/core/ops/comm/link_degraded。
3. 发布：bms/core/ops/comm/security_event。
4. 发布：bms/core/ops/comm/topology_changed。
5. 订阅：edge.platform/telemetry/link_state。
6. 订阅：edge.raw.*。

## 8. 重点 payload 清单

1. LinkQualitySnapshot。
2. DegradationAlert。
3. SecurityEvent。
4. CommTopologySnapshot。

## 9. 样例与测试入口

1. [Formal 07 样例基线](../../BMS_Contract_Test_Baseline.md)
2. [MsgService 与 CommNet 职责对照](../../BMS_MsgService_vs_CommNet_Responsibility_Matrix.md)

## 10. 小组签收清单

1. 已签收链路质量、降级和安全事件边界。
2. 已签收与 MsgService 的职责分离规则。
3. 已确认 topology_changed 的使用口径。

## 11. 字段级核对表

1. [Payload_Checklist.md](Payload_Checklist.md)
