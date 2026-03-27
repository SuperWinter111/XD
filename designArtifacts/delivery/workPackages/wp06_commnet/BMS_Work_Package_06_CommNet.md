# BMS 工作包 06 CommNet

本文档是通信组网分系统的可执行工作包，供软件工程师或 agent 直接领取并进入实现。

## 1. 基本信息

1. 分系统名称：CommNet。
2. 负责人类型：软件工程师或 agent。
3. 对应 Container：plantumlC4/C4_L2_Container.puml 中通信组网分系统。
4. 对应 Component 图：plantumlC4/C4_L3_Component_10_CommNet.puml。
5. 对应 Code 图：plantumlC4/Code_08_CommNet.puml。
6. 对应正式 ICD：BMS_ICD_Formal_07。

## 2. 目标范围

1. 接收平台侧链路遥测与网络安全输入，形成统一链路质量与安全事件对象。
2. 生成 LinkQualitySnapshot、DegradationAlert、SecurityEvent 等通信权威对象。
3. 向 ResMgmt、BattleCtrl 和 MonitorLog 提供链路质量、降级和安全态势输入。
4. 对多链路、多节点拓扑变化形成可追踪的组网视图。
5. 保持通信承载职责与消息治理职责清晰分离。

不包含：

1. 业务消息投递与死信治理。
2. 资源裁定本体实现。
3. 平台业务命令生成。

## 3. 对象边界

### 3.1 主拥有对象

1. LinkQualitySnapshot。
2. DegradationAlert。
3. SecurityEvent。
4. CommTopologySnapshot。

### 3.2 只读消费对象

1. edge.platform/telemetry/link_state 原始遥测。
2. edge.raw.* 网络侧原始事件。
3. 平台节点注册与身份信息。

### 3.3 禁止越权修改

1. 不得代替 MsgService 输出 DeliveryReceipt 或 DeadLetterRecord。
2. 不得把 DegradationAlert 当成持续资源状态对象。
3. 不得直接裁定 AllocationDecision 或改写 BattlePlan。
4. 不得把安全事件直接解释成业务处理结果。

## 4. topic 责任

### 4.1 发布 topic

| topic | payload | 触发条件 | 下游 |
| --- | --- | --- | --- |
| bms/core/ops/comm/link_quality | LinkQualitySnapshot | 链路遥测更新或周期评估 | ResMgmt, BattleCtrl, MonitorLog |
| bms/core/ops/comm/link_degraded | DegradationAlert | 链路质量跌破阈值或拓扑不可达 | ResMgmt, BattleCtrl, MonitorLog |
| bms/core/ops/comm/security_event | SecurityEvent | 认证失败、干扰、入侵等安全事件触发 | MonitorLog, AuthAudit |
| bms/core/ops/comm/topology_changed | CommTopologySnapshot | 节点或路径拓扑发生变化 | MonitorLog, OpsMgmt |

### 4.2 订阅 topic

| topic | payload | 上游 | 消费动作 |
| --- | --- | --- | --- |
| edge.platform/telemetry/link_state | 原始链路遥测 | 平台与网络设备 | 计算链路质量 |
| edge.raw.* | 原始网络事件 | 网络设备 | 提取异常与安全信号 |
| bms/edge/platform/event/platform_registered | ResourceRegistration | EnhanceUnit | 建立节点拓扑视图 |

## 5. 模块拆分

| 模块 | 责任 | 输入 | 输出 |
| --- | --- | --- | --- |
| LinkTelemetryCollector | 接收链路遥测与网络原始输入 | link_state, edge.raw.* | 标准化链路观测 |
| QualityScoringService | 计算链路质量评分 | 标准化链路观测 | LinkQualitySnapshot |
| DegradationPolicyEngine | 识别降级与不可达场景 | LinkQualitySnapshot | DegradationAlert |
| SecurityEventBridge | 提取安全事件与攻击线索 | edge.raw.* | SecurityEvent |
| TopologyViewService | 维护网络拓扑变化视图 | ResourceRegistration, 链路观测 | CommTopologySnapshot |

## 6. 实施步骤

1. 先接入 link_state 遥测，形成 LinkQualitySnapshot 主链。
2. 接入降级判定逻辑，输出 link_degraded。
3. 补齐安全事件归一与上报。
4. 接入节点注册信息，形成拓扑变化视图。
5. 最后与 ResMgmt、BattleCtrl、MonitorLog 完成联合验收。

## 7. 测试与验收

### 7.1 必备样例

1. 正常样例：link_quality 正常发布。
2. 异常样例：link_degraded 或 security_event 触发。
3. 边界样例：DegradationAlert 是事件，不等于持续状态对象。

### 7.2 契约测试

1. LinkQualitySnapshot、DegradationAlert、SecurityEvent 必须符合 Formal 07。
2. 安全事件与链路质量对象语义不得混用。
3. 拓扑变化输出必须能追溯到具体节点或链路变化来源。
4. 不得出现以通信层事件替代消息治理结果的情况。

### 7.3 完成定义

1. Code_08_CommNet 的主模块已形成实现骨架。
2. link_quality 与 link_degraded 两条主链可验证。
3. 与 ResMgmt、BattleCtrl、MonitorLog 的联调项已映射到联调矩阵。
4. 已准备主业务闭环场景 C 所需链路样例。

## 8. 风险与待决项

1. 风险：网络遥测来源多样时，统一质量评分口径会变复杂。
2. 风险：安全事件与链路故障交织时，容易导致下游误判根因。
3. 待决项：topology_changed 的最小对象粒度是否需要追加专项样例。
