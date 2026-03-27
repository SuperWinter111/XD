# BMS 工作包 03 SitMgmt

本文档是态势管理分系统的可执行工作包，供软件工程师或 agent 直接领取并进入实现。

## 1. 基本信息

1. 分系统名称：SitMgmt。
2. 负责人类型：软件工程师或 agent。
3. 对应 Container：plantumlC4/C4_L2_Container.puml 中态势管理分系统。
4. 对应 Component 图：plantumlC4/C4_L3_Component_04_SitMgmt.puml。
5. 对应 Code 图：plantumlC4/Code_04_SitMgmt.puml。
6. 对应正式 ICD：BMS_ICD_Formal_04、05、06、09。

## 2. 目标范围

1. 接收边缘感知、外部态势和仿真真值输入，形成稳定的事实观测对象。
2. 生成 FusedTrack、ThreatAssessment、SituationSnapshot 等态势权威对象。
3. 吸收 KnowledgeRule 的 RecommendationItem 作为辅助输入，但不让推荐替代权威态势对象。
4. 向 BattleCtrl、BFF 和其它消费者提供统一的态势输出语义。
5. 支撑主业务闭环中的态势驱动交战输入场景。

不包含：

1. 交战计划生成与任务分解。
2. 平台侧传感器驱动实现。
3. 推理规则引擎本体实现。

## 3. 对象边界

### 3.1 主拥有对象

1. FusedTrack。
2. ThreatAssessment。
3. SituationSnapshot。
4. SituationSummaryReport。
5. CriticalAlert。

### 3.2 只读消费对象

1. RawTargetInput。
2. 外部态势输入对象。
3. TargetTruth。
4. RecommendationItem。

### 3.3 禁止越权修改

1. 不得把态势对象直接改写成任务或计划对象。
2. 不得把 RecommendationItem 伪装成 FusedTrack 或 ThreatAssessment。
3. 不得让仿真真值冒充真实融合结果。
4. 不得越权直接发布平台执行命令。

## 4. topic 责任

### 4.1 发布 topic

| topic | payload | 触发条件 | 下游 |
| --- | --- | --- | --- |
| bms/core/situation/fused_track | FusedTrack | 感知关联与融合完成 | BattleCtrl, BFF |
| bms/core/situation/threat/assessed | ThreatAssessment | 威胁评估完成 | BattleCtrl, BFF |
| bms/core/situation/snapshot | SituationSnapshot | 周期性快照或关键态势变化 | BFF, MonitorLog |
| bms/core/situation/summary_generated | SituationSummaryReport | 形成阶段性态势摘要 | HMI-BFF |
| bms/core/situation/critical_event | CriticalAlert | 发现高优先级态势告警 | BattleCtrl, MonitorLog |

### 4.2 订阅 topic

| topic | payload | 上游 | 消费动作 |
| --- | --- | --- | --- |
| edge.payload/perception/* | RawTargetInput | EnhanceUnit | 接收边缘感知原始输入 |
| bms/simulation/payload/target_truth | TargetTruth | Simulation | 校核仿真场景与融合效果 |
| bms/core/knowledge/inference/recommended | RecommendationItem | KnowledgeRule | 补充推理建议与解释 |
| ext.analysis.* | 外部态势分析对象 | 外部接口管理 | 汇入外部态势来源 |

## 5. 模块拆分

| 模块 | 责任 | 输入 | 输出 |
| --- | --- | --- | --- |
| PerceptionIngestService | 接收与标准化感知输入 | RawTargetInput, 外部态势输入 | 标准化观测 |
| TrackAssociationService | 完成轨迹关联与目标归并 | 标准化观测 | 轨迹候选 |
| AttributeFusionService | 形成 FusedTrack 与特征快照 | 轨迹候选 | FusedTrack |
| ThreatAssessmentService | 生成威胁评估与理由 | FusedTrack, RecommendationItem | ThreatAssessment |
| SituationSummaryService | 输出快照、摘要和关键告警 | ThreatAssessment, FusedTrack | SituationSnapshot, CriticalAlert |

## 6. 实施步骤

1. 先实现感知输入归一与目标关联主链。
2. 打通 fused_track 输出，形成可消费的事实观测对象。
3. 接入 ThreatAssessmentService，补齐 threat/assessed 主链。
4. 接入 RecommendationItem 与仿真真值输入，明确辅助输入边界。
5. 最后补齐 summary_generated 与 critical_event，完成界面和联调支持。

## 7. 测试与验收

### 7.1 必备样例

1. 正常样例：raw target -> fused_track -> threat_assessed。
2. 异常样例：观测不足、来源冲突或置信度下降时的降级输出。
3. 边界样例：RecommendationItem 不替代 ThreatAssessment，TargetTruth 不冒充真实态势。

### 7.2 契约测试

1. FusedTrack 与 ThreatAssessment 语义必须符合 Formal 04。
2. TargetFeatureSnapshot 与 TargetStatus 扩展字段必须符合 Formal 05。
3. RecommendationItem 只能作为辅助输入，必须符合 Formal 06。
4. 仿真真值输入的引用边界必须符合 Formal 09。

### 7.3 完成定义

1. Code_04_SitMgmt 中的主链模块已落到实现骨架。
2. fused_track 与 threat_assessed 两条主链可验证。
3. 与 BattleCtrl、KnowledgeRule、EnhanceUnit 的联调项已映射到联调矩阵。
4. 已准备主业务闭环场景 E 的样例与验收记录。

## 8. 风险与待决项

1. 风险：感知来源异构时，特征归一与轨迹关联规则容易积累过多特殊分支。
2. 风险：若 RecommendationItem 与 ThreatAssessment 边界实现不清，容易出现推荐越权。
3. 待决项：SituationSummaryReport 的展示粒度是否需要与 BFF 视图契约进一步联动收敛。
