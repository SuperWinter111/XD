# BMS 分系统执行手册

本文档用于约束分系统负责人如何从设计资料进入实现、mock、契约测试和联调。这里的分系统负责人既可以是软件工程师，也可以是执行编码任务的 agent。

## 1. 适用对象

1. 人类软件工程师。
2. 具备代码实现、测试与文档更新能力的 agent。

两者在交付责任上没有区别，差别只体现在执行方式，不体现在完成标准。

## 2. 标准执行顺序

1. 阅读 [BMS_Subsystem_Design_Traceability_Matrix.md](designArtifacts/delivery/BMS_Subsystem_Design_Traceability_Matrix.md)，确认自己对应的分系统边界。
2. 阅读 [BMS_Owner_Rule_Baseline.md](designArtifacts/delivery/BMS_Owner_Rule_Baseline.md) 与 [BMS_Completion_Definition.md](designArtifacts/delivery/BMS_Completion_Definition.md)，确认 ownership 和完成标准。
3. 如本次任务涉及公共接口调整，再阅读 [BMS_Change_Governance.md](designArtifacts/delivery/BMS_Change_Governance.md)。
4. 阅读对应的 Container、Component、Code 图，确认内部模块骨架。
5. 阅读对应正式 ICD，确认跨分系统语义边界。
6. 阅读 [BMS_Contract_Test_Baseline.md](designArtifacts/delivery/BMS_Contract_Test_Baseline.md)，确认本分系统至少必须交的契约测试集。
7. 阅读 [BMS_Execution_Index.md](designArtifacts/delivery/BMS_Execution_Index.md)，确认本工作包对应的 ICD、测试组与联调场景。
8. 阅读 [BMS_Phased_Implementation_And_Integration_Plan.md](designArtifacts/delivery/BMS_Phased_Implementation_And_Integration_Plan.md)，确认当前任务所在实施批次。
9. 阅读 [BMS_Integration_Matrix.md](designArtifacts/delivery/BMS_Integration_Matrix.md)，确认上游输入、下游输出与联调链路。
10. 阅读 [BMS_Core_Battle_Loop_Integration_Scenarios.md](designArtifacts/delivery/BMS_Core_Battle_Loop_Integration_Scenarios.md)，确认主业务闭环优先联调路径。
11. 产出本分系统的内部模块拆分、topic producer / consumer 清单、mock 方案和契约测试方案。
12. 完成实现后，先过单体验证，再进入系统联调。

## 3. 每个负责人必须产出的最小结果

每个分系统负责人至少必须交付：

1. 代码目录骨架与模块职责说明。
2. topic 发布清单与订阅清单。
3. payload 样例：正常样例、异常样例各至少 1 套。
4. mock 组件或 mock 数据方案。
5. 契约测试清单。
6. 联调入口说明。
7. 风险清单与未决问题清单。
8. 与主业务闭环联调场景的映射关系。

## 4. 标准工作流

### 4.1 设计落图

负责人必须先回答 4 个问题：

1. 本分系统拥有哪些主对象。
2. 本分系统只消费哪些外部对象。
3. 本分系统哪些行为通过同步接口完成。
4. 本分系统哪些行为通过 DDS topic 完成。

### 4.2 实现准备

负责人必须形成以下清单：

1. 模块清单。
2. 领域对象清单。
3. 外部依赖清单。
4. 订阅 topic 清单。
5. 发布 topic 清单。
6. 测试样例清单。

### 4.3 契约验证

负责人必须验证：

1. topic 名称与 DDS 目录一致。
2. payload 结构与 proto 一致。
3. 字段语义与正式 ICD 一致。
4. 自己不越权写入其他 owner 的主数据。

### 4.4 联调准备

负责人必须准备：

1. 正常链路样例。
2. 超时、拒绝、降级、异常链路样例。
3. trace_id 贯穿验证方法。
4. 版本兼容与回退说明。

## 5. 完成定义

一个分系统开发任务只有在下列条件同时满足时才算完成：

1. 组件职责与 Code 图一致。
2. 关键 topic 已实现并可验证收发。
3. 契约测试已覆盖正常路径与异常路径。
4. 上下游联调双方已确认 payload 版本一致。
5. mock 不再替代真实联调链路。
6. 文档已更新到对应 delivery 与 contract 文档。

## 6. 对 agent 的附加约束

1. agent 不得擅自改变容器边界。
2. agent 不得自行新增跨容器同步耦合。
3. agent 修改公共 schema 或正式 ICD 前，必须先回到契约基线文档核对影响范围。
4. agent 不得越权改写主拥有对象，必须遵守 [BMS_Owner_Rule_Baseline.md](designArtifacts/delivery/BMS_Owner_Rule_Baseline.md)。
5. agent 交付结果必须包含可供人类复核的变更说明、测试说明和风险说明。
