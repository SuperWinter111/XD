# WP02 TaskMgmt 实现工程

本目录是 wp02_taskmgmt 的独立实现工程。

## 1. 对应设计输入

1. ../../designArtifacts/delivery/workPackages/wp02_taskmgmt/BMS_Work_Package_02_TaskMgmt.md
2. ../../designArtifacts/delivery/workPackages/wp02_taskmgmt/ICD_Package.md
3. ../../designArtifacts/delivery/workPackages/wp02_taskmgmt/Payload_Checklist.md
4. ../../designArtifacts/delivery/workPackages/wp02_taskmgmt/AGENT_HANDOFF.md

## 2. 当前工程范围

1. MissionCommand、TaskConstraint、TaskPackage、AllocationRequest、TaskReconstructionDecision 首版工程对象。
2. CommandNormalizer、TaskDecomposer、ResourceRequestCoordinator、TaskPackageBuilder。
3. TaskReconstructionService 与 TaskLifecycleTracker。
4. TaskMgmtApplicationService 主链编排层，以及 command_ack、mission_progress、effect_report 生命周期消费。
5. 外部入口 DTO、CommandMapper、CommandHandler。
6. Response DTO 与 ResponseMapper。
7. command_received、decomposed、allocation_requested、plan_created、task_reconstruction、反馈闭环测试。

## 3. 当前实现原则

1. TaskMgmt 不越权直接生成 BattlePlan。
2. AllocationRequest 只表达请求，不表达裁定结果。
3. TaskPackage 保持任务层输入语义，不携带平台执行动作细节。
4. 任务级重构仅在越出任务边界时触发。

## 4. 当前测试覆盖

1. 主链：MissionCommand -> TaskConstraint -> AllocationRequest -> TaskPackage。
2. 异常：越出任务边界时输出 task reconstruction 决策。
3. 边界：无效任务请求拒绝进入主链。
4. 生命周期：command_received、decomposed、allocation_requested、allocation_resolved、plan_created、command_acknowledged、mission_progress_updated、effect_reported、reconstruction_required 记录。
