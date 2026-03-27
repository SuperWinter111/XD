# BMS 设计图稿与契约文档总说明

本文档用于系统性说明当前 BMS 设计阶段已形成的图稿、契约文档、schema/IDL 文档之间的定义、边界与关系。

本文档不替代各专项文档，而是作为总导航与阅读入口。

当前项目文件夹统一归档基线见 [designArtifacts/delivery/BMS_Project_Folder_Archive_Baseline.md](designArtifacts/delivery/BMS_Project_Folder_Archive_Baseline.md)。

delivery 根目录文档分类导航见 [designArtifacts/delivery/README.md](designArtifacts/delivery/README.md)。

## 1. 设计产物分层

当前设计产物可分为 7 层：

1. 需求源层：定义系统要解决什么问题。
2. 架构视图层：定义系统从外部到内部的结构与交互。
3. 语义与契约层：定义任务、计划、异常、DDS、容器边界和对象拥有权。
4. 代码设计层：定义关键分系统的模块骨架与对象关系。
5. 系统设计目标层：定义后续架构、交付、集成与变更治理的共同目标。
6. 交付与集成层：定义负责人如何领取分系统工作包并进入联调。
7. schema/ICD 层：定义跨分系统可实现、可联调的消息对象与字段约束。

关系主线如下：

需求源层 -> 系统设计目标层 -> 架构视图层 -> 语义与契约层 -> 代码设计层 -> schema/ICD 层 -> 交付与集成层 -> 后续实现与联调

## 2. 需求源层

### sysFunctionalRequirements/sysFunctionalRequirements.md

定义：系统功能需求主文档。

作用：

1. 是全部架构图稿与接口设计的起点。
2. 约束系统能力范围、业务场景与目标功能。

### sysFunctionalRequirements/sysFunctionalRequirements.xmind

定义：需求脑图版整理。

作用：

1. 用于从层次结构快速审阅需求。
2. 作为 markdown 需求主文档的辅助浏览视图。

## 3. 架构视图层

本层以 plantumlC4 目录下的 PlantUML 图稿为主。

### 3.1 宏观架构图

#### plantumlC4/C4_L0_Landscape.puml

定义：系统景观图。

作用：

1. 说明 BMS 与外部系统、操作者、仿真环境之间的总体位置关系。
2. 给后续上下文图与容器图提供系统边界。

#### plantumlC4/C4_L1_Context.puml

定义：系统上下文图。

作用：

1. 说明 BMS 对外依赖与交互对象。
2. 明确人、外部系统、仿真环境和平台侧的接口关系。

#### plantumlC4/C4_L2_Container.puml

定义：BMS 主容器图。

作用：

1. 是当前唯一主容器图。
2. 定义前端、任务、态势、交战、资源、通信、规则、边缘增强等容器及依赖关系。
3. 为容器契约矩阵、DDS 主题与 L3 组件图提供基础。

### 3.2 组件图

#### plantumlC4/C4_L3_Component_01_ExtInterface.puml

定义：外部接口管理分系统组件图。

#### plantumlC4/C4_L3_Component_02_HMI.puml

定义：HMI/BFF 与前端交互职责组件图。

#### plantumlC4/C4_L3_Component_03_TaskMgmt.puml

定义：任务管理分系统组件图。

#### plantumlC4/C4_L3_Component_04_SitMgmt.puml

定义：态势管理分系统组件图。

#### plantumlC4/C4_L3_Component_05_BattleCtrl.puml

定义：交战管控分系统组件图。

#### plantumlC4/C4_L3_Component_06_ResMgmt.puml

定义：资源管理分系统组件图。

#### plantumlC4/C4_L3_Component_07_MsgService.puml

定义：消息服务与 DDS 契约治理组件图。

#### plantumlC4/C4_L3_Component_08_KnowledgeRule.puml

定义：知识与规则管理组件图。

#### plantumlC4/C4_L3_Component_09_DbMgmt.puml

定义：数据库管理组件图。

#### plantumlC4/C4_L3_Component_10_CommNet.puml

定义：通信组网组件图。

#### plantumlC4/C4_L3_Component_11_EnhanceUnit.puml

定义：协同增强单元组件图。

