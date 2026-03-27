# BMS Delivery 文档分类导航

本文档用于把 delivery 根目录下的设计文档按职责分层分类，方便后续开发、联调和治理时快速定位正确入口。

本分类是逻辑分类，不改变现有文件路径。

## 1. 分类目标

当前 delivery 根目录文档已经齐备，但如果直接按文件名平铺浏览，理解成本较高。

因此建议后续统一按以下 5 类来阅读和使用：

1. 设计治理基线。
2. 分发与联调主入口。
3. 工作包与测试执行闭环。
4. agent 与小组交付。
5. 设计完成与归档基线。

## 2. 设计治理基线

这组文档回答的是：系统设计按什么原则收敛，什么叫完成，谁拥有对象，变更怎么治理。

1. [BMS_System_Design_Goal.md](BMS_System_Design_Goal.md)
2. [BMS_Owner_Rule_Baseline.md](BMS_Owner_Rule_Baseline.md)
3. [BMS_Completion_Definition.md](BMS_Completion_Definition.md)
4. [BMS_Change_Governance.md](BMS_Change_Governance.md)

建议使用场景：

1. 新成员理解系统设计边界。
2. 判断是否允许改 topic、schema 或 ownership。
3. 判断某个工作包是否真的完成。

## 3. 分发与联调主入口

这组文档回答的是：如何把设计分发给各组，以及后续如何进入联调。

1. [BMS_Subsystem_Design_Traceability_Matrix.md](BMS_Subsystem_Design_Traceability_Matrix.md)
2. [BMS_Subsystem_Development_Handoff_Packages.md](BMS_Subsystem_Development_Handoff_Packages.md)
3. [BMS_Integration_Matrix.md](BMS_Integration_Matrix.md)
4. [BMS_Subsystem_Execution_Playbook.md](BMS_Subsystem_Execution_Playbook.md)
5. [BMS_Subsystem_Work_Package_Template.md](BMS_Subsystem_Work_Package_Template.md)
6. [workPackages/README.md](workPackages/README.md)

建议使用场景：

1. 确认某个分系统该拿哪些设计输入。
2. 确认上下游联调对象。
3. 确认工作包应该如何落模板与落目录。

## 4. 工作包与测试执行闭环

这组文档回答的是：工作包如何对接样例、测试和联调场景，形成真正可执行闭环。

1. [BMS_Execution_Index.md](BMS_Execution_Index.md)
2. [BMS_Contract_Test_Baseline.md](BMS_Contract_Test_Baseline.md)
3. [BMS_Sample_And_Test_Directory_Spec.md](BMS_Sample_And_Test_Directory_Spec.md)
4. [BMS_WorkPackage_Test_Asset_Mapping.md](BMS_WorkPackage_Test_Asset_Mapping.md)
5. [BMS_Core_Battle_Loop_Integration_Scenarios.md](BMS_Core_Battle_Loop_Integration_Scenarios.md)
6. [BMS_Phased_Implementation_And_Integration_Plan.md](BMS_Phased_Implementation_And_Integration_Plan.md)

建议使用场景：

1. 根据 workPackage 找对应 Formal ICD 样例。
2. 根据测试资产判断当前实现要补什么。
3. 根据联调场景准备 mock、样例与验收模板。

## 5. agent 与小组交付

这组文档回答的是：如何把设计输入直接交给小组或 agent，让其开始实现。

1. [BMS_Team_ICD_Delivery_Packages.md](BMS_Team_ICD_Delivery_Packages.md)
2. [BMS_Agent_Handoff_Readiness_Standard.md](BMS_Agent_Handoff_Readiness_Standard.md)
3. [BMS_Agent_Handoff_Packaging_Guide.md](BMS_Agent_Handoff_Packaging_Guide.md)

建议使用场景：

1. 判断 workPackage 是否可正式交给 agent。
2. 给某个小组整理最小设计包。
3. 约束 agent 阅读顺序与执行边界。

## 6. 设计完成与归档基线

这组文档回答的是：当前仓库是否已进入设计完成阶段，以及整个项目目录如何作为后续开发基线固定下来。

1. [BMS_Design_Completion_Gate_And_Dev_Start_Criteria.md](BMS_Design_Completion_Gate_And_Dev_Start_Criteria.md)
2. [BMS_Design_Completion_Baseline.md](BMS_Design_Completion_Baseline.md)
3. [BMS_Project_Folder_Archive_Baseline.md](BMS_Project_Folder_Archive_Baseline.md)
4. [BMS_First_Development_Package_Recommendation.md](BMS_First_Development_Package_Recommendation.md)

建议使用场景：

1. 判断现在能不能直接进入开发。
2. 判断是否可以宣布设计完成。
3. 约束后续新增文档和样例的归档位置。

## 7. 横切专项边界文档

这组文档不是主入口，但在具体子系统开发时非常关键。

1. [BMS_MsgService_vs_CommNet_Responsibility_Matrix.md](BMS_MsgService_vs_CommNet_Responsibility_Matrix.md)
2. [BMS_BFF_View_Contract_Catalog.md](BMS_BFF_View_Contract_Catalog.md)
3. [BMS_VersionDeploy_OpsMgmt_Collaboration_Rules.md](BMS_VersionDeploy_OpsMgmt_Collaboration_Rules.md)

建议使用场景：

1. CommNet 与 MsgService 边界争议。
2. BFF 聚合视图对象设计。
3. VersionDeploy 与 OpsMgmt 协同边界审查。

## 8. 推荐阅读路径

如果你的目标是“理解系统再开始开发”，建议按下面顺序读：

1. [BMS_System_Design_Goal.md](BMS_System_Design_Goal.md)
2. [BMS_Owner_Rule_Baseline.md](BMS_Owner_Rule_Baseline.md)
3. [BMS_Completion_Definition.md](BMS_Completion_Definition.md)
4. [BMS_Project_Folder_Archive_Baseline.md](BMS_Project_Folder_Archive_Baseline.md)
5. [BMS_Design_Completion_Baseline.md](BMS_Design_Completion_Baseline.md)
6. [BMS_Subsystem_Design_Traceability_Matrix.md](BMS_Subsystem_Design_Traceability_Matrix.md)
7. [BMS_Execution_Index.md](BMS_Execution_Index.md)
8. [BMS_WorkPackage_Test_Asset_Mapping.md](BMS_WorkPackage_Test_Asset_Mapping.md)
9. [workPackages/README.md](workPackages/README.md)
10. 对应 workPackage 子目录下的主工作包、ICD_Package、Payload_Checklist、AGENT_HANDOFF、TODO

## 9. 分类后的使用收益

采用本分类后，后续开发理解会更高效，原因是：

1. 不需要先猜某个文件是治理文档还是执行文档。
2. 不会把“完成定义”和“联调矩阵”混在一起阅读。
3. 可以按治理、分发、执行、交付、归档 5 条主线快速定位。
4. 新成员、工程师和 agent 可以使用同一套入口。

## 10. 当前建议

当前不建议继续拆分或移动 delivery 根目录文件。

原因如下：

1. 现有引用关系已经稳定。
2. 继续物理移动文件会增加大量链接维护成本。
3. 通过增加分类导航，已经足够显著降低理解成本。

因此，后续开发建议统一从本文件进入，而不是直接平铺浏览 delivery 根目录。
