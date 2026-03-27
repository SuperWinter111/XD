# BMS 小组 ICD 设计包总览

本文档用于把“每个小组到底应该拿哪些 ICD 设计文件”整理成统一分发入口。

## 1. 分发原则

1. 不建议把 11 份 Formal ICD 全量复制给每个小组。
2. 建议给每个小组发“本组专属 ICD 设计包”，由以下部分组成：
   1. 本组主工作包文档。
   2. 本组必须遵守的 Formal ICD 原文。
   3. 本组必须阅读的补充协作文档、责任边界文档和视图契约文档。
   4. 本组重点 topic、payload、边界和验收项说明。
3. 这样能保证：
   1. 小组拿到的是完整设计输入。
   2. 不会因为收到无关 ICD 而淹没重点。
   3. 多组共享同一 Formal ICD 时仍保持单一事实来源。

## 2. 当前交付方式

1. 每个 workPackage 子目录下新增 ICD_Package.md，作为该小组的 ICD 设计包入口。
2. 每个 ICD_Package.md 会明确：
   1. 必读 Formal ICD。
   2. 必读补充设计文档。
   3. 本组重点确认对象与 topic。
   4. 交付前必须完成的核对项。

## 3. 小组设计包入口

1. [wp01 BattleCtrl ICD 包](workPackages/wp01_battlectrl/ICD_Package.md)
2. [wp02 TaskMgmt ICD 包](workPackages/wp02_taskmgmt/ICD_Package.md)
3. [wp03 SitMgmt ICD 包](workPackages/wp03_sitmgmt/ICD_Package.md)
4. [wp04 ResMgmt ICD 包](workPackages/wp04_resmgmt/ICD_Package.md)
5. [wp05 EnhanceUnit ICD 包](workPackages/wp05_enhanceunit/ICD_Package.md)
6. [wp06 CommNet ICD 包](workPackages/wp06_commnet/ICD_Package.md)
7. [wp07 MsgService ICD 包](workPackages/wp07_msgservice/ICD_Package.md)
8. [wp08 KnowledgeRule ICD 包](workPackages/wp08_knowledgerule/ICD_Package.md)
9. [wp09 AuthAudit ICD 包](workPackages/wp09_authaudit/ICD_Package.md)
10. [wp10 MonitorLog ICD 包](workPackages/wp10_monitorlog/ICD_Package.md)
11. [wp11 OpsMgmt ICD 包](workPackages/wp11_opsmgmt/ICD_Package.md)
12. [wp12 BFF_HMI ICD 包](workPackages/wp12_bff_hmi/ICD_Package.md)
13. [wp13 VersionDeploy ICD 包](workPackages/wp13_versiondeploy/ICD_Package.md)

## 4. 使用建议

1. 小组先读自己目录下的 ICD_Package.md。
2. 再读本组主工作包文档。
3. 再按 ICD_Package.md 中的顺序阅读 Formal ICD 和补充设计文档。
4. 最后用 BMS_Execution_Index 和 BMS_Contract_Test_Baseline 准备样例与联调。
