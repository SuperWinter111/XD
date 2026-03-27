# WP09 AuthAudit Payload 核对表

## 1. 重点 payload

1. AuditEvent。
2. AccessDecisionRecord。
3. SecurityReviewRecord。
4. SecurityEvent。

## 2. 字段级核对重点

1. AuditEvent：必须有操作者、动作、对象、时间点和 trace_id。
2. AccessDecisionRecord：必须有访问请求、决策结果、决策依据和时间点。
3. SecurityReviewRecord：必须能关联原始 SecurityEvent 和审计流程。
4. SecurityEvent：接入审计时必须保留原始来源和原始严重级别。

## 3. 常见错误

1. AuditEvent 缺少操作者或对象标识。
2. AccessDecisionRecord 没有记录决策依据。
3. 审计过程中覆盖原始 SecurityEvent 内容。