#### plantumlC4/C4_L3_Component_12_AuthAudit.puml

定义：权限与审计组件图。

#### plantumlC4/C4_L3_Component_13_MonitorLog.puml

定义：监控与日志组件图。

#### plantumlC4/C4_L3_Component_14_OpsMgmt.puml

定义：运维管理组件图。

#### plantumlC4/C4_L3_Component_15_VersionDeploy.puml

定义：版本与部署管理相关组件图。

组件图统一作用：

1. 细化容器内部职责划分。
2. 为后续代码设计图与分工提供边界。

### 3.3 动态图

#### plantumlC4/C4_Dynamic_01_CommandChain.puml

定义：任务指令与任务入域动态链。

#### plantumlC4/C4_Dynamic_02_SensingChain.puml

定义：态势感知与目标链路动态过程。

#### plantumlC4/C4_Dynamic_03_KillChain.puml

定义：杀伤链作为特殊任务类型的主执行动态过程。

#### plantumlC4/C4_Dynamic_04_ReplanRecovery.puml

定义：异常、计划调整、任务重构与人工干预动态过程。

动态图统一作用：

1. 说明跨分系统时序与闭环。
2. 为任务/计划/异常语义文档提供动态依据。

### 3.4 部署与补充图

#### plantumlC4/C4_Deployment_01_LabSingleServer.puml

定义：实验室单机部署图。

#### plantumlC4/C4_Deployment_02_Engineering_DualNano.puml

定义：工程双 Nano 部署图。

#### plantumlC4/Supplementary_01_UavDigitalTwin.puml

定义：无人机数字孪生/联合仿真补充图。

作用：

1. 说明不同部署条件下的运行形态。
2. 说明仿真环境如何复用真实接口契约而不变成第二套核心业务容器。

## 4. 语义与契约层

### designArtifacts/contracts/BMS_Task_Plan_And_Exception_Semantics.md

定义：任务、计划、异常、人工干预的语义基线。

作用：

1. 定义 Task 与 Plan 的边界。
2. 定义计划内调整与任务重构的分界。

### designArtifacts/contracts/BMS_Container_Contract_Matrix.md

定义：容器职责、同步接口、DDS 主题、主数据拥有权和禁止事项矩阵。

作用：

1. 约束容器间协作方式。
2. 是多 agent 并行开发边界的主文档。

### designArtifacts/contracts/BMS_DDS_Topic_Catalog.md

定义：DDS topic、QoS 档位与 topic 到 payload 的对齐目录。

作用：

1. 统一消息主题命名与 QoS 档位。
2. 为 TopicDefinition 和 MessageEnvelope 提供系统级约束来源。

### designArtifacts/contracts/BMS_Code_Interface_Object_Catalog.md

定义：跨分系统对象拥有权与语义边界目录。

作用：

1. 明确哪个分系统拥有哪个对象。
2. 防止任务对象、计划对象、态势对象、聚合视图对象混用。

### designArtifacts/review/C4_Review_Checklist.md

定义：C4 审查清单。

作用：

1. 用于系统审阅 L0/L1/L2/L3/Dynamic 的完整性。
2. 作为阶段审查入口。

### designArtifacts/review/OldSys_ICD_Reference_Assessment.md

定义：旧系统 ICD 参考价值、风险与使用边界评估文档。

作用：

1. 约束旧系统 ICD 只作为颗粒度与工程约束参考。
2. 防止旧系统混乱语义反向污染当前正式 ICD。

## 5. 代码设计层

### plantumlC4/Code_01_EnhanceUnit.puml

定义：协同增强单元代码设计图。

### plantumlC4/Code_02_TaskMgmt.puml

定义：任务管理代码设计图。

### plantumlC4/Code_03_BattleCtrl.puml

定义：交战管控代码设计图。

### plantumlC4/Code_04_SitMgmt.puml

定义：态势管理代码设计图。

### plantumlC4/Code_05_ResMgmt.puml

定义：资源管理代码设计图。

### plantumlC4/Code_06_MsgService.puml

定义：消息服务代码设计图。

### plantumlC4/Code_07_KnowledgeRule.puml

定义：知识与规则代码设计图。

### plantumlC4/Code_08_CommNet.puml

