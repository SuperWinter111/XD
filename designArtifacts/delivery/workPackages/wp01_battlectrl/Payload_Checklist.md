# WP01 BattleCtrl Payload 核对表

## 1. 重点 payload

1. BattlePlan。
2. EngagementEffectReport。
3. TaskConstraint。
4. TaskPackage。
5. AllocationDecision。
6. CommandAck。
7. MissionProgress。

## 2. 字段级核对重点

1. BattlePlan：必须能唯一标识 plan_id、task_id、trace_id、执行对象和关键约束引用。
2. TaskPackage：必须保留任务级边界，不得混入平台执行细节字段。
3. AllocationDecision：必须显式区分 accepted、allocated_resource_ids、reserved_resource_ids 和 arbitration_reason。
4. CommandAck：必须区分受理状态与执行完成状态，不能把 accepted 当完成。
5. MissionProgress：必须带执行阶段、时间点和进度语义，不能只给模糊文本。
6. EngagementEffectReport：必须能回接 task_id、plan_id、trace_id 和效果结论。

## 3. 常见错误

1. 用 BattlePlan 反写 TaskConstraint。
2. 用 CommandAck 表达任务完成。
3. 把 AllocationDecision 当成可修改输入对象。
