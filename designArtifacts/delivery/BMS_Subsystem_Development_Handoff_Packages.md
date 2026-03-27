# BMS 分系统开发交付包清单

本文档用于把每个分系统负责人实际应收到的设计材料、实现边界与交付要求整理成统一分发包。这里的负责人可以是软件工程师，也可以是承担该分系统实现任务的 agent。

## 1. 每个分系统交付包的标准内容

每个分系统交付包至少应包含：

1. 分系统职责说明。
2. 对应 Container / Component / Code 图。
3. 必须遵守的正式 ICD 清单。
4. topic 发布与订阅清单。
5. 上下游联调对象与 mock 需求。
6. 本分系统验收清单。
7. 如需落成独立工作包，应使用 [BMS_Subsystem_Work_Package_Template.md](designArtifacts/delivery/BMS_Subsystem_Work_Package_Template.md)。
8. 如涉及 owner、完成标准或公共接口变更，必须同时附带治理基线文档。
9. 契约测试样例必须以 [BMS_Contract_Test_Baseline.md](designArtifacts/delivery/BMS_Contract_Test_Baseline.md) 为最小基线。
10. 如需按小组直接分发 ICD 设计输入，应同时附带 [BMS_Team_ICD_Delivery_Packages.md](BMS_Team_ICD_Delivery_Packages.md) 及对应 workPackage 子目录下的 ICD_Package.md。
11. 如需正式下发给 agent，应同时遵守 [BMS_Agent_Handoff_Readiness_Standard.md](BMS_Agent_Handoff_Readiness_Standard.md) 与 [BMS_Agent_Handoff_Packaging_Guide.md](BMS_Agent_Handoff_Packaging_Guide.md)。

## 2. 分系统交付包映射

| 分系统 | 必发设计文件 | 必读正式 ICD | 必读契约文件 | 实施重点 | 必交测试件 | 交付输出物 |
| --- | --- | --- | --- | --- | --- | --- |
| TaskMgmt | C4_L2, C4_L3_Component_03, Code_02 | 02, 03, 06 | Container_Contract_Matrix, DDS_Topic_Catalog, Code_Interface_Object_Catalog | 任务入域、分解、方案生成、调度 | 任务指令样例、资源申请样例、契约测试 | 任务域服务设计、topic producer/consumer、mock 与契约测试 |
| SitMgmt | C4_L2, C4_L3_Component_04, Code_04 | 04, 05, 06, 09 | 同上 | 融合、特征快照、威胁评估、回放输入 | 目标融合样例、威胁评估样例、仿真输入样例 | 态势融合服务设计、威胁评估服务设计、仿真输入适配 |
| BattleCtrl | C4_L2, C4_L3_Component_05, Code_03 | 01, 02, 03, 04, 06, 07 | 同上 | 交战计划、执行控制、异常回退 | 平台命令样例、执行回传样例、异常链路样例 | 交战计划、执行监控、异常回退实现 |
| ResMgmt | C4_L2, C4_L3_Component_06, Code_05 | 03, 07 | 同上 | 资源状态、能力收敛、分配裁定 | 状态快照样例、分配结果样例 | 资源状态、能力、分配裁定实现 |
| EnhanceUnit | C4_L2, C4_L3_Component_11, Code_01 | 01, 09 | DDS_Topic_Catalog, OldSys_ICD_Reference_Assessment | 平台协议适配、命令翻译、边缘事件上报 | flight_state、command_ack、mission_progress 样例 | 平台适配、边缘状态/命令映射、仿真桥接 |
| CommNet | C4_L2, C4_L3_Component_10, Code_08 | 07 | DDS_Topic_Catalog, Code_Interface_Object_Catalog | 拓扑、链路质量、降级、安全事件 | link_quality、degraded、security_event 样例 | 拓扑、链路质量、降级与安全事件实现 |
| MsgService | C4_L2, C4_L3_Component_07, Code_06 | 08 | DDS_Topic_Catalog, Schema_IDL_Baseline | topic registry、回执、死信、订阅治理 | 投递回执样例、死信样例 | topic registry、订阅登记、回执与死信治理 |
| KnowledgeRule | C4_L2, C4_L3_Component_08, Code_07 | 06 | Code_Interface_Object_Catalog | 推理请求、规则解释、推荐输出 | inference_requested、recommended 样例 | 推理服务、规则引用、推荐输出 |
| AuthAudit | C4_L2, C4_L3_Component_12 | 10 | DDS_Topic_Catalog, Code_Interface_Object_Catalog | 认证、权限与审计 | audit_event、认证失败样例 | 认证权限实现、审计事件输出 |
| MonitorLog | C4_L2, C4_L3_Component_13 | 10 | DDS_Topic_Catalog, Code_Interface_Object_Catalog | 指标汇总、告警收敛、日志分析 | metric、alert、死信与链路异常样例 | 监控指标、告警与日志分析实现 |
| OpsMgmt | C4_L2, C4_L3_Component_14 | 10 | DDS_Topic_Catalog, Container_Contract_Matrix | 配置、自检、作业、流程治理 | config_changed、告警处置、自检样例 | 配置治理、运维任务、流程与作业实现 |
| Version / Deploy | C4_L2, C4_L3_Component_15 | 10 | DDS_Topic_Catalog, Container_Contract_Matrix | 版本、发布、回滚、环境检测 | release_event、回滚、环境阻断样例 | 发布流程、版本基线、回滚与环境检测实现 |
| API Gateway / BFF / HMI | C4_L2, C4_L3_Component_02 | 11 | Container_Contract_Matrix | 聚合只读查询、UI 推送、订阅恢复 | dashboard、alert_stream、重连恢复样例 | 聚合查询、UI 推送、前端只读视图 |

