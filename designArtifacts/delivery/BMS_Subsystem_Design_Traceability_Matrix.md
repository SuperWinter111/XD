# BMS 分系统设计追踪矩阵

本文档用于把需求、Container、Component、Code、正式 ICD、topic 职责和联调边界收敛到统一追踪矩阵，作为后续分系统负责人领取设计包的总入口。

## 1. 使用方式

1. 每个分系统负责人先定位自己对应的 Container。
2. 再查看对应的 Component 图与 Code 图。
3. 再阅读本分系统负责实现或必须遵守的正式 ICD。
4. 最后按联调矩阵确认上下游依赖、mock 需求与验收范围。

## 2. 追踪矩阵

| 分系统 | Container / 主容器 | Component 图 | Code 图 | 主负责正式 ICD | 重点发布主题 | 重点订阅主题 | 主要联调对象 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| HMI / API Gateway / BFF | plantumlC4/C4_L2_Container.puml 中 HMI 与 API Gateway / BFF | plantumlC4/C4_L3_Component_02_HMI.puml | 无独立 code 图，聚合对象见 plantumlC4/Code_09_DomainObjectMap.puml | 11 | bms/ui/push/dashboard, bms/ui/push/alert_stream | task.*, sit.*, battle.*, res.*, ops.* | TaskMgmt, SitMgmt, BattleCtrl, ResMgmt, MonitorLog |
| 外部接口管理 | plantumlC4/C4_L2_Container.puml 中外部接口管理 | plantumlC4/C4_L3_Component_01_ExtInterface.puml | 无 | 02, 04 | ext.command.*, ext.plan.*, ext.analysis.* | sit.report.*, task.report.* | TaskMgmt, SitMgmt |
| TaskMgmt | 任务管理分系统 | plantumlC4/C4_L3_Component_03_TaskMgmt.puml | plantumlC4/Code_02_TaskMgmt.puml | 02, 03, 06 | bms/core/command/task/* | ext.command.*, bms/core/execution/*, bms/core/command/resource/allocation_committed | BattleCtrl, ResMgmt, SitMgmt |
| SitMgmt | 态势管理分系统 | plantumlC4/C4_L3_Component_04_SitMgmt.puml | plantumlC4/Code_04_SitMgmt.puml | 04, 05, 06, 09 | bms/core/situation/* | edge.payload/perception/*, bms/simulation/payload/target_truth, bms/core/knowledge/inference/recommended | BattleCtrl, KnowledgeRule, HMI-BFF |
| BattleCtrl | 交战管控分系统 | plantumlC4/C4_L3_Component_05_BattleCtrl.puml | plantumlC4/Code_03_BattleCtrl.puml | 01, 02, 03, 04, 06, 07 | bms/core/command/battle/* | bms/core/situation/*, bms/core/resource/state_snapshot, bms/core/ops/comm/link_degraded | TaskMgmt, ResMgmt, EnhanceUnit, SitMgmt |
| ResMgmt | 资源管理分系统 | plantumlC4/C4_L3_Component_06_ResMgmt.puml | plantumlC4/Code_05_ResMgmt.puml | 03, 07 | bms/core/resource/state_snapshot, bms/core/command/resource/allocation_committed | edge.platform.*, bms/core/command/resource/allocation_requested, bms/core/ops/comm/link_quality | TaskMgmt, BattleCtrl, CommNet |
| MsgService | 消息服务 | plantumlC4/C4_L3_Component_07_MsgService.puml | plantumlC4/Code_06_MsgService.puml | 08 | bms/core/ops/msg/* | 系统级登记与订阅关系 | 全部分系统 |
| KnowledgeRule | 知识与规则 | plantumlC4/C4_L3_Component_08_KnowledgeRule.puml | plantumlC4/Code_07_KnowledgeRule.puml | 06 | bms/core/knowledge/inference/recommended | bms/core/knowledge/inference/requested, bms/core/situation/target/feature_snapshot | SitMgmt, TaskMgmt, BattleCtrl |
| DbMgmt | 数据库管理 | plantumlC4/C4_L3_Component_09_DbMgmt.puml | plantumlC4/Code_10_DbMgmt.puml | 以 schema 和 ownership 约束为主 | 无强制 DDS 主主题 | 跨域持久化对象 | 各业务 owner |
| CommNet | 通信组网 | plantumlC4/C4_L3_Component_10_CommNet.puml | plantumlC4/Code_08_CommNet.puml | 07 | bms/core/ops/comm/* | edge.platform/telemetry/link_state, edge.raw.* | ResMgmt, BattleCtrl, MonitorLog |
| EnhanceUnit | 协同增强单元 | plantumlC4/C4_L3_Component_11_EnhanceUnit.puml | plantumlC4/Code_01_EnhanceUnit.puml | 01, 09 | bms/edge/platform/*, bms/edge/payload/* | bms/core/command/battle/*, bms/simulation/* | BattleCtrl, SitMgmt, ResMgmt |
| AuthAudit | 权限与安全审计 | plantumlC4/C4_L3_Component_12_AuthAudit.puml | 无 | 10 | bms/core/ops/sec/audit_event | 安全事件与用户动作 | MonitorLog, OpsMgmt |
| MonitorLog | 监控与日志 | plantumlC4/C4_L3_Component_13_MonitorLog.puml | 无 | 10 | bms/core/ops/monitor/* | comm.*, sec.*, msg.* | OpsMgmt, HMI-BFF |
| OpsMgmt | 运维管理 | plantumlC4/C4_L3_Component_14_OpsMgmt.puml | 无 | 10 | ops.config.*, ops.job.*, ops.selfcheck.* | bms/core/ops/monitor/*, deploy.* | MonitorLog, AuthAudit |
| Version / Deploy | 版本与部署 | plantumlC4/C4_L3_Component_15_VersionDeploy.puml | 无 | 10 | bms/core/ops/deploy/release_event | 运维与监控相关事件 | OpsMgmt, MonitorLog |
| Simulation | 仿真与训练 | C4_L1 与 Deployment / Supplementary 图 | 无单独 code 图 | 09 | bms/simulation/* | battle.command.*, task.plan.* | EnhanceUnit, SitMgmt, BattleCtrl |

## 3. 使用结论

1. 正式 ICD 负责定义跨分系统交换语义。
2. Component 图负责定义容器内部职责拆分。
3. Code 图负责定义实现骨架与对象落点。
4. 本矩阵负责把三者映射到具体负责人可执行的开发范围。
