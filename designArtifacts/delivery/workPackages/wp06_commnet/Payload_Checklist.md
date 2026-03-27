# WP06 CommNet Payload 核对表

## 1. 重点 payload

1. LinkQualitySnapshot。
2. DegradationAlert。
3. SecurityEvent。
4. CommTopologySnapshot。

## 2. 字段级核对重点

1. LinkQualitySnapshot：必须有链路标识、质量指标、时间点和评分来源。
2. DegradationAlert：必须明确触发阈值、影响范围和事件时间。
3. SecurityEvent：必须保留事件类型、来源节点、严重级别和审计关联字段。
4. CommTopologySnapshot：必须标识节点、链路关系和变更原因。

## 3. 常见错误

1. 把 DegradationAlert 当成持续状态对象。
2. 在 SecurityEvent 中丢失来源节点或严重级别。
3. 把消息治理字段塞进通信事件对象。
