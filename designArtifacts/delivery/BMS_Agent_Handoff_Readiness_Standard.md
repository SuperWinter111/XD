# BMS Agent 交付就绪标准

本文档用于回答两个问题：

1. 一个 workPackage 的设计什么时候算结束。
2. 什么时候可以把该 workPackage 正式交给对应 agent 进入实现或联调准备。

本文档是对 [BMS_Completion_Definition.md](BMS_Completion_Definition.md) 的细化，适用于各工作包目录下的 agent 交付判定。

## 1. 设计结束的判定层级

一个 workPackage 的状态建议分为 4 级：

1. 草案中：边界、对象、topic、上下游仍在变动。
2. 设计冻结：小组职责、正式 ICD、topic 边界和 owner rule 已稳定。
3. 可交付给 agent：agent 已经可以按包内材料直接拆实现任务、写骨架、补测试样例。
4. 可进入联调：上下游版本与样例已经足够支撑真实联调。

只有达到“可交付给 agent”，才建议正式下发给对应 agent。

## 2. 设计结束标准

满足以下条件时，该 workPackage 可视为“设计结束”：

1. 主工作包文档已经稳定，职责范围、输入输出、禁止事项明确。
2. ICD_Package 已稳定，正式 ICD、补充文档、关键 topic、关键 payload 清单齐备。
3. Payload_Checklist 已完成，关键字段语义、边界和常见错误已列出。
4. README、STATUS、TODO 已齐备，且能指导 agent 按顺序领取工作。
5. 对应 testAssets/workPackages 目录已有 README，至少说明样例入口、当前基线和待补样例方向。
6. 该工作包涉及的正式 ICD、topic catalog、contract matrix 与当前设计一致。
7. owner rule 已明确，没有未决的主拥有权冲突。
8. 该工作包没有“必须等别人先定义字段”这一类阻断项，或者阻断项已显式记录在 TODO/STATUS 中。

## 3. 可交付给 agent 的最低门槛

只有在以下条件同时满足时，才建议把 workPackage 交给对应 agent：

1. agent 能从主工作包读出明确职责边界。
2. agent 能从 ICD_Package 找到必须遵守的正式 ICD 和上下游对象。
3. agent 能从 Payload_Checklist 看懂关键 payload 的字段级限制。
4. agent 能从 TODO 直接提取首批实现任务，不需要二次口头解释。
5. agent 能从 testAssets/workPackages 对应目录找到最小测试入口或样例基线。
6. agent 已知哪些对象可以发布，哪些只能订阅，哪些禁止越权生成。
7. 当前包内未留有“对象还没命名”“topic 还未定”“字段是否需要保留待讨论”这类核心未决项。

如果以上 7 项有任意 1 项不满足，则不应视为可正式交付给 agent。

## 4. 可交付但不算设计结束的情况

以下情况可以让 agent 做准备工作，但不应标记为设计结束：

1. 只允许先搭代码骨架，不允许落 payload 结构。
2. topic 名称已定，但 payload 字段级语义尚未冻结。
3. 上下游对象边界已定，但异常样例仍缺失。
4. 主链路已稳定，但回退、拒绝、降级语义尚未确认。

这类状态建议标记为“可预研”或“可搭骨架”，不要标记为“设计结束”。

## 5. 不可交付给 agent 的典型信号

出现以下任一情况时，不建议交付：

1. 主工作包还在频繁改职责边界。
2. ICD_Package 中正式 ICD 仍有待补编号或待确认文档。
3. Payload_Checklist 只列对象名，没有字段级约束。
4. TODO 仍以“待讨论”“待明确”为主，缺少可执行项。
5. testAssets 目录只有空文件夹，没有入口说明。
6. 对同一 topic 存在多个 owner 口径。
7. 关键异常链路没有定义拒绝、回退或降级方式。

## 6. 建议的交付判定方法

每个 workPackage 在下发给 agent 之前，建议按下表自检：

| 检查项 | 判定问题 | 通过标准 |
| --- | --- | --- |
| 职责边界 | agent 是否能明确知道本组做什么、不做什么 | 主工作包与 owner rule 无冲突 |
| 契约输入 | agent 是否能准确找到必读 ICD 和 topic | ICD_Package 完整 |
| 字段语义 | agent 是否能知道字段不可删改点 | Payload_Checklist 完整 |
| 执行入口 | agent 是否能直接开始拆任务 | TODO 为可执行项 |
| 测试入口 | agent 是否能直接找到样例和验证入口 | testAssets README 可用 |
| 联调边界 | agent 是否知道上下游是谁 | ICD_Package 与 integration matrix 一致 |
| 风险状态 | 是否仍有核心阻断问题 | STATUS/TODO 已显式记录 |

以上检查项全部通过后，可标记该工作包为“Ready for Agent Handoff”。

## 7. Ready for Agent Handoff 的最终定义

一个 workPackage 只有在以下结果全部成立时，才应在 STATUS 中标记为可交付：

1. 设计结构齐备：主工作包、ICD_Package、Payload_Checklist、README、STATUS、TODO 已存在。
2. 契约基线齐备：正式 ICD、topic、payload、owner rule 已能闭环说明。
3. 执行入口齐备：TODO 已能直接拆首批任务。
4. 样例入口齐备：testAssets 对应目录已能指向最小样例基线。
5. 风险透明：仍未解决的问题已被显式登记，而不是隐藏在口头说明中。

## 8. 与现有基线文档的关系

1. 本文档不替代 [BMS_Completion_Definition.md](BMS_Completion_Definition.md)，而是把“可交付给 agent”这一层做细化。
2. 如本文档与工作包内说明冲突，以更严格要求为准。
3. agent 与工程师适用同一套交付判定，只是领取方式不同。
4. 如果需要区分“可开工”和“整体设计完成”，以 [BMS_Design_Completion_Gate_And_Dev_Start_Criteria.md](BMS_Design_Completion_Gate_And_Dev_Start_Criteria.md) 为准。