定义：通信组网代码设计图。

### plantumlC4/Code_09_DomainObjectMap.puml

定义：跨分系统领域对象映射图。

### plantumlC4/Code_10_DbMgmt.puml

定义：数据库管理代码设计图。

代码设计图统一作用：

1. 位于组件图与 proto/ICD 之间。
2. 说明内部模块骨架、核心对象和接口关系。

## 6. 系统设计目标层

### designArtifacts/delivery/BMS_System_Design_Goal.md

定义：系统设计目标与原则。

作用：

1. 明确 agent-based 与工程师协同开发的设计目标。
2. 约束分系统交付、集成、验收、变更治理的标准。
3. 作为架构、开发、交付、联调与变更治理的总目标参考。

### designArtifacts/delivery/BMS_Owner_Rule_Baseline.md

定义：跨分系统对象拥有权与越权边界基线。

### designArtifacts/delivery/BMS_Completion_Definition.md

定义：设计完成、分系统可交付、可进入联调、系统级可验收的统一完成定义。

### designArtifacts/delivery/BMS_Change_Governance.md

定义：公共接口、ownership、架构边界与工作包变更的治理流程。

### designArtifacts/delivery/BMS_Project_Folder_Archive_Baseline.md

定义：项目文件夹统一归档与目录职责基线。

### designArtifacts/delivery/BMS_Design_Completion_Gate_And_Dev_Start_Criteria.md

定义：设计完成关口与开发启动条件说明。

### designArtifacts/delivery/BMS_Design_Completion_Baseline.md

定义：当前仓库进入整体设计完成阶段的正式基线结论。

## 7. 交付与集成层

### designArtifacts/delivery/BMS_Subsystem_Design_Traceability_Matrix.md

定义：分系统到 Container、Component、Code、正式 ICD、topic 责任的追踪矩阵。

### designArtifacts/delivery/BMS_Subsystem_Development_Handoff_Packages.md

定义：分系统负责人的开发交付包清单。

### designArtifacts/delivery/BMS_Team_ICD_Delivery_Packages.md

定义：各小组 ICD 设计输入的统一分发入口。

### designArtifacts/delivery/BMS_Integration_Matrix.md

定义：系统对系统的联调关系、mock 需求与验收口径矩阵。

### designArtifacts/delivery/BMS_Subsystem_Execution_Playbook.md

定义：软件工程师或 agent 领取分系统工作包后的统一执行手册。

### designArtifacts/delivery/BMS_Subsystem_Work_Package_Template.md

定义：各分系统工作包的统一模板。

### designArtifacts/delivery/BMS_Agent_Handoff_Readiness_Standard.md

定义：workPackage 可正式交给 agent 的判定标准。

### designArtifacts/delivery/BMS_Agent_Handoff_Packaging_Guide.md

定义：向 agent 分发 workPackage 时的最小打包与交付规则。

### designArtifacts/delivery/workPackages/README.md

定义：按 agent 或分系统归档的工作包目录导航。

### designArtifacts/delivery/workPackages/wp01_battlectrl/BMS_Work_Package_01_BattleCtrl.md

定义：交战管控分系统的首个实例工作包。

### designArtifacts/delivery/workPackages/wp02_taskmgmt/BMS_Work_Package_02_TaskMgmt.md

定义：任务管理分系统的实例工作包。

### designArtifacts/delivery/workPackages/wp03_sitmgmt/BMS_Work_Package_03_SitMgmt.md

定义：态势管理分系统的实例工作包。

### designArtifacts/delivery/workPackages/wp04_resmgmt/BMS_Work_Package_04_ResMgmt.md

定义：资源管理分系统的实例工作包。

### designArtifacts/delivery/workPackages/wp05_enhanceunit/BMS_Work_Package_05_EnhanceUnit.md

定义：协同增强单元分系统的实例工作包。

### designArtifacts/delivery/workPackages/wp06_commnet/BMS_Work_Package_06_CommNet.md

定义：通信组网分系统的实例工作包。

### designArtifacts/delivery/workPackages/wp07_msgservice/BMS_Work_Package_07_MsgService.md

定义：消息服务分系统的实例工作包。

