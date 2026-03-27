# BMS 工作包 02 TaskMgmt

本文档是任务管理分系统的可执行工作包，供软件工程师或 agent 直接领取并进入实现。

## 1. 基本信息

1. 分系统名称：TaskMgmt。
2. 负责人类型：软件工程师或 agent。
3. 对应 Container：plantumlC4/C4_L2_Container.puml 中任务管理分系统。
4. 对应 Component 图：plantumlC4/C4_L3_Component_03_TaskMgmt.puml。
5. 对应 Code 图：plantumlC4/Code_02_TaskMgmt.puml。
6. 对应正式 ICD：BMS_ICD_Formal_02、03、06。

## 2. 目标范围

1. 接收外部任务指令并规范化为 MissionCommand 入域对象。
2. 分解任务目标、时窗、约束和依赖关系，形成 TaskConstraint 与 TaskPackage。
3. 向 ResMgmt 发起 AllocationRequest，并基于裁定结果维护任务生命周期。
4. 在越出任务边界的异常场景中发起任务级重构，而不是伪装成计划级调整。
5. 向 BattleCtrl 输出稳定的任务层权威对象，不越权生成 BattlePlan。

不包含：

1. 交战计划生成与平台命令翻译。
2. 资源裁定本体实现。
3. 威胁评估与态势融合算法实现。

## 3. 对象边界

### 3.1 主拥有对象

1. MissionCommand。
2. TaskConstraint。
3. TaskPackage。
4. TaskReconstructionDecision。

### 3.2 只读消费对象

1. AllocationDecision。
2. MissionProgress。
3. CommandAck。
4. EngagementEffectReport。
5. RecommendationItem。

### 3.3 禁止越权修改

1. 不得直接生成或改写 BattlePlan。
2. 不得替代 ResMgmt 做 AllocationDecision。
3. 不得把 RecommendationItem 当成任务权威结论直接落盘。
4. 不得用任务重构掩盖平台层受理失败等计划内异常。

## 4. topic 责任

### 4.1 发布 topic

| topic | payload | 触发条件 | 下游 |
| --- | --- | --- | --- |
| bms/core/command/task/command_received | MissionCommand | 外部任务指令入域完成 | TaskMgmt 内部流程, MonitorLog |
| bms/core/command/task/decomposed | TaskConstraint | 任务拆解与约束计算完成 | BattleCtrl |
| bms/core/command/task/plan_created | TaskPackage | 任务包已形成并可进入计划层 | BattleCtrl |
| bms/core/command/resource/allocation_requested | AllocationRequest | 任务需要资源裁定 | ResMgmt |

### 4.2 订阅 topic

| topic | payload | 上游 | 消费动作 |
| --- | --- | --- | --- |
| ext.command.* | MissionCommand 或外部任务对象 | 外部接口管理 | 完成指令归一与任务入域 |
| bms/core/command/resource/allocation_committed | AllocationDecision | ResMgmt | 判断是否可继续推进任务 |
| bms/edge/platform/event/mission_progress | MissionProgress | EnhanceUnit | 更新任务执行状态 |
| bms/edge/platform/event/command_ack | CommandAck | EnhanceUnit | 识别平台受理异常 |
| bms/core/command/battle/effect_report | EngagementEffectReport | BattleCtrl | 更新任务效果与结案结论 |
| bms/core/knowledge/inference/recommended | RecommendationItem | KnowledgeRule | 作为任务辅助决策输入 |

## 5. 模块拆分

| 模块 | 责任 | 输入 | 输出 |
| --- | --- | --- | --- |
| CommandNormalizer | 归一外部任务指令 | ext.command.* | MissionCommand |
| TaskDecomposer | 分解任务目标与约束 | MissionCommand | TaskConstraint |
| TaskPackageBuilder | 生成计划层输入对象 | TaskConstraint | TaskPackage |
| ResourceRequestCoordinator | 组织资源申请与回填 | TaskPackage | AllocationRequest, 任务资源上下文 |
| TaskReconstructionService | 在越界异常时发起任务级重构 | AllocationDecision, EngagementEffectReport | TaskReconstructionDecision |
| TaskLifecycleTracker | 跟踪任务状态与 trace_id | 全链路事件 | 生命周期状态 |

## 6. 实施步骤

1. 先打通 MissionCommand 入域与 command_received 主链。
2. 实现 TaskDecomposer 和 TaskPackageBuilder，输出 TaskConstraint 与 TaskPackage。
3. 接入 AllocationRequest 和 AllocationDecision，完成资源请求闭环。
4. 接入 mission_progress、command_ack 与 effect_report，完善任务生命周期状态机。
5. 最后补齐 TaskReconstructionService，完成任务级重构路径。

## 7. 测试与验收

### 7.1 必备样例

1. 正常样例：MissionCommand -> TaskConstraint -> TaskPackage -> AllocationRequest。
2. 异常样例：资源裁定失败或执行越界异常触发任务重构。
3. 边界样例：TaskMgmt 不越权直接生成 BattlePlan。

### 7.2 契约测试

1. TaskConstraint 与 TaskPackage 的字段语义必须符合 Formal 02。
2. AllocationRequest 只是申请，不得冒充 AllocationDecision，必须符合 Formal 03。
3. RecommendationItem 只能作为辅助输入，不得替代任务权威对象。
4. trace_id 必须贯穿 command_received、decomposed、plan_created 和重构输出。

### 7.3 完成定义

1. Code_02_TaskMgmt 的主模块已形成实现骨架。
2. TaskPackage 与 AllocationRequest 两条主链可独立验证。
3. 与 BattleCtrl、ResMgmt 的主要联调项已映射到联调矩阵。
4. 已准备主业务闭环场景 A、B、D 所需样例和验收记录。

## 8. 风险与待决项

1. 风险：外部任务语义过于松散时，CommandNormalizer 容易积累大量兼容逻辑。
2. 风险：任务重构与计划级调整边界若实现不清，会导致 BattleCtrl 与 TaskMgmt 职责串位。
3. 待决项：任务级重构后的 trace_id 继承策略是否需要追加单独规范说明。
