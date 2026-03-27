# WP10 MonitorLog 实现工程

本目录是 wp10_monitorlog 的独立实现工程。

1. 当前工程覆盖 metric、alert、log_digest 和 trace_correlation 四条主链。
2. MonitorLog 保持只读监控语义，不回写业务域或审计域对象。