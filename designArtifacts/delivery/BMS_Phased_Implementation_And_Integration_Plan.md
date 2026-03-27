# BMS 分批实施与联调计划

本文档用于把当前设计交付物转换为可执行的阶段计划，明确每一批优先实现哪些工作包、优先打通哪些链路，以及每批的通过标准。

当前版本已根据 wp07_msgservice 审核通过状态更新。后续排序以“先形成主业务闭环输入链，再补治理与展示域”为原则，不再按工作包编号顺序推进。

## 1. 计划目标

1. 避免一次性同时推进全部工作包导致协同面过大。
2. 先收敛主业务闭环，再扩展到治理、前端与发布运维。
3. 让工程师或 agent 可以按批次逐步推进实现与联调。
4. 已完成并审核通过的工作包转入冻结基线，不再与后续未实现包混排。

## 2. 当前已完成基线

范围：

1. [BMS_Work_Package_07_MsgService.md](workPackages/wp07_msgservice/BMS_Work_Package_07_MsgService.md)。

状态：

1. wp07_msgservice 已实现完成并审核通过。
2. 已形成 sqlite 默认持久化、随程序目录分发 sqlite3.dll 的工程基线。
3. 当前实现验证结果为 9/9 测试通过，含 SQLite 字段级集成测试。

后续作用：

1. 作为 MonitorLog、业务分系统和后续上层程序集成的消息治理基础设施基线。
2. 作为后续工作包 trace_id、topic 注册、订阅治理、回执与死信观测的复用底座。

## 3. 第一批：主业务入口与桥接底座

范围：

1. [BMS_Work_Package_02_TaskMgmt.md](workPackages/wp02_taskmgmt/BMS_Work_Package_02_TaskMgmt.md)。
2. [BMS_Work_Package_05_EnhanceUnit.md](workPackages/wp05_enhanceunit/BMS_Work_Package_05_EnhanceUnit.md)。
3. [BMS_Work_Package_06_CommNet.md](workPackages/wp06_commnet/BMS_Work_Package_06_CommNet.md)。

目标：

1. 打通任务入域与 TaskPackage、AllocationRequest 主链。
2. 打通 BattlePlan 到 command_ack、mission_progress、platform_registered、RawTargetInput 的边缘桥接主链。
3. 打通链路质量、降级与安全事件主链，形成资源、交战和观测所需的通信输入。

通过标准：

1. TaskMgmt、EnhanceUnit、CommNet 三包各自主链可独立验证。
2. AllocationRequest、command_ack、mission_progress、link_quality、link_degraded 的语义边界稳定。
3. 至少完成 Formal 01、02、07、09 中对应对象的最小契约测试组。

## 4. 第二批：资源与态势权威对象

范围：

1. [BMS_Work_Package_04_ResMgmt.md](workPackages/wp04_resmgmt/BMS_Work_Package_04_ResMgmt.md)。
2. [BMS_Work_Package_03_SitMgmt.md](workPackages/wp03_sitmgmt/BMS_Work_Package_03_SitMgmt.md)。
3. 第一批工作包继续联调。

目标：

1. 基于 AllocationRequest、平台注册、链路质量输入形成 AllocationDecision 与 ResourceStateSnapshot。
2. 基于 RawTargetInput、外部态势和仿真真值形成 FusedTrack 与 ThreatAssessment。
3. 为 BattleCtrl 提供稳定的资源与态势权威输入。

通过标准：

1. allocation_committed、state_snapshot、fused_track、threat_assessed 四条主链可验证。
2. RecommendationItem 尚未接入前，SitMgmt 的权威对象语义已可独立成立。
3. 至少完成 Formal 03、04、05、09 的最小契约测试组。

## 5. 第三批：交战闭环与规则辅助

范围：

1. [BMS_Work_Package_01_BattleCtrl.md](workPackages/wp01_battlectrl/BMS_Work_Package_01_BattleCtrl.md)。
2. [BMS_Work_Package_08_KnowledgeRule.md](workPackages/wp08_knowledgerule/BMS_Work_Package_08_KnowledgeRule.md)。
3. 前两批工作包继续联调。

目标：

1. 打通 TaskPackage、AllocationDecision、FusedTrack、ThreatAssessment 到 BattlePlan 的交战闭环。
2. 打通 inference_requested 到 recommended、reason_trace 的规则辅助链。
3. 形成“任务 -> 资源/态势 -> 交战 -> 平台反馈 -> 效果回流”的主业务闭环。

