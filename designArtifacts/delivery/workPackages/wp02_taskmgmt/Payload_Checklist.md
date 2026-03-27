# WP02 TaskMgmt Payload 核对表

## 1. 重点 payload

1. MissionCommand。
2. TaskConstraint。
3. TaskPackage。
4. AllocationRequest。
5. AllocationDecision。

## 2. 字段级核对重点

1. MissionCommand：必须包含来源、任务目标、时窗和 trace_id。
2. TaskConstraint：必须保留任务边界、约束条件和重构判断所需字段。
3. TaskPackage：必须是计划层输入对象，不得直接携带平台执行动作细节。
4. AllocationRequest：必须表达请求，不得带 accepted 一类裁定结果字段。
5. AllocationDecision：只读消费，字段必须用于状态判断而非再裁定。

## 3. 常见错误

1. 在 TaskPackage 中混入 BattlePlan 字段。
2. 在 AllocationRequest 中预置裁定结果。
3. 重构路径丢失 trace_id 继承关系。
