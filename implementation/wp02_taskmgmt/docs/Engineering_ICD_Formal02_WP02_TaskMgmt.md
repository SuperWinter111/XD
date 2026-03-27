# WP02 TaskMgmt 工程级 ICD 初版

本文档是 wp02_taskmgmt 在工程实现阶段的工程级接口约束。

## 1. 当前阶段

1. 当前版本：v1.0。
2. 当前用途：模块完成待审核版的工程实现约束。
3. 冻结程度：可作为后续 ResMgmt、BattleCtrl、EnhanceUnit 联调的任务层实现基线，不视为跨包契约最终冻结版。

## 2. 当前冻结项

1. MissionCommand 是 TaskMgmt 入域权威对象。
2. TaskConstraint 与 TaskPackage 属于任务层权威对象。
3. AllocationRequest 只表达请求，不带 accepted 等裁定字段。
4. TaskMgmt 不发布 BattlePlan。
5. 任务级重构与计划级调整的分界，由 exceeds task boundary 决定。

## 3. 当前实现映射

1. CommandNormalizer 负责 MissionCommand 入域校验。
2. TaskDecomposer 负责 MissionCommand 到 TaskConstraint。
3. ResourceRequestCoordinator 负责 TaskConstraint 到 AllocationRequest。
4. TaskPackageBuilder 仅在 AllocationDecision.accepted=true 时输出 TaskPackage。
5. TaskReconstructionService 负责重构决策，不负责计划级调整。
6. TaskLifecycleTracker 记录主链和反馈阶段。
7. TaskMgmtApplicationService 形成 receive command、commit allocation、handle exception 三条入口主链。
8. command_ack、mission_progress、effect_report 作为只读消费输入进入生命周期追踪。

## 4. 当前验证基线

1. wp02_taskmgmt_main_chain_test：主链输出验证。
2. wp02_taskmgmt_reconstruction_test：任务重构边界验证。
3. wp02_taskmgmt_command_mapper_test：DTO 到命令映射验证。
4. wp02_taskmgmt_command_handler_test：入口和响应验证。
5. wp02_taskmgmt_lifecycle_test：生命周期阶段记录验证。
6. wp02_taskmgmt_feedback_test：执行反馈闭环与状态收敛验证。

## 5. 模块完成判定

当前 wp02 已达到“模块完成，待审核”状态，依据如下：

1. MissionCommand 入域、TaskConstraint 拆解、AllocationRequest 生成与 TaskPackage 生成主链已闭环。
2. AllocationRequest 与 AllocationDecision 的边界已通过类型模型和测试固化。
3. TaskMgmt 不越权生成 BattlePlan 的边界已通过对象建模和测试固化。
4. command_ack、mission_progress、effect_report 已进入任务生命周期消费链。
5. 任务级重构仅在越出任务边界时触发，计划级调整场景不会被误判为重构。
6. 当前工程实现已通过 6/6 测试。

当前仍待后续联调阶段继续细化，但不构成模块审核阻断：

1. 任务级重构后的 trace_id 继承策略是否进一步细分为 parent/new trace。
2. 与 ResMgmt、BattleCtrl 的真实 DTO 或消息适配层事务边界。
3. RecommendationItem 进入任务辅助输入后的更细粒度策略约束。
