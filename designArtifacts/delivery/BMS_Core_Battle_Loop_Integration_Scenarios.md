# BMS 主业务闭环联调场景基线

本文档用于把 TaskMgmt、SitMgmt、BattleCtrl、ResMgmt 以及 EnhanceUnit 的核心联调路径固化为一组最小可执行场景。软件工程师或 agent 领取工作包后，应优先按本文场景推进联调。

## 1. 适用范围

本文覆盖以下主业务闭环：

1. 任务入域。
2. 任务分解与任务包生成。
3. 资源申请与资源裁定。
4. 交战计划生成与平台执行。
5. 执行进度、异常、降级与任务重构。
6. 态势回馈与效果评估。

## 2. 联调前置条件

1. TaskMgmt、SitMgmt、BattleCtrl、ResMgmt 至少具备各自实例工作包要求的主链实现。
2. EnhanceUnit 至少能 mock 接收平台控制命令，并返回 command_ack、mission_progress、platform_alert。
3. 所有样例必须带 trace_id。
4. topic 名称、payload 名称与正式 ICD 版本必须一致。

## 3. 场景清单

### 场景 A 正常任务闭环

目标：验证从 MissionCommand 到 effect_report 的最短正常闭环。

参与分系统：TaskMgmt、ResMgmt、BattleCtrl、EnhanceUnit。

输入：

1. MissionCommand 正常样例。
2. AllocationDecision.accepted = true 的资源裁定样例。
3. command_ack.accepted = true 的命令受理样例。
4. mission_progress 正常推进样例。

期望 topic 顺序：

1. bms/core/command/task/command_received
2. bms/core/command/task/decomposed
3. bms/core/command/resource/allocation_requested
4. bms/core/command/resource/allocation_committed
5. bms/core/command/task/plan_created
6. bms/core/command/battle/plan_created
7. bms/edge/platform/command/flight_plan_upload 或其它平台命令
8. bms/edge/platform/event/command_ack
9. bms/edge/platform/event/mission_progress
10. bms/core/command/battle/effect_report

验收重点：

1. TaskMgmt 只输出 TaskPackage，不越界输出 BattlePlan。
2. BattleCtrl 只在接到 TaskPackage 后输出 BattlePlan。
3. ResMgmt 的 AllocationDecision 是唯一资源裁定结果。
4. command_ack 只表示受理，不表示完成。

### 场景 B 资源部分满足闭环

目标：验证部分满足和预留场景下，TaskMgmt 与 BattleCtrl 是否正确处理资源边界。

参与分系统：TaskMgmt、ResMgmt、BattleCtrl。

输入：

1. AllocationRequest 含多项 demand。
2. AllocationDecision.accepted = true，但只返回部分 allocated_resource_ids，或仅返回 reserved_resource_ids。

期望行为：

1. ResMgmt 输出带 arbitration_reason 的 AllocationDecision。
2. TaskMgmt 判断任务约束是否仍成立。
3. BattleCtrl 只在约束成立时继续生成或调整 BattlePlan。

验收重点：

1. accepted = true 不等于完全满足。
2. TaskMgmt 与 BattleCtrl 不得自行改写 AllocationDecision。
3. reserve_only 与即时分配场景必须被明确区分。

### 场景 C 计划级调整闭环

目标：验证执行异常仍在任务约束内时，BattleCtrl 进行计划级调整而非任务重构。

参与分系统：BattleCtrl、EnhanceUnit、ResMgmt、CommNet。

输入：

1. mission_progress 执行中样例。
2. platform_alert 或 link_degraded 样例，表示当前路线或链路受限，但仍可在任务约束内调整。
3. 可替换资源或可替代路线样例。

期望 topic 顺序：

1. bms/edge/platform/event/mission_progress
2. bms/edge/platform/event/platform_alert 或 bms/core/ops/comm/link_degraded
3. bms/core/command/resource/allocation_requested
4. bms/core/command/resource/allocation_committed
5. bms/core/command/battle/plan_updated
6. 新一轮平台执行命令下发

验收重点：

1. BattleCtrl 只能在当前 TaskConstraint 仍成立时做 plan_updated。
2. 调整后仍需走 AllocationDecision 校核。
3. platform_alert 与 execution_exception 的职责不能混淆。

### 场景 D 任务级重构闭环

目标：验证异常超出当前任务边界时，回退到 TaskMgmt 发起任务重构。

参与分系统：BattleCtrl、TaskMgmt、ResMgmt、EnhanceUnit。

输入：

1. execution_exception 样例，表示平台失联、任务时窗违约、关键资源彻底不可用等越界异常。
2. 资源裁定失败或 accepted = false 样例。

期望行为：

1. BattleCtrl 不再继续 plan_updated。
2. TaskMgmt 进入 TaskReconstructionService。
3. 重新发布新的 TaskPackage 或给出任务失败结论。

验收重点：

1. 任务级重构与计划级调整边界清晰。
2. BattleCtrl 不得伪装任务重构为计划更新。
3. 新 TaskPackage 的 trace_id 继承与因果链必须可追溯。

### 场景 E 态势驱动交战输入闭环

目标：验证 SitMgmt 的 FusedTrack 与 ThreatAssessment 能稳定进入 BattleCtrl 计划输入。

参与分系统：SitMgmt、BattleCtrl、KnowledgeRule、HMI-BFF。

输入：

1. raw target 或 perception 样例。
2. FusedTrack 正常样例。
3. ThreatAssessment 正常样例。
4. knowledge/inference/recommended 可选辅助样例。

期望行为：

1. SitMgmt 先发布 fused_track，再发布 threat_assessed。
2. BattleCtrl 只把 ThreatAssessment 作为态势输入，不把它当作命令。
3. HMI-BFF 可以看到态势与威胁输出，但不反写主业务对象。

验收重点：

1. FusedTrack 是事实观测对象。
2. ThreatAssessment 是分析判断对象。
3. recommendation 只能作为辅助输入，不得替代权威态势对象。

## 4. 最小样例包要求

每个场景至少应准备：

1. 1 套正常样例。
2. 1 套异常样例。
3. 1 套链路追踪说明，说明 trace_id 如何跨 topic 传递。
4. 1 份验收记录模板，记录每一步是否通过。

## 5. 联调通过定义

1. 所有参与方能按约定 topic 和 payload 互通。
2. 任务、计划、资源、态势四类权威对象边界没有被打破。
3. 正常路径与异常路径都能闭环。
4. 任何回退、重构、降级操作都能追溯到明确事件来源。