### designArtifacts/delivery/workPackages/wp08_knowledgerule/BMS_Work_Package_08_KnowledgeRule.md

定义：知识与规则分系统的实例工作包。

### designArtifacts/delivery/BMS_Contract_Test_Baseline.md

定义：正式 ICD 与跨分系统 topic 的统一契约测试最小集合。

### designArtifacts/delivery/workPackages/wp09_authaudit/BMS_Work_Package_09_AuthAudit.md

定义：权限与安全审计分系统的实例工作包。

### designArtifacts/delivery/workPackages/wp10_monitorlog/BMS_Work_Package_10_MonitorLog.md

定义：监控与日志分系统的实例工作包。

### designArtifacts/delivery/workPackages/wp11_opsmgmt/BMS_Work_Package_11_OpsMgmt.md

定义：运维管理分系统的实例工作包。

### designArtifacts/delivery/workPackages/wp12_bff_hmi/BMS_Work_Package_12_BFF_HMI.md

定义：API Gateway / BFF / HMI 分系统的实例工作包。

### designArtifacts/delivery/workPackages/wp13_versiondeploy/BMS_Work_Package_13_VersionDeploy.md

定义：版本与部署管理分系统的实例工作包。

### designArtifacts/delivery/BMS_MsgService_vs_CommNet_Responsibility_Matrix.md

定义：消息治理与通信承载职责边界对照矩阵。

### designArtifacts/delivery/BMS_BFF_View_Contract_Catalog.md

定义：BFF 聚合视图的对象、刷新方式与推送约束清单。

### designArtifacts/delivery/BMS_VersionDeploy_OpsMgmt_Collaboration_Rules.md

定义：Version / Deploy 与 OpsMgmt 的协同边界、审批权与回滚联动规则。

### designArtifacts/delivery/BMS_Execution_Index.md

定义：工作包、正式 ICD、契约测试和联调场景之间的统一执行索引。

### designArtifacts/delivery/BMS_WorkPackage_Test_Asset_Mapping.md

定义：工作包到正式 ICD、样例目录、关键样例文件与联调场景的闭环映射总表。

### designArtifacts/delivery/BMS_Sample_And_Test_Directory_Spec.md

定义：样例 payload、mock、契约测试和联调记录的统一目录规范。

### designArtifacts/delivery/BMS_Phased_Implementation_And_Integration_Plan.md

定义：按批次推进工作包实现、联调和阶段审查的实施计划。

### designArtifacts/delivery/BMS_Core_Battle_Loop_Integration_Scenarios.md

定义：主业务闭环的最小联调场景基线。

## 8. schema/ICD 层

### designArtifacts/schema/BMS_Schema_IDL_Baseline.md

定义：schema/IDL 总基线文档。

作用：

1. 汇总当前跨分系统对象的 proto 级定义。
2. 统一公共头、枚举、对象包结构和 topic 到 payload 绑定。

### designArtifacts/schema/BMS_ICD_Engineering_Guideline.md

定义：proto 与正式 ICD 的关系说明。

作用：

1. 说明 proto 是 schema 层，不等于完整工程 ICD。
2. 说明后续工程 ICD 还需要单位、范围、码表、时序、约束、拒绝码等内容。

### designArtifacts/icd/BMS_ICD_Formal_01_Platform_Execution_Chain.md

定义：平台执行链正式 ICD 专题文档。

### designArtifacts/icd/BMS_ICD_Formal_02_Task_Battle_Execution_Closure.md

定义：任务、计划、执行闭环正式 ICD 专题文档。

### designArtifacts/icd/BMS_ICD_Formal_03_Resource_Allocation_And_Reservation.md

定义：资源申请、分配、预留与释放规则正式 ICD 专题文档。

### designArtifacts/icd/BMS_ICD_Formal_04_Situation_And_Threat.md

定义：态势融合与威胁评估正式 ICD 专题文档。

### designArtifacts/icd/BMS_ICD_Formal_05_Target_Feature_And_Status_Extension.md

定义：目标特征与目标状态扩展正式 ICD 专题文档。

### designArtifacts/icd/BMS_ICD_Formal_06_Threat_Reasoning_And_Rule_Inference.md

定义：威胁理由结构化与规则推理正式 ICD 专题文档。

