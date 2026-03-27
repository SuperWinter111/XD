# BMS 正式 ICD 专题 02 任务计划执行闭环

本文档是面向任务、计划、执行、异常回退主链的正式 ICD 专题文档。

本文档覆盖的闭环范围包括：

1. 任务指令入域。
2. 任务约束与任务包形成。
3. 交战计划生成与更新。
4. 执行状态回传。
5. 执行异常上报。
6. 计划内调整与任务级重构的分界。

## 1. 文档定位

本文档与其它设计文档的关系如下：

1. 需求来源：sysFunctionalRequirements/sysFunctionalRequirements.md。
2. 动态语义来源：plantumlC4/C4_Dynamic_01_CommandChain.puml、plantumlC4/C4_Dynamic_03_KillChain.puml、plantumlC4/C4_Dynamic_04_ReplanRecovery.puml。
3. 语义基线来源：designArtifacts/contracts/BMS_Task_Plan_And_Exception_Semantics.md。
4. DDS 绑定来源：designArtifacts/contracts/BMS_DDS_Topic_Catalog.md。
5. schema 来源：proto/bms/schema/task.proto、proto/bms/schema/battle.proto、proto/bms/schema/execution.proto。
6. 工程交付映射：designArtifacts/delivery/BMS_Subsystem_Design_Traceability_Matrix.md。

本文档在字段样板基础上重点补充：

1. topic 绑定与角色职责。
2. 任务与计划语义边界。
3. 闭环时序。
4. 计划级调整与任务级重构的分界规则。
5. 异常回退与人工介入原则。

## 2. 闭环范围

### 2.1 任务与计划接口

1. bms/core/command/task/command_received
2. bms/core/command/task/decomposed
3. bms/core/command/task/plan_created
4. bms/core/command/task/plan_confirmed
5. bms/core/command/battle/plan_created
6. bms/core/command/battle/plan_updated

### 2.2 执行与效果接口

1. bms/core/execution/state_snapshot
2. bms/core/execution/exception
3. bms/core/command/battle/effect_report

### 2.3 资源协同接口

1. bms/core/command/resource/allocation_requested
2. bms/core/command/resource/allocation_committed

## 3. 角色与职责

### 3.1 任务管理分系统

负责：

1. 接收 MissionCommand。
2. 识别任务类型。
3. 形成 TaskConstraint。
4. 生成或确认 TaskPackage。
5. 在计划无法满足任务约束时执行任务重构。

### 3.2 交战管控分系统

负责：

1. 接收 TaskPackage。
2. 生成 BattlePlan。
3. 在任务约束内执行计划级调整。
4. 消费执行状态与执行异常。
5. 输出计划更新与效果评估。

### 3.3 资源管理分系统

负责：

1. 接收资源申请。
2. 输出 AllocationDecision。
3. 作为资源主拥有者提供分配与预留裁定。

### 3.4 协同增强单元

负责：

1. 执行 BattlePlan 转换后的平台动作。
2. 输出 ExecutionStateSnapshot 对应的边缘执行态信号来源。
3. 在边缘异常触发时向核心业务侧提供异常输入来源。

## 4. payload 绑定

| topic | payload | 发布方 | 订阅方 |
| --- | --- | --- | --- |
| bms/core/command/task/command_received | bms.schema.task.MissionCommand | ExtInterface 或 HMI-BFF | TaskMgmt |
| bms/core/command/task/decomposed | bms.schema.task.TaskConstraint | TaskMgmt | BattleCtrl, ResMgmt |
| bms/core/command/task/plan_created | bms.schema.task.TaskPackage | TaskMgmt | HMI-BFF, BattleCtrl |
| bms/core/command/task/plan_confirmed | bms.schema.task.TaskPackage 或确认事件封装 | HMI-BFF | TaskMgmt, BattleCtrl |
| bms/core/command/battle/plan_created | bms.schema.battle.BattlePlan | BattleCtrl | EnhanceUnit, HMI-BFF |
| bms/core/command/battle/plan_updated | bms.schema.battle.BattlePlan | BattleCtrl | EnhanceUnit, HMI-BFF |
| bms/core/command/resource/allocation_requested | 资源申请对象或请求封装 | TaskMgmt 或 BattleCtrl | ResMgmt |
| bms/core/command/resource/allocation_committed | bms.schema.resource.AllocationDecision | ResMgmt | TaskMgmt, BattleCtrl |
| bms/core/execution/state_snapshot | bms.schema.execution.ExecutionStateSnapshot | EnhanceUnit 或 BattleCtrl | BattleCtrl, TaskMgmt, HMI |
| bms/core/execution/exception | bms.schema.execution.ExecutionException | EnhanceUnit 或 BattleCtrl | BattleCtrl, TaskMgmt |
| bms/core/command/battle/effect_report | 效果评估对象 | BattleCtrl | TaskMgmt, HMI-BFF |

注：

1. 当前 schema 仓已覆盖 MissionCommand、TaskConstraint、TaskPackage、BattlePlan、ExecutionStateSnapshot、ExecutionException、AllocationRequest、AllocationDecision。
2. effect_report 的最终 message 仍可在下一阶段继续工程化专题中补齐。

## 5. 主闭环时序

### 5.1 任务入域

1. 上级系统或 HMI 形成 MissionCommand。
2. TaskMgmt 接收原始任务指令。
3. TaskMgmt 完成任务识别、分解与约束建模。

