# BMS 工作包 01 BattleCtrl

本文档是交战管控分系统的首个可执行工作包，供软件工程师或 agent 直接领取并进入实现。

## 1. 基本信息

1. 分系统名称：BattleCtrl。
2. 负责人类型：软件工程师或 agent。
3. 对应 Container：plantumlC4/C4_L2_Container.puml 中交战管控分系统。
4. 对应 Component 图：plantumlC4/C4_L3_Component_05_BattleCtrl.puml。
5. 对应 Code 图：plantumlC4/Code_03_BattleCtrl.puml。
6. 对应正式 ICD：BMS_ICD_Formal_01、02、03、04、06、07。

## 2. 目标范围

1. 接收 TaskMgmt 输出的 TaskConstraint 和 TaskPackage，形成平台侧可执行 BattlePlan。
2. 消费态势、资源、链路与执行反馈，持续判断当前计划是否仍满足任务约束。
3. 在任务边界内完成计划级调整，生成 plan_updated 并重新下发平台命令。
4. 在任务边界被打破时停止计划内调整，并回退 TaskMgmt 发起任务重构。
5. 输出执行效果评估结果，为任务闭环和界面展示提供权威交战结果。

不包含：

1. 平台协议适配与末端设备驱动实现。
2. 资源权威裁定与预留策略实现。
3. 态势融合算法本体实现。

## 3. 对象边界

### 3.1 主拥有对象

1. BattlePlan。
2. EngagementConstraint。
3. PlanAdjustmentDecision。
4. EngagementEffectReport。

### 3.2 只读消费对象

1. TaskConstraint。
2. TaskPackage。
3. AllocationDecision。
4. ResourceStateSnapshot。
5. FusedTrack。
6. ThreatAssessment。
7. MissionProgress。
8. CommandAck。
9. PlatformAlert。
10. DegradationAlert。

### 3.3 禁止越权修改

1. 不得改写 TaskMgmt 提交的 TaskConstraint 与 TaskPackage 原意。
2. 不得替代 ResMgmt 做 AllocationDecision 裁定。
3. 不得把 ThreatAssessment 直接降格成平台命令。
4. 不得把 command_ack 解释成任务完成结论。

## 4. topic 责任

### 4.1 发布 topic

| topic | payload | 触发条件 | 下游 |
| --- | --- | --- | --- |
| bms/core/command/battle/plan_created | BattlePlan | TaskPackage 已就绪且当前约束满足 | EnhanceUnit |
| bms/core/command/battle/plan_updated | BattlePlan | 执行异常或链路降级仍可在任务约束内调整 | EnhanceUnit |
| bms/core/command/battle/effect_report | EngagementEffectReport | 执行完成或效果可判定 | TaskMgmt, HMI-BFF |
| bms/core/knowledge/inference/requested | InferenceRequest | 需要规则推理辅助交战决策 | KnowledgeRule |

### 4.2 订阅 topic

| topic | payload | 上游 | 消费动作 |
| --- | --- | --- | --- |
| bms/core/command/task/decomposed | TaskConstraint | TaskMgmt | 建立交战约束上下文 |
| bms/core/command/task/plan_created | TaskPackage | TaskMgmt | 触发 BattlePlan 生成 |
| bms/core/command/resource/allocation_committed | AllocationDecision | ResMgmt | 校核资源可用性与时间窗 |
| bms/core/resource/state_snapshot | ResourceStateSnapshot | ResMgmt | 刷新资源与能力状态 |
| bms/core/situation/fused_track | FusedTrack | SitMgmt | 更新目标事实观测输入 |
| bms/core/situation/threat/assessed | ThreatAssessment | SitMgmt | 更新威胁判断输入 |
| bms/edge/platform/event/mission_progress | MissionProgress | EnhanceUnit | 评估执行进度与偏差 |
| bms/edge/platform/event/command_ack | CommandAck | EnhanceUnit | 判断命令是否被平台受理 |
| bms/edge/platform/event/platform_alert | PlatformAlert | EnhanceUnit | 判断平台级异常 |
| bms/core/ops/comm/link_degraded | DegradationAlert | CommNet | 决定是否进入降级调整 |

## 5. 模块拆分

| 模块 | 责任 | 输入 | 输出 |
| --- | --- | --- | --- |
| TaskIntentAdapter | 接收任务包并整理交战输入上下文 | TaskConstraint, TaskPackage | 交战输入模型 |
| BattlePlanGenerator | 生成首版 BattlePlan | 交战输入模型, AllocationDecision, ThreatAssessment | BattlePlan |
| ConstraintGuard | 校核任务约束与资源边界 | TaskConstraint, AllocationDecision, MissionProgress | 约束校核结果 |
| PlanAdjustmentService | 在约束内完成计划级调整 | BattlePlan, PlatformAlert, DegradationAlert | plan_updated |
| EffectAssessmentService | 形成执行效果与闭环结论 | MissionProgress, ThreatAssessment | EngagementEffectReport |
| RuleAssistGateway | 向 KnowledgeRule 发起推理请求 | ThreatAssessment, 交战问题上下文 | InferenceRequest |

## 6. 实施步骤

1. 先实现 BattlePlanGenerator 主链，打通 TaskPackage 到 plan_created。
2. 接入 AllocationDecision 与 ResourceStateSnapshot，补齐约束校核逻辑。
3. 接入 command_ack、mission_progress 与 platform_alert，形成执行反馈闭环。
4. 接入 link_degraded，完成约束内 plan_updated 路径。
5. 补齐 effect_report 与推理请求输出，完成交战闭环验收。

## 7. 测试与验收

### 7.1 必备样例

1. 正常样例：TaskPackage -> BattlePlan -> command_ack.accepted -> mission_progress -> effect_report。
2. 异常样例：platform_alert 或 link_degraded 触发 plan_updated。
3. 边界样例：ExecutionException 越出任务约束时回退 TaskMgmt，而不是继续 plan_updated。

### 7.2 契约测试

1. BattlePlan 与平台命令映射必须符合 Formal 01。
2. TaskPackage 与 BattlePlan 的语义边界必须符合 Formal 02。
3. AllocationDecision 只能被消费，不能被 BattleCtrl 越权改写。
4. ThreatAssessment 只作为态势输入，不直接等价于执行命令。

### 7.3 完成定义

1. Code_03_BattleCtrl 中的主模块已落到实现骨架。
2. plan_created 与 plan_updated 两条链路均可验证。
3. 与 TaskMgmt、ResMgmt、EnhanceUnit、SitMgmt 的主要联调项已映射到联调矩阵。
4. 至少覆盖主业务闭环场景 A、C、D 的样例准备与验收记录。

## 8. 风险与待决项

1. 风险：不同平台能力差异可能导致 BattlePlan 到平台命令的映射规则膨胀。
2. 风险：链路降级与执行异常的职责边界若定义不清，会造成错误的任务回退。
3. 待决项：effect_report 的量化粒度与 MOE 指标绑定是否需要在后续 ICD 中进一步细化。
