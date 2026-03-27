# BMS 正式 ICD 专题 04 态势与威胁

本文档定义态势管理分系统向交战管控、任务管理、HMI 提供融合航迹与威胁评估结果时的正式 ICD 约束。

本文档以当前 BMS 语义边界为主，仅吸收旧系统 ICD 中对目标属性颗粒度、量纲口径、状态口径的有益部分，不继承旧系统目标模型。

## 1. 文档定位

本文档重点覆盖以下内容：

1. FusedTrack 的正式语义与 topic 绑定。
2. ThreatAssessment 的正式语义与 topic 绑定。
3. 融合航迹与威胁评估之间的主链关系。
4. 可直接进入当前正式 ICD 的目标属性颗粒度。
5. 不允许混入当前正式对象的旧系统语义。

本文档来源包括：

1. designArtifacts/contracts/BMS_DDS_Topic_Catalog.md
2. designArtifacts/contracts/BMS_Code_Interface_Object_Catalog.md
3. designArtifacts/delivery/BMS_Integration_Matrix.md
4. designArtifacts/review/OldSys_ICD_Reference_Assessment.md
5. proto/bms/schema/situation.proto

## 2. 闭环范围

本专题覆盖以下主链：

1. Raw target 输入进入 SitMgmt。
2. SitMgmt 输出 FusedTrack。
3. SitMgmt 基于融合航迹输出 ThreatAssessment。
4. BattleCtrl 与 HMI 消费态势与威胁结果。

本专题不覆盖：

1. 原始点迹级算法。
2. 传感器图像与视频流本体。
3. 目标真值或裁决真值对象。
4. 交战计划生成逻辑本体。

## 3. Topic 绑定

| topic | payload | 发布方 | 订阅方 | QoS |
| --- | --- | --- | --- | --- |
| bms/core/situation/track/fused_track | bms.schema.situation.FusedTrack | SitMgmt | BattleCtrl, HMI-BFF | QOS-TRACK |
| bms/core/situation/threat/assessed | bms.schema.situation.ThreatAssessment | SitMgmt | BattleCtrl, HMI-BFF | QOS-ALERT |
| bms/core/situation/track/track_lost | 航迹丢失事件 | SitMgmt | BattleCtrl, HMI-BFF | QOS-ALERT |

说明：

1. FusedTrack 是融合结果，不是原始目标输入。
2. ThreatAssessment 是评估结果，不是交战命令。
3. track_lost 是航迹生命周期事件，不替代 FusedTrack 删除语义。

## 4. 核心对象语义

### 4.1 FusedTrack

FusedTrack 是态势管理分系统的权威融合航迹对象。

当前正式 payload 结构如下：

```proto
message FusedTrack {
  CommonHeader header = 1;
  string track_id = 2;
  string target_type = 3;
  double latitude = 4;
  double longitude = 5;
  double altitude_m = 6;
  double speed_mps = 7;
  double heading_deg = 8;
  double confidence = 9;
  repeated string source_refs = 10;
}
```

语义约束：

1. track_id 是融合航迹唯一标识。
2. target_type 当前保留字符串，但应受标准词表控制。
3. confidence 必须归一到 [0, 1]。
4. latitude、longitude、altitude_m 是统一空间位置口径。
5. FusedTrack 允许只提供当前稳定可得的运动学字段，不允许伪造缺失值。

### 4.2 ThreatAssessment

ThreatAssessment 是基于 FusedTrack 及其上下文形成的威胁评估结果对象。

当前正式 payload 结构如下：

```proto
message ThreatAssessment {
  CommonHeader header = 1;
  string threat_id = 2;
  string track_id = 3;
  int32 threat_level = 4;
  int32 priority_rank = 5;
  string threat_reason = 6;
}
```

语义约束：

1. threat_id 是评估对象唯一标识。
2. track_id 是 ThreatAssessment 回溯到目标链的唯一主线。
3. threat_level 表示威胁强弱。
4. priority_rank 表示排序优先级。
5. threat_reason 当前允许解释文本，但不能替代结构化理由编码的后续演进。

## 5. FusedTrack 与 ThreatAssessment 的边界

### 5.1 FusedTrack 关注事实观测

FusedTrack 主要表达：

