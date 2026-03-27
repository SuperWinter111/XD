# BMS 工作包目录

本目录用于把各 agent 或分系统负责的工作包按独立子文件夹归档，避免通用治理文档与实例工作包混放在同一层级。

## 1. 使用原则

1. delivery 根目录仅保留通用治理、索引、计划、基线和跨分系统协作文档。
2. 每个工作包使用单独子目录，便于后续在同目录补充样例、说明和阶段记录。
3. 子目录命名与 testAssets/workPackages 下的编号保持一致，方便文档与测试资产对照。
4. 每个可交付工作包应至少包含主工作包、ICD_Package、Payload_Checklist、README、STATUS、TODO。

## 2. 工作包目录清单

1. wp01_battlectrl/BMS_Work_Package_01_BattleCtrl.md
2. wp02_taskmgmt/BMS_Work_Package_02_TaskMgmt.md
3. wp03_sitmgmt/BMS_Work_Package_03_SitMgmt.md
4. wp04_resmgmt/BMS_Work_Package_04_ResMgmt.md
5. wp05_enhanceunit/BMS_Work_Package_05_EnhanceUnit.md
6. wp06_commnet/BMS_Work_Package_06_CommNet.md
7. wp07_msgservice/BMS_Work_Package_07_MsgService.md
8. wp08_knowledgerule/BMS_Work_Package_08_KnowledgeRule.md
9. wp09_authaudit/BMS_Work_Package_09_AuthAudit.md
10. wp10_monitorlog/BMS_Work_Package_10_MonitorLog.md
11. wp11_opsmgmt/BMS_Work_Package_11_OpsMgmt.md
12. wp12_bff_hmi/BMS_Work_Package_12_BFF_HMI.md
13. wp13_versiondeploy/BMS_Work_Package_13_VersionDeploy.md

## 3. 交付给 agent 的判断口径

1. 是否可正式交付给 agent，以 [BMS_Agent_Handoff_Readiness_Standard.md](../BMS_Agent_Handoff_Readiness_Standard.md) 为准。
2. 如何打包交给 agent，以 [BMS_Agent_Handoff_Packaging_Guide.md](../BMS_Agent_Handoff_Packaging_Guide.md) 为准。

## 4. 开发路线图入口

1. 当前推荐的剩余工作包开发顺序、分批推进方式和退出条件，统一以 [BMS_Phased_Implementation_And_Integration_Plan.md](../BMS_Phased_Implementation_And_Integration_Plan.md) 为准。
2. wp07_msgservice 已实现完成并审核通过，后续工作包默认把它作为消息治理基础设施基线使用。
