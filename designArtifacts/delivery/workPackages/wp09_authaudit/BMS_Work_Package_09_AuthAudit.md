# BMS 工作包 09 AuthAudit

本文档是权限与安全审计分系统的可执行工作包，供软件工程师或 agent 直接领取并进入实现。

## 1. 基本信息

1. 分系统名称：AuthAudit。
2. 负责人类型：软件工程师或 agent。
3. 对应 Container：plantumlC4/C4_L2_Container.puml 中权限与安全审计分系统。
4. 对应 Component 图：plantumlC4/C4_L3_Component_12_AuthAudit.puml。
5. 对应 Code 图：无独立 code 图，以 Component 图、owner 规则和 Formal 10 为主。
6. 对应正式 ICD：BMS_ICD_Formal_10。

## 2. 目标范围

1. 统一接收用户动作、权限判定和安全相关事件，形成 AuditEvent。
2. 提供可追溯的访问决策记录与审计链，支撑长期运维与安全复核。
3. 将 CommNet 等来源的安全事件纳入审计域，但不替代原始安全事件 owner。
4. 向 MonitorLog 和 OpsMgmt 提供可追溯的审计输入。
5. 保障高风险操作、审批与敏感动作具备明确审计证据。

不包含：

1. 监控告警聚合与指标可视化。
2. 版本发布与回滚执行。
3. 业务对象本体修改。

## 3. 对象边界

### 3.1 主拥有对象

1. AuditEvent。
2. AccessDecisionRecord。
3. SecurityReviewRecord。

### 3.2 只读消费对象

1. SecurityEvent。
2. 用户动作日志。
3. 运维审批与执行动作摘要。

### 3.3 禁止越权修改

1. 不得替代 MonitorLog 发布 MonitorAlert。
2. 不得替代 OpsMgmt 执行运维流程审批。
3. 不得改写原始 SecurityEvent 的事实内容，只能形成审计记录。
4. 不得越权改写业务主域对象。

## 4. topic 责任

### 4.1 发布 topic

| topic | payload | 触发条件 | 下游 |
| --- | --- | --- | --- |
| bms/core/ops/sec/audit_event | AuditEvent | 发生用户动作、权限决策或安全审计事件 | MonitorLog, OpsMgmt |
| bms/core/ops/sec/access_decision | AccessDecisionRecord | 权限校验完成 | OpsMgmt, MonitorLog |

### 4.2 订阅 topic

| topic | payload | 上游 | 消费动作 |
| --- | --- | --- | --- |
| bms/core/ops/comm/security_event | SecurityEvent | CommNet | 将通信安全事件纳入审计链 |
| bms/ui/user_action/* | 用户动作对象 | HMI / BFF | 记录敏感操作与访问行为 |
| bms/core/ops/job_* | 运维作业摘要 | OpsMgmt | 建立运维动作审计记录 |

## 5. 模块拆分

| 模块 | 责任 | 输入 | 输出 |
| --- | --- | --- | --- |
| AccessPolicyEvaluator | 输出权限决策记录 | 用户动作, 访问上下文 | AccessDecisionRecord |
| OperationAuditRecorder | 记录操作审计事件 | 用户动作, 运维动作 | AuditEvent |
| SecurityCorrelationService | 关联安全事件与审计上下文 | SecurityEvent | SecurityReviewRecord |
| AuditQueryService | 支撑审计检索与复核 | AuditEvent, AccessDecisionRecord | 审计查询结果 |

## 6. 实施步骤

1. 先实现操作审计与 access_decision 主链。
2. 接入 SecurityEvent，形成安全审计关联链。
3. 接入 HMI / BFF 用户动作和 OpsMgmt 运维动作摘要。
4. 补齐审计检索与复核支撑能力。
5. 最后与 MonitorLog、OpsMgmt 完成联合验收。

## 7. 测试与验收

### 7.1 必备样例

1. 正常样例：用户动作 -> access_decision -> audit_event。
2. 异常样例：高危操作或安全事件触发加强审计。
3. 边界样例：审计对象不反写业务主域或监控域对象。

### 7.2 契约测试

1. AuditEvent 与 AccessDecisionRecord 必须符合 Formal 10。
2. SecurityEvent 纳入审计时必须保留原始来源与 trace_id。
3. 权限决策与操作审计的时间顺序必须可追溯。
4. 不得把审计事件伪装成监控告警事件。

### 7.3 完成定义

1. 审计主链已形成实现骨架。
2. audit_event 与 access_decision 两条主链可验证。
3. 与 MonitorLog、OpsMgmt 的联调项已映射到联调矩阵。
4. 已准备 Formal 10 的审计样例与验收记录。

## 8. 风险与待决项

1. 风险：高频用户动作若全部入审计主链，可能导致审计数据量快速膨胀。
2. 风险：安全事件来源多样时，审计关联规则容易出现遗漏。
3. 待决项：access_decision 是否需要细分审批前决策与执行前决策两类事件。
