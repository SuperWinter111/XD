# WP05 EnhanceUnit Payload 核对表

## 1. 重点 payload

1. BattlePlan。
2. PlatformCommand。
3. CommandAck。
4. MissionProgress。
5. PlatformAlert。
6. ResourceRegistration。
7. RawTargetInput。

## 2. 字段级核对重点

1. PlatformCommand：必须保留命令类型、目标平台、参数和 trace_id。
2. CommandAck：必须表达命令受理结果、拒绝原因和关联命令标识。
3. MissionProgress：必须表达阶段、进度值和时间点。
4. PlatformAlert：必须区分平台异常和执行进度反馈。
5. ResourceRegistration：必须保留平台注册标识和能力来源。
6. RawTargetInput：必须标明来源传感器和原始上报时间。

## 3. 常见错误

1. 用 CommandAck 代表最终任务执行结果。
2. 用 RawTargetInput 冒充 SitMgmt 权威态势输出。
3. 在 PlatformCommand 中混入任务层语义字段。
