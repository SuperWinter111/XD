# WP10 MonitorLog Payload 核对表

## 1. 重点 payload

1. MonitorMetric。
2. MonitorAlert。
3. LogDigest。
4. TraceCorrelationRecord。
5. DeliveryReceipt。
6. SecurityEvent。
7. ReleaseEvent。

## 2. 字段级核对重点

1. MonitorMetric：必须明确指标名、指标值、时间点和来源域。
2. MonitorAlert：必须明确告警等级、触发条件、时间点和影响范围。
3. LogDigest：必须保留原始日志来源和聚合摘要范围。
4. TraceCorrelationRecord：必须能串联多域 trace_id 与关键事件节点。
5. DeliveryReceipt、SecurityEvent、ReleaseEvent：接入监控时必须保留原始 owner 来源。

## 3. 常见错误

1. MonitorAlert 没有明确告警等级和触发条件。
2. 监控聚合时丢失原始来源域。
3. TraceCorrelationRecord 只保留单域事件，不能跨域排障。