### designArtifacts/icd/BMS_ICD_Formal_07_Comm_Link_And_Security.md

定义：通信链路、拓扑、降级与安全事件正式 ICD 专题文档。

### designArtifacts/icd/BMS_ICD_Formal_08_Message_Governance_And_Delivery.md

定义：消息治理、投递回执与死信正式 ICD 专题文档。

### designArtifacts/icd/BMS_ICD_Formal_09_Simulation_And_Training_Integration.md

定义：仿真训练控制、状态、真值与裁决正式 ICD 专题文档。

### designArtifacts/icd/BMS_ICD_Formal_10_Ops_Audit_And_Monitoring.md

定义：运维审计与监控正式 ICD 专题文档。

### designArtifacts/icd/BMS_ICD_Formal_11_BFF_Aggregation_And_UI_Push.md

定义：BFF 聚合视图与 UI 推送正式 ICD 专题文档。

### designArtifacts/schema/BMS_Proto_Refinement_Priority.md

定义：proto 收敛路线图。

作用：

1. 标识哪些字段应先从 string 升级为枚举或结构化对象。
2. 记录哪些收敛项已完成、哪些仍待后续阶段。

### proto/README.md

定义：proto 目录导航。

作用：

1. 说明每个 schema 文件承载的对象范围。
2. 作为实现阶段进入 proto 仓的快速入口。

### proto/bms/schema/*.proto

定义：机器可实现的 schema 主体。

作用：

1. 承接跨分系统对象的结构定义。
2. 为后续生成代码、联调、消息验证与 ICD 定稿提供基础。

## 8. 当前关系链

当前最重要的关系链如下：