### 5.2 任务到计划

1. TaskMgmt 形成 TaskConstraint。
2. 若需要资源前提判断，TaskMgmt 与 ResMgmt 协同完成资源匹配。
3. TaskMgmt 输出 TaskPackage 作为 BattleCtrl 的正式输入。
4. BattleCtrl 将任务语义转化为 BattlePlan。

### 5.3 计划到执行

1. BattleCtrl 发布 BattlePlan。
2. EnhanceUnit 接收计划并映射到平台侧执行动作。
3. 执行过程中持续回传 ExecutionStateSnapshot。

### 5.4 执行到异常与回退

1. 若执行链异常但仍在任务约束内，则 BattleCtrl 优先尝试计划级调整。
2. 若异常已超出任务约束，则 BattleCtrl 回退 TaskMgmt 发起任务重构。
3. 人工可在任务层、计划层、执行层任意节点介入。

## 6. 关键语义边界

### 6.1 MissionCommand

语义：

1. 原始任务文书或原始任务指令。
2. 关注“要做什么”。

禁止：

1. 直接传给 EnhanceUnit 作为平台执行命令。
2. 直接被 BattleCtrl 当作计划输入而不经过 TaskMgmt 归一。

### 6.2 TaskConstraint

语义：

1. 任务约束权威对象。
2. 关注任务目标、时间窗、MOE、资源前提、覆盖约束。

禁止：

1. BattleCtrl 修改后仍将其视为原始 TaskConstraint。

### 6.3 TaskPackage

语义：

1. 任务层对计划层的唯一正式输入对象。
2. 表达经确认的任务方案与约束组合。

禁止：

1. HMI 绕过 TaskMgmt 直接构造 TaskPackage。

### 6.4 BattlePlan

语义：

1. 计划层对执行层的唯一正式输入对象。
2. 关注“怎么做、由谁做、按什么参数做”。

禁止：

1. BattlePlan 反向覆盖任务语义。

### 6.5 ExecutionStateSnapshot

语义：

1. 执行态快照。
2. 只表达执行进度，不表达异常归因结论。

### 6.6 ExecutionException

语义：

1. 执行链上的异常事件。
2. 用于触发计划级调整或任务级重构判断。

禁止：

1. 将 ExecutionException 直接视为任务失败终局结论。

## 7. 计划级调整与任务级重构判据

### 7.1 计划级调整

满足以下条件时，优先做计划级调整：

1. in_task_constraint = true。
2. 现有任务目标与时间窗仍可满足。
3. BattleCtrl 在当前任务约束内可重算可执行计划。

典型场景：

1. 局部航路重规划。
2. 编队成员替换但任务目标不变。
3. 传感器模式调整。

### 7.2 任务级重构

满足以下条件时，必须回退 TaskMgmt：

1. in_task_constraint = false。
2. 计划调整后仍无法满足 MOE、时间窗或覆盖目标。
3. 资源条件已根本变化。

典型场景：

1. 关键平台失联。
2. 任务时窗无法满足。
3. 目标区域覆盖要求无法满足。
4. 任务资源前提被破坏。

## 8. 资源协同规则

1. TaskMgmt 可基于任务分解提出资源前提。
2. BattleCtrl 可基于计划生成提出资源申请。
3. ResMgmt 是 AllocationDecision 的唯一主拥有者。
4. TaskMgmt 与 BattleCtrl 都不得自行确认资源裁定结果。

## 9. QoS 与触发方式建议

| 接口 | QoS | 触发方式 | 备注 |
| --- | --- | --- | --- |
| command_received | QOS-CMD | 事件触发 | 原始任务入域 |
| task/decomposed | QOS-PLAN | 事件触发 | 任务分解输出 |
| task/plan_created | QOS-PLAN | 事件触发 | 候选或确认任务包 |
| task/plan_confirmed | QOS-CMD | 事件触发 | 人工确认 |
| battle/plan_created | QOS-PLAN | 事件触发 | 初始交战计划 |
| battle/plan_updated | QOS-PLAN | 事件触发 | 计划调整 |
| allocation_requested | QOS-CMD | 事件触发 | 资源申请 |
| allocation_committed | QOS-PLAN | 事件触发 | 资源分配结果 |
| execution/state_snapshot | QOS-STATE | 周期或关键变化触发 | 执行进度状态 |
| execution/exception | QOS-EVENT | 事件触发 | 执行异常 |
| battle/effect_report | QOS-ALERT | 事件触发 | 效果评估 |

## 10. 人工介入原则

人工介入必须保留在以下层次：

1. MissionCommand 录入或修改。
2. TaskPackage 确认。
3. BattlePlan 调整或批准。
4. 异常处置与任务重构选择。

自动策略可以替代操作流程，但不得抹掉这些语义层的介入口。

## 11. 当前正式 ICD 仍待补充的内容

本专题仍有以下内容适合在下一轮继续深化：

1. command_source 标准枚举或码表。
2. MOE 指标标准对象化。
3. effect_report 的正式 payload 定义。
4. 资源申请对象的正式 payload 定义。
5. ExecutionException.reason 的标准错误码表。

## 12. 建议的下一份正式 ICD 专题

建议下一份继续补：

1. 态势与威胁专题。
2. 资源调度专题。