## 3. 标准领取顺序

1. 先在 [BMS_Subsystem_Design_Traceability_Matrix.md](designArtifacts/delivery/BMS_Subsystem_Design_Traceability_Matrix.md) 中确认自己的边界。
2. 再阅读 [BMS_Owner_Rule_Baseline.md](designArtifacts/delivery/BMS_Owner_Rule_Baseline.md) 与 [BMS_Completion_Definition.md](designArtifacts/delivery/BMS_Completion_Definition.md)。
3. 如任务涉及公共接口或 ownership 调整，再阅读 [BMS_Change_Governance.md](designArtifacts/delivery/BMS_Change_Governance.md)。
4. 再从上表领取对应设计文件与正式 ICD。
5. 再依据 [BMS_Integration_Matrix.md](designArtifacts/delivery/BMS_Integration_Matrix.md) 确认上下游联调对象。
6. 再依据 [BMS_Core_Battle_Loop_Integration_Scenarios.md](designArtifacts/delivery/BMS_Core_Battle_Loop_Integration_Scenarios.md) 对齐主业务闭环场景。
7. 最后按 [BMS_Subsystem_Execution_Playbook.md](designArtifacts/delivery/BMS_Subsystem_Execution_Playbook.md) 执行实现、mock、契约测试与联调。

## 4. 交付要求

1. 负责人不得只拿 ICD，不拿对应的 Component / Code 图。
2. 负责人不得只看自己发布的 topic，还必须看自己订阅 topic 的 owner 文档。
3. 所有分系统开发必须配套 mock 方案与契约测试。
4. 负责人交付时必须同时给出正常链路和异常链路样例。
5. 负责人可以是工程师或 agent，但验收标准完全一致。
6. 负责人必须遵守 owner rule、completion definition 和 change governance。

## 5. 完成标准

一个分系统交付包只有在下列结果齐备时，才可以进入联调：

1. 设计输入完整，且与追踪矩阵一致。
2. topic producer / consumer 已形成清单。
3. mock 与契约测试已经准备完成。
4. 输出对象、异常对象、回执对象都有样例。
5. 联调验收项已映射到系统联调矩阵。
6. 联调验收项已映射到主业务闭环场景基线。
7. 已满足 [BMS_Completion_Definition.md](designArtifacts/delivery/BMS_Completion_Definition.md) 的最小要求。

