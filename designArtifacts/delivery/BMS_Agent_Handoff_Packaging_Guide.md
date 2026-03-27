# BMS Agent 文件打包指南

本文档用于定义：当一个 workPackage 已达到可交付状态后，应该如何把文件打包给对应 agent。

## 1. 打包目标

打包的目的不是复制全部设计资料，而是让 agent 在最小上下文内获得：

1. 明确职责边界。
2. 明确契约输入。
3. 明确字段级限制。
4. 明确首批执行任务。
5. 明确测试入口。

## 2. 推荐打包方式

推荐两种方式：

1. 仓内引用式打包。
2. 独立快照式打包。

如果 agent 与你工作在同一仓库，优先使用“仓内引用式打包”。
如果 agent 只能拿一组固定文件，不方便跨目录检索，则使用“独立快照式打包”。

## 3. 仓内引用式打包

适用场景：agent 直接在当前仓库中工作。

最小交付清单如下：

1. workPackages 对应子目录中的主工作包。
2. 同目录中的 ICD_Package。
3. 同目录中的 Payload_Checklist。
4. 同目录中的 README、STATUS、TODO。
5. testAssets/workPackages 对应子目录 README。
6. 该工作包在 ICD_Package 中引用到的正式 ICD。
7. 公共治理基线文档。

建议按以下顺序交给 agent：

1. workPackages/wpXX_xxx/README.md
2. workPackages/wpXX_xxx/BMS_Work_Package_xx_xxx.md
3. workPackages/wpXX_xxx/ICD_Package.md
4. workPackages/wpXX_xxx/Payload_Checklist.md
5. workPackages/wpXX_xxx/TODO.md
6. testAssets/workPackages/wpXX_xxx/README.md
7. BMS_Completion_Definition.md
8. BMS_Agent_Handoff_Readiness_Standard.md

## 4. 独立快照式打包

适用场景：agent 不能自由浏览整个仓库，只能接收一个固定包。

建议每个小组输出一个独立目录，命名如下：

1. agent_handoff/wp01_battlectrl/
2. agent_handoff/wp02_taskmgmt/
3. agent_handoff/wp03_sitmgmt/
4. 其余工作包按同样规则处理。

每个独立目录建议包含：

1. 00_README.md
2. 01_Work_Package.md
3. 02_ICD_Package.md
4. 03_Payload_Checklist.md
5. 04_STATUS.md
6. 05_TODO.md
7. 06_TestAsset_Entry.md
8. refs/ 下放本组必读正式 ICD 与公共治理文档

## 5. 每个包必须放入的文件

无论采用哪种打包方式，每个 agent 包至少需要：

1. 主工作包文件。
2. ICD_Package。
3. Payload_Checklist。
4. TODO。
5. testAssets 入口说明。
6. Completion Definition。
7. 如涉及 ownership、公共接口或职责冲突，还必须附带：
8. Change Governance。
9. Owner Rule Baseline。
10. Integration Matrix。

## 6. 不建议直接打给 agent 的文件形态

以下做法不建议采用：

1. 只给一份主工作包，不给 ICD_Package。
2. 只给 topic 清单，不给 payload 字段级核对表。
3. 只给工作包目录，不告诉 agent 先读顺序。
4. 只给 testAssets 空目录，不给入口说明。
5. 把多个小组文件混在一个目录里，不标主责范围。

## 7. 推荐的交付话术模板

给 agent 时，建议附 1 段固定说明：

1. 你只负责本工作包主职责范围。
2. 先按 README 的顺序阅读。
3. 严格遵守 ICD_Package 和 Payload_Checklist。
4. 只能发布本组 owner 的对象，不得越权生成别组权威对象。
5. 从 TODO 中领取首批任务。
6. 样例与验证入口见 testAssets 对应目录 README。

## 8. 交付前检查清单

在把包发给 agent 之前，建议最后检查：

1. README 是否已写清阅读顺序。
2. TODO 是否都是可执行项，而非讨论项。
3. STATUS 是否说明当前阶段和阻断项。
4. ICD_Package 是否列清正式 ICD 与联调对象。
5. Payload_Checklist 是否至少列出重点字段语义与常见错误。
6. testAssets 入口说明是否能定位到最小样例基线。

## 9. 最小交付建议

如果你希望先快速下发给 agent，而不是做完整快照，最小可交付集合建议就是：

1. 对应工作包目录 6 个文件：
2. README.md
3. BMS_Work_Package_xx_*.md
4. ICD_Package.md
5. Payload_Checklist.md
6. STATUS.md
7. TODO.md
8. 对应 testAssets/workPackages/wpXX_xxx/README.md
9. delivery 根目录的公共基线 2 到 4 份。

## 10. 建议的公共基线最小集合

通常建议至少随包附带以下公共基线：

1. [BMS_Completion_Definition.md](BMS_Completion_Definition.md)
2. [BMS_Agent_Handoff_Readiness_Standard.md](BMS_Agent_Handoff_Readiness_Standard.md)
3. [BMS_Owner_Rule_Baseline.md](BMS_Owner_Rule_Baseline.md)
4. [BMS_Contract_Test_Baseline.md](BMS_Contract_Test_Baseline.md)

如果该组涉及跨组协同，再增加：

1. [BMS_Integration_Matrix.md](BMS_Integration_Matrix.md)
2. [BMS_Change_Governance.md](BMS_Change_Governance.md)