1. sysFunctionalRequirements.md -> C4_L0/L1/L2：定义系统边界与主容器。
2. C4_L2_Container.puml -> 各 C4_L3_Component_*.puml：定义容器内部职责。
3. C4_L3_Component_*.puml + C4_Dynamic_*.puml -> designArtifacts/contracts/BMS_Task_Plan_And_Exception_Semantics.md：定义任务闭环语义。
4. designArtifacts/contracts/BMS_Container_Contract_Matrix.md + designArtifacts/contracts/BMS_DDS_Topic_Catalog.md + designArtifacts/contracts/BMS_Code_Interface_Object_Catalog.md：定义容器契约、主题契约、对象契约。
5. 上述契约文档 -> Code_*.puml：约束代码设计图中的模块边界。
6. Code_09_DomainObjectMap.puml + designArtifacts/contracts/BMS_Code_Interface_Object_Catalog.md -> designArtifacts/schema/BMS_Schema_IDL_Baseline.md：收敛为 schema/IDL 基线。
7. designArtifacts/schema/BMS_Schema_IDL_Baseline.md -> proto/bms/schema/*.proto：形成机器可实现的 schema 文件。
8. designArtifacts/schema/BMS_Schema_IDL_Baseline.md + 正式 ICD 专题文档 + designArtifacts/schema/BMS_ICD_Engineering_Guideline.md：共同构成后续工程联调的接口基线。
9. designArtifacts/delivery/BMS_Project_Folder_Archive_Baseline.md + designArtifacts/delivery/BMS_Design_Completion_Baseline.md：构成当前仓库的开发基线和归档基线。
10. designArtifacts/delivery/BMS_Subsystem_Design_Traceability_Matrix.md + designArtifacts/delivery/BMS_Subsystem_Development_Handoff_Packages.md + designArtifacts/delivery/BMS_Integration_Matrix.md + designArtifacts/delivery/BMS_WorkPackage_Test_Asset_Mapping.md：构成分系统分发、独立开发、测试闭环与联调执行入口。

## 9. 推荐阅读顺序

推荐阅读顺序如下：

1. sysFunctionalRequirements/sysFunctionalRequirements.md
2. plantumlC4/C4_L0_Landscape.puml
3. plantumlC4/C4_L1_Context.puml
4. plantumlC4/C4_L2_Container.puml
5. designArtifacts/contracts/BMS_Container_Contract_Matrix.md
6. designArtifacts/contracts/BMS_Task_Plan_And_Exception_Semantics.md
7. plantumlC4/C4_Dynamic_01_CommandChain.puml
8. plantumlC4/C4_Dynamic_03_KillChain.puml
9. plantumlC4/C4_Dynamic_04_ReplanRecovery.puml
10. designArtifacts/contracts/BMS_Code_Interface_Object_Catalog.md
11. plantumlC4/Code_09_DomainObjectMap.puml
12. designArtifacts/schema/BMS_Schema_IDL_Baseline.md
13. designArtifacts/icd/BMS_ICD_Formal_01_Platform_Execution_Chain.md
14. designArtifacts/icd/BMS_ICD_Formal_02_Task_Battle_Execution_Closure.md
15. designArtifacts/icd/BMS_ICD_Formal_03_Resource_Allocation_And_Reservation.md
16. designArtifacts/icd/BMS_ICD_Formal_04_Situation_And_Threat.md
17. designArtifacts/icd/BMS_ICD_Formal_05_Target_Feature_And_Status_Extension.md
18. designArtifacts/icd/BMS_ICD_Formal_06_Threat_Reasoning_And_Rule_Inference.md
19. designArtifacts/icd/BMS_ICD_Formal_07_Comm_Link_And_Security.md
20. designArtifacts/icd/BMS_ICD_Formal_08_Message_Governance_And_Delivery.md
21. designArtifacts/icd/BMS_ICD_Formal_09_Simulation_And_Training_Integration.md
22. designArtifacts/icd/BMS_ICD_Formal_10_Ops_Audit_And_Monitoring.md
23. designArtifacts/icd/BMS_ICD_Formal_11_BFF_Aggregation_And_UI_Push.md
24. designArtifacts/delivery/BMS_Project_Folder_Archive_Baseline.md
25. designArtifacts/delivery/BMS_Design_Completion_Baseline.md
26. designArtifacts/delivery/BMS_Subsystem_Design_Traceability_Matrix.md
27. designArtifacts/delivery/BMS_Subsystem_Development_Handoff_Packages.md
28. designArtifacts/delivery/BMS_Team_ICD_Delivery_Packages.md
29. designArtifacts/delivery/BMS_Agent_Handoff_Readiness_Standard.md
30. designArtifacts/delivery/BMS_Agent_Handoff_Packaging_Guide.md
31. designArtifacts/delivery/BMS_Integration_Matrix.md
32. designArtifacts/delivery/BMS_Subsystem_Execution_Playbook.md
33. designArtifacts/delivery/BMS_WorkPackage_Test_Asset_Mapping.md
34. designArtifacts/delivery/BMS_Subsystem_Work_Package_Template.md
35. designArtifacts/delivery/workPackages/wp01_battlectrl/BMS_Work_Package_01_BattleCtrl.md
36. designArtifacts/delivery/workPackages/wp02_taskmgmt/BMS_Work_Package_02_TaskMgmt.md
37. designArtifacts/delivery/workPackages/wp03_sitmgmt/BMS_Work_Package_03_SitMgmt.md
38. designArtifacts/delivery/workPackages/wp04_resmgmt/BMS_Work_Package_04_ResMgmt.md
39. designArtifacts/delivery/BMS_Core_Battle_Loop_Integration_Scenarios.md
40. proto/README.md

## 10. 当前阶段收敛结论

当前阶段已经完成以下收敛：

1. 主流程关键字段已完成第一轮强类型化。
2. 任务约束已从文字化条件升级为结构化资源前提与覆盖约束。
3. 计划参数已从字符串列表升级为键值参数对象。
4. 链路等级、QoS 档位、BFF 告警类型与严重等级已标准化。
5. TopicDefinition 的发布者与订阅者已收敛为结构化 EndpointBinding。
6. 分系统分发、独立开发与联调执行入口已收敛到 delivery 分区。
7. 分系统负责人无论是工程师还是 agent，执行与验收口径已经统一。
8. 13 个工作包均已具备实例级设计包、字段核对表和 agent 交付说明。
9. Formal 01 到 Formal 11 已具备最小契约测试样例基线。
10. 项目文件夹、工作包样例闭环与整体设计完成状态已收敛为统一基线。

这意味着当前设计资料已经从“可讨论架构”推进到“整体设计完成、可直接进入 workPackage 开发”的阶段。
