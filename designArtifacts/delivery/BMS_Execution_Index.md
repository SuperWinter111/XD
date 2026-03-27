# BMS 执行索引

本文档用于把“工作包 -> 正式 ICD -> 契约测试 -> 联调场景”串成统一执行入口，方便工程师或 agent 直接按索引领取任务、准备样例并进入联调。

## 1. 使用方式

1. 先到 workPackages/ 目录定位自己对应的工作包。
2. 再按工作包关联的正式 ICD 准备契约测试样例。
3. 再按联调对象映射到联调矩阵和主业务闭环场景。
4. 最后按执行手册进入实现、mock、契约测试和联调。

## 2. 执行索引总表

| 工作包 | 正式 ICD | 契约测试组 | 主要联调对象 | 主要联调场景 |
| --- | --- | --- | --- | --- |
| [BMS_Work_Package_01_BattleCtrl](workPackages/wp01_battlectrl/BMS_Work_Package_01_BattleCtrl.md) | 01, 02, 03, 04, 06, 07 | Formal 01, 02, 03, 04, 06, 07 | TaskMgmt, ResMgmt, EnhanceUnit, SitMgmt | 主业务闭环、链路降级、异常回退 |
| [BMS_Work_Package_02_TaskMgmt](workPackages/wp02_taskmgmt/BMS_Work_Package_02_TaskMgmt.md) | 02, 03, 06 | Formal 02, 03, 06 | BattleCtrl, ResMgmt | 任务入域、资源申请、任务重构 |
| [BMS_Work_Package_03_SitMgmt](workPackages/wp03_sitmgmt/BMS_Work_Package_03_SitMgmt.md) | 04, 05, 06, 09 | Formal 04, 05, 06, 09 | BattleCtrl, KnowledgeRule, EnhanceUnit | 态势融合、威胁评估、仿真输入 |
| [BMS_Work_Package_04_ResMgmt](workPackages/wp04_resmgmt/BMS_Work_Package_04_ResMgmt.md) | 03, 07 | Formal 03, 07 | TaskMgmt, BattleCtrl, EnhanceUnit, CommNet | 资源裁定、链路质量校核 |
| [BMS_Work_Package_05_EnhanceUnit](workPackages/wp05_enhanceunit/BMS_Work_Package_05_EnhanceUnit.md) | 01, 09 | Formal 01, 09 | BattleCtrl, SitMgmt, ResMgmt | 命令翻译、边缘反馈、仿真桥接 |
| [BMS_Work_Package_06_CommNet](workPackages/wp06_commnet/BMS_Work_Package_06_CommNet.md) | 07 | Formal 07 | ResMgmt, BattleCtrl, MonitorLog | 链路质量、降级、安全事件 |
| [BMS_Work_Package_07_MsgService](workPackages/wp07_msgservice/BMS_Work_Package_07_MsgService.md) | 08 | Formal 08 | 发布者、订阅者、MonitorLog | topic 定义、回执、死信、版本兼容 |
| [BMS_Work_Package_08_KnowledgeRule](workPackages/wp08_knowledgerule/BMS_Work_Package_08_KnowledgeRule.md) | 06 | Formal 06 | SitMgmt, TaskMgmt, BattleCtrl | 推理请求、推荐输出、解释一致性 |
| [BMS_Work_Package_09_AuthAudit](workPackages/wp09_authaudit/BMS_Work_Package_09_AuthAudit.md) | 10 | Formal 10 | MonitorLog, OpsMgmt | 审计事件、安全事件纳入审计 |
| [BMS_Work_Package_10_MonitorLog](workPackages/wp10_monitorlog/BMS_Work_Package_10_MonitorLog.md) | 10 | Formal 10 | AuthAudit, MsgService, CommNet, OpsMgmt, BFF | 指标汇总、告警收敛、日志分析 |
| [BMS_Work_Package_11_OpsMgmt](workPackages/wp11_opsmgmt/BMS_Work_Package_11_OpsMgmt.md) | 10 | Formal 10 | MonitorLog, AuthAudit, Version / Deploy | 配置治理、告警处置、发布联动 |
| [BMS_Work_Package_12_BFF_HMI](workPackages/wp12_bff_hmi/BMS_Work_Package_12_BFF_HMI.md) | 11 | Formal 11 | TaskMgmt, SitMgmt, BattleCtrl, ResMgmt, MonitorLog | dashboard、alert_stream、重连恢复 |
| [BMS_Work_Package_13_VersionDeploy](workPackages/wp13_versiondeploy/BMS_Work_Package_13_VersionDeploy.md) | 10 | Formal 10 | OpsMgmt, MonitorLog | 发布、回滚、环境阻断 |

## 3. 执行入口文档

1. 工作包入口：[workPackages/README.md](workPackages/README.md) 与各子目录下的 BMS_Work_Package_* 文档。
2. 契约测试入口：[BMS_Contract_Test_Baseline.md](BMS_Contract_Test_Baseline.md)。
3. 联调入口：[BMS_Integration_Matrix.md](BMS_Integration_Matrix.md)。
4. 主业务闭环入口：[BMS_Core_Battle_Loop_Integration_Scenarios.md](BMS_Core_Battle_Loop_Integration_Scenarios.md)。
5. 执行顺序入口：[BMS_Subsystem_Execution_Playbook.md](BMS_Subsystem_Execution_Playbook.md)。
6. 实际样例资产入口：testAssets/。
7. 工作包样例闭环总表：[BMS_WorkPackage_Test_Asset_Mapping.md](BMS_WorkPackage_Test_Asset_Mapping.md)。

## 4. 使用要求

1. 每个工作包至少映射到一个正式 ICD 组。
2. 每个工作包至少映射到一组契约测试样例。
3. 每个工作包至少映射到一个主要联调对象和一个主要联调场景。
4. 若工作包、正式 ICD 或 ownership 变更，必须同步更新本索引。
5. 若样例文件路径变更，必须同步更新 [BMS_WorkPackage_Test_Asset_Mapping.md](BMS_WorkPackage_Test_Asset_Mapping.md)。
