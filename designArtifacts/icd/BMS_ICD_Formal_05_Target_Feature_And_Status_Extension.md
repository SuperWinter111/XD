# BMS 正式 ICD 专题 05 目标特征与目标状态扩展

本文档定义在 FusedTrack 与 ThreatAssessment 之外，如何以独立扩展对象承载目标观察特征与目标状态，避免把融合航迹对象扩展成跨层杂糅的大对象。

## 1. 文档定位

本文档覆盖以下内容：

1. TargetFeatureSnapshot 的正式语义与 topic 绑定。
2. TargetStatus 的正式语义与 topic 绑定。
3. 与 FusedTrack、ThreatAssessment 的边界关系。
4. 从旧系统 ICD 吸收哪些颗粒度，拒绝哪些旧语义。

本文档来源包括：

1. designArtifacts/icd/BMS_ICD_Formal_04_Situation_And_Threat.md
2. designArtifacts/review/OldSys_ICD_Reference_Assessment.md
3. oldSysReference/bms_type.txt
4. proto/bms/schema/situation.proto
5. designArtifacts/contracts/BMS_DDS_Topic_Catalog.md

## 2. 设计原则

1. FusedTrack 继续只承载融合航迹与基础运动学观测。
2. ThreatAssessment 继续只承载威胁判断。
3. 目标特征与目标状态通过独立扩展对象表达。
4. 旧系统字段只作为颗粒度参考，不照搬旧目标模型。

## 3. Topic 绑定

| topic | payload | 发布方 | 订阅方 | QoS |
| --- | --- | --- | --- | --- |
| bms/core/situation/target/feature_snapshot | bms.schema.situation.TargetFeatureSnapshot | SitMgmt | BattleCtrl, HMI-BFF, KnowledgeRule | QOS-ALERT |
| bms/core/situation/target/status_updated | bms.schema.situation.TargetStatus | SitMgmt | BattleCtrl, HMI-BFF | QOS-ALERT |

说明：

1. 这两个对象都通过 track_id 回溯到 FusedTrack 主链。
2. 它们是扩展对象，不替代 FusedTrack 或 ThreatAssessment。

## 4. TargetFeatureSnapshot

### 4.1 对象职责

TargetFeatureSnapshot 表达的是当前观察到的目标特征快照，而不是知识域中的长期目标画像。

它适合承载：

1. 阵营或敌我属性。
2. 时敏特征。
3. 机动能力。
4. 防护能力。
5. 国家或来源标签。
6. 探测方式与部分观测型能力指标。
7. 长宽高等外形尺寸。

### 4.2 正式 payload

```proto
message TargetFeatureSnapshot {
  CommonHeader header = 1;
  string feature_id = 2;
  string track_id = 3;
  string target_name = 4;
  string target_type = 5;
  string target_source = 6;
  TargetCamp camp = 7;
  TimeSensitivity time_sensitivity = 8;
  TargetMobility mobility = 9;
  ProtectionCapability protection_capability = 10;
  string country_code = 11;
  string detection_method = 12;
  double detection_range_km = 13;
  double horizontal_detection_angle_deg = 14;
  double vertical_detection_angle_deg = 15;
  double weapon_attack_height_m = 16;
  double weapon_attack_distance_km = 17;
  double length_m = 18;
  double width_m = 19;
  double height_m = 20;
}
```

### 4.3 边界说明

1. target_source 当前保留字符串，后续可再收敛为码表或枚举。
2. target_type 当前仍与 FusedTrack 对齐，后续可统一到词表。
3. 该对象是观察或识别快照，不等于 KnowledgeRule 拥有的 TargetFeatureProfile。

## 5. TargetStatus

### 5.1 对象职责

TargetStatus 表达目标的状态更新，尤其是位置口径与毁伤状态口径。

它适合承载：

1. 目标当前坐标系。
2. 目标状态位置。
3. 毁伤状态。

### 5.2 正式 payload

```proto
message TargetStatus {
  CommonHeader header = 1;
  string status_id = 2;
  string track_id = 3;
  string target_source = 4;
  CoordinateSystemType coordinate_system = 5;
  double latitude = 6;
  double longitude = 7;
  double altitude_m = 8;
  DamageStatus damage_status = 9;
}
```

### 5.3 边界说明

1. TargetStatus 不等于 FusedTrack，后者仍是融合航迹主对象。
2. TargetStatus 不等于 EffectReport，后者属于交战效果评估语义。
3. damage_status 是目标状态字段，不是战果结论全文。

## 6. 从旧系统吸收的颗粒度

本专题明确吸收旧系统中的以下颗粒度方向：

1. camp。
2. timeSensitive。
3. mobility。
4. protectionCapability。
5. coordinateSystem。
6. status。
7. 长宽高与探测相关字段。

但不直接照搬以下内容：

1. 旧系统 TargetProperty 全量结构。
2. 旧系统 TargetInfo28 混合对象。
3. 旧系统中与任务方案、威胁判定、修改来源耦合的字段组织方式。

## 7. 与现有正式 ICD 的关系

### 7.1 与 Formal 04 的关系

1. Formal 04 定义态势主链边界。
2. 本专题定义主链外的目标特征与目标状态扩展对象。

### 7.2 与 KnowledgeRule 的关系

1. TargetFeatureSnapshot 是 SitMgmt 的观察结果。
2. TargetFeatureProfile 是 KnowledgeRule 的知识对象。
3. KnowledgeRule 可以消费 TargetFeatureSnapshot，但不能因此丢失知识域 own 的画像边界。

## 8. 下一阶段建议

1. 为 target_source 建立标准码表或枚举。
2. 为 detection_method 建立标准词表。
3. 视需要补充电磁和红外特征的结构化子对象，而不是继续堆叠扁平字段。
4. 继续推进 ThreatAssessment.reason_codes 或 rule_refs 的结构化。