通过标准：

1. plan_created、plan_updated、effect_report、recommended 四条关键链路可验证。
2. KnowledgeRule 只输出辅助对象，不替代 ThreatAssessment、TaskPackage、BattlePlan。
3. 至少完成 Formal 01、03、04、06 的跨包联调最小测试组。

## 6. 第四批：观测与审计治理

范围：

1. [BMS_Work_Package_10_MonitorLog.md](workPackages/wp10_monitorlog/BMS_Work_Package_10_MonitorLog.md)。
2. [BMS_Work_Package_09_AuthAudit.md](workPackages/wp09_authaudit/BMS_Work_Package_09_AuthAudit.md)。

目标：

1. 汇聚 MsgService、CommNet、业务域输出，形成 metric、alert、log_digest 主链。
2. 接入 SecurityEvent、用户动作和运维动作摘要，形成 access_decision 与 audit_event 主链。
3. 建立 trace_id 维度的跨分系统观测与审计基础。

通过标准：

1. Formal 10 的最小契约测试组通过。
2. MonitorMetric、MonitorAlert、AuditEvent、AccessDecisionRecord 链路可追溯。
3. 监控域与审计域职责边界清晰。

## 7. 第五批：运维与发布治理

范围：

1. [BMS_Work_Package_11_OpsMgmt.md](workPackages/wp11_opsmgmt/BMS_Work_Package_11_OpsMgmt.md)。
2. [BMS_Work_Package_13_VersionDeploy.md](workPackages/wp13_versiondeploy/BMS_Work_Package_13_VersionDeploy.md)。

目标：

1. 基于 MonitorLog 和 AuthAudit 输入打通 incident_updated、config_changed、ops_job、selfcheck_result。
2. 基于 config_changed、monitor alert 和 incident_updated 打通 release_event 与 rollback_record。
3. 形成运维治理与发布治理闭环。

通过标准：

1. Formal 10 中运维与发布对象的最小契约测试组通过。
2. OpsMgmt 与 Version / Deploy 的协同边界符合协作文档约束。
3. 告警处置、配置治理、发布执行、回滚记录全链可追溯。

## 8. 第六批：BFF / HMI 交付收口

范围：

1. [BMS_Work_Package_12_BFF_HMI.md](workPackages/wp12_bff_hmi/BMS_Work_Package_12_BFF_HMI.md)。
2. 依赖前五批稳定输出。

目标：

1. 打通 dashboard、alert_stream 和前端重连恢复。
2. 让主业务、运维告警、前端展示形成完整可演示闭环。

通过标准：

1. Formal 11 的最小契约测试组通过。
2. BFF 视图保持只读聚合语义。
3. HMI 不直接订阅后端 DDS 业务 topic。

## 9. 剩余工作包线性推荐顺序

若按单线程顺序持续推进，建议按如下次序领取剩余工作包：

1. wp02_taskmgmt
2. wp05_enhanceunit
3. wp06_commnet
4. wp04_resmgmt
5. wp03_sitmgmt
6. wp01_battlectrl
7. wp08_knowledgerule
8. wp10_monitorlog
9. wp09_authaudit
10. wp11_opsmgmt
11. wp13_versiondeploy
12. wp12_bff_hmi

排序原则：

1. 先做主业务入口和桥接底座。
2. 再做资源与态势权威对象。
3. 再做交战闭环与规则辅助。
4. 最后做观测、审计、运维、发布和界面聚合域。

## 10. 每批的统一退出条件

1. 本批涉及的工作包已具备最小正常样例、异常样例和边界负样例。
2. 本批涉及的正式 ICD 契约测试已通过。
3. 本批涉及的主要联调链路已完成至少 1 次记录化联调。
4. 执行索引、工作包和相关治理文档已同步更新。

## 11. 阶段完成定义

当以下条件同时满足时，可认为本阶段完成并可进入审查：

1. 工作包体系完整，覆盖主要 Container。
2. 治理基线、契约测试基线、职责边界文档和横向收敛文档齐备。
3. 执行索引和分批实施计划已形成。
4. 导航文档和交付包清单均已登记上述文档。
5. 当前批次及其前置批次的测试资产骨架已经落地到 testAssets。