## 6. 已落地工作包

1. [BMS_Subsystem_Work_Package_Template.md](BMS_Subsystem_Work_Package_Template.md)：通用工作包模板。
2. [BMS_Work_Package_01_BattleCtrl.md](workPackages/wp01_battlectrl/BMS_Work_Package_01_BattleCtrl.md)：BattleCtrl 首个实例工作包。
3. [BMS_Work_Package_02_TaskMgmt.md](workPackages/wp02_taskmgmt/BMS_Work_Package_02_TaskMgmt.md)：TaskMgmt 实例工作包。
4. [BMS_Work_Package_03_SitMgmt.md](workPackages/wp03_sitmgmt/BMS_Work_Package_03_SitMgmt.md)：SitMgmt 实例工作包。
5. [BMS_Work_Package_04_ResMgmt.md](workPackages/wp04_resmgmt/BMS_Work_Package_04_ResMgmt.md)：ResMgmt 实例工作包。
6. [BMS_Work_Package_05_EnhanceUnit.md](workPackages/wp05_enhanceunit/BMS_Work_Package_05_EnhanceUnit.md)：EnhanceUnit 实例工作包。
7. [BMS_Work_Package_06_CommNet.md](workPackages/wp06_commnet/BMS_Work_Package_06_CommNet.md)：CommNet 实例工作包。
8. [BMS_Work_Package_07_MsgService.md](workPackages/wp07_msgservice/BMS_Work_Package_07_MsgService.md)：MsgService 实例工作包。
9. [BMS_Work_Package_08_KnowledgeRule.md](workPackages/wp08_knowledgerule/BMS_Work_Package_08_KnowledgeRule.md)：KnowledgeRule 实例工作包。
10. [BMS_Work_Package_09_AuthAudit.md](workPackages/wp09_authaudit/BMS_Work_Package_09_AuthAudit.md)：AuthAudit 实例工作包。
11. [BMS_Work_Package_10_MonitorLog.md](workPackages/wp10_monitorlog/BMS_Work_Package_10_MonitorLog.md)：MonitorLog 实例工作包。
12. [BMS_Work_Package_11_OpsMgmt.md](workPackages/wp11_opsmgmt/BMS_Work_Package_11_OpsMgmt.md)：OpsMgmt 实例工作包。
13. [BMS_Work_Package_12_BFF_HMI.md](workPackages/wp12_bff_hmi/BMS_Work_Package_12_BFF_HMI.md)：API Gateway / BFF / HMI 实例工作包。
14. [BMS_Work_Package_13_VersionDeploy.md](workPackages/wp13_versiondeploy/BMS_Work_Package_13_VersionDeploy.md)：Version / Deploy 实例工作包。
15. [BMS_MsgService_vs_CommNet_Responsibility_Matrix.md](BMS_MsgService_vs_CommNet_Responsibility_Matrix.md)：消息治理与通信承载职责对照矩阵。
16. [BMS_BFF_View_Contract_Catalog.md](BMS_BFF_View_Contract_Catalog.md)：BFF 聚合视图契约清单。
17. [BMS_VersionDeploy_OpsMgmt_Collaboration_Rules.md](BMS_VersionDeploy_OpsMgmt_Collaboration_Rules.md)：部署与运维协同约束。
18. [BMS_Execution_Index.md](BMS_Execution_Index.md)：工作包到测试与联调的执行索引。
19. [BMS_Sample_And_Test_Directory_Spec.md](BMS_Sample_And_Test_Directory_Spec.md)：样例与测试目录规范。
20. [BMS_Phased_Implementation_And_Integration_Plan.md](BMS_Phased_Implementation_And_Integration_Plan.md)：分批实施与联调计划。
21. [BMS_Contract_Test_Baseline.md](BMS_Contract_Test_Baseline.md)：系统级契约测试最小基线。
22. [BMS_Core_Battle_Loop_Integration_Scenarios.md](designArtifacts/delivery/BMS_Core_Battle_Loop_Integration_Scenarios.md)：主业务闭环联调场景基线。