1. 目标在哪里。
2. 目标在怎么运动。
3. 这条融合结果有多可信。
4. 它来自哪些上游源。

### 5.2 ThreatAssessment 关注分析判断

ThreatAssessment 主要表达：

1. 当前目标有多危险。
2. 相对于其它目标排第几。
3. 为什么得出这个威胁判断。

### 5.3 禁止事项

1. 不得把 ThreatAssessment 的威胁等级反向写回 FusedTrack 作为事实字段。
2. 不得把 FusedTrack 直接当作交战指令。
3. 不得把 ThreatAssessment 直接当作 BattlePlan 或火力授权对象。

## 6. 吸收旧系统 ICD 后的颗粒度定位

根据旧系统 ICD 参考评估，当前态势正式 ICD 可吸收以下目标属性颗粒度方向，但必须以扩展或后续结构化字段方式进入：

1. 阵营或敌我属性。
2. 时敏特征。
3. 机动能力。
4. 防护能力。
5. 电磁辐射或红外特征。
6. 目标毁伤状态。
7. 目标坐标系统口径。

当前阶段的落地原则：

1. 这些内容暂不直接塞进现有 FusedTrack 主对象，避免把融合对象变成目标知识大杂烩。
2. 可以在后续通过 TargetFeatureProfile、TargetStatus 扩展对象或 ThreatAssessment 结构化理由对象承载。
3. 旧系统中的 camp、timeSensitive、protectionCapability 只作为字段候选方向，不直接照搬枚举值。

## 7. 工程字段口径

### 7.1 空间与运动字段

1. latitude：单位 deg，建议精度 1e-7。
2. longitude：单位 deg，建议精度 1e-7。
3. altitude_m：单位 m，建议精度 0.1。
4. speed_mps：单位 m/s，建议精度 0.1。
5. heading_deg：单位 deg，建议精度 0.1。

### 7.2 评估字段

1. threat_level 建议约束到固定等级区间，例如 [0, 10]。
2. priority_rank 应是相对排序值，不应与 threat_level 混用。
3. threat_reason 当前是文本解释，后续应增加 reason_codes 或 rule_refs。

## 8. 生命周期与刷新建议

### 8.1 FusedTrack

1. 推荐以周期触发和状态变化触发结合方式发布。
2. 推荐 QoS 为 QOS-TRACK。
3. 推荐刷新率 1Hz 到 10Hz，具体取决于目标机动性与上游融合频率。

### 8.2 ThreatAssessment

1. 推荐以变化触发为主，必要时低频周期刷新。
2. 推荐 QoS 为 QOS-ALERT。
3. 推荐在 threat_level、priority_rank 或主要 threat_reason 发生变化时发布。

## 9. BattleCtrl 与 HMI 的消费原则

### 9.1 BattleCtrl

BattleCtrl 可以基于 FusedTrack 与 ThreatAssessment：

1. 进行目标排序。
2. 进行战术匹配。
3. 进行计划候选筛选。

BattleCtrl 不得：

1. 私自发布权威 ThreatAssessment 覆盖 SitMgmt。
2. 把交战判决结果回写成态势主对象。

### 9.2 HMI

HMI 应区分展示：

1. 观测事实层。
2. 评估判断层。

禁止把 threat_level 与 target_type 混排后当成同一类基础字段展示。

## 10. 与旧系统接口的映射启发

旧系统中以下内容适合仅作为当前专题的映射启发：

1. targetSource 可启发后续 source 质量标签设计。
2. camp 可启发后续敌我属性设计。
3. timeSensitive 可启发后续时敏目标标签设计。
4. protectionCapability 可启发后续防护能力标签设计。
5. target status 可启发后续毁伤状态对象设计。

这些字段不应直接回填到当前 FusedTrack/ThreatAssessment 主对象，除非后续专门完成结构化设计。

## 11. 下一阶段建议

建议下阶段优先补以下内容：

1. 对 target_type 建立标准词表或枚举方案。
2. 为 ThreatAssessment 增加 rule_refs 或 reason_codes。
3. 设计独立的 TargetStatus 或 TargetFeatureProfile 扩展对象。
4. 统一态势侧 topic 命名与字段样表口径。
