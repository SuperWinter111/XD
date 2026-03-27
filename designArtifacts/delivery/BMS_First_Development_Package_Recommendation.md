# BMS 首个开发包推荐与工程级 ICD 启动策略

本文档用于明确两个问题：

1. 哪个 workPackage 最适合作为首个开发包。
2. 工程级 ICD 应在什么时机启动设计与冻结。

## 1. 首个开发包推荐结论

推荐首个开发包：wp07_msgservice。

对应文档入口：

1. [workPackages/wp07_msgservice/BMS_Work_Package_07_MsgService.md](workPackages/wp07_msgservice/BMS_Work_Package_07_MsgService.md)
2. [workPackages/wp07_msgservice/ICD_Package.md](workPackages/wp07_msgservice/ICD_Package.md)
3. [workPackages/wp07_msgservice/Payload_Checklist.md](workPackages/wp07_msgservice/Payload_Checklist.md)
4. [workPackages/wp07_msgservice/AGENT_HANDOFF.md](workPackages/wp07_msgservice/AGENT_HANDOFF.md)

## 2. 为什么选 MsgService 作为首发包

选择 wp07_msgservice 的原因如下：

1. 对应正式 ICD 单一，只依赖 Formal 08，契约范围最集中。
2. 对象边界清晰，TopicDefinition、SubscriptionBinding、MessageEnvelope、DeliveryReceipt、DeadLetterRecord 已稳定。
3. 不承担业务对象语义裁定，业务争议最少。
4. 测试样例已齐备，正常、异常、边界三类样例都已存在。
5. 其代码骨架对后续各业务工作包都有复用价值，因为其他分系统都会经过消息治理链路。
6. 与 CommNet 的边界已单独文档化，外围职责冲突风险较低。

不优先选择 wp02_taskmgmt 的原因：

1. 它直接处于主业务闭环中心，跨 BattleCtrl、ResMgmt、KnowledgeRule 的耦合更高。
2. 容易在首个开发包阶段把问题带入业务语义争议，而不是先稳定工程骨架。

不优先选择 wp06_commnet 的原因：

1. 它虽然 Formal 07 单一，但对平台遥测、网络设备和拓扑变化输入依赖更重。
2. 首发包更适合选择输入抽象更稳定、对外部环境依赖更少的工程治理包。

## 3. 开发工程是否应独立文件夹维护

结论：应独立文件夹维护，但不建议独立仓库。

推荐方式：

1. 仍在当前仓库内开发。
2. 为首个开发包建立独立工程目录。
3. 工程目录与设计工作包目录分离。

建议目录形态如下：

1. implementation/wp07_msgservice/
2. implementation/wp07_msgservice/src/
3. implementation/wp07_msgservice/tests/
4. implementation/wp07_msgservice/mocks/
5. implementation/wp07_msgservice/README.md

这样做的原因：

1. 设计资产仍保留在 designArtifacts/delivery/workPackages 下。
2. 实现资产集中在 implementation 目录，避免设计文件夹被代码污染。
3. 每个 workPackage 后续都可以沿用同一模式扩展。

## 4. 工程级 ICD 什么时候开始设计

结论：不是在代码骨架和测试骨架都完成之后才开始，而是应在代码骨架启动时同步开始。

更准确地说，工程级 ICD 应分 3 个阶段推进。

### 4.1 阶段 A：开发前冻结最小接口骨架

在开始写代码骨架前，至少先冻结：

1. topic 名称。
2. payload 名称。
3. owner。
4. 关键主键字段。
5. trace_id 贯通规则。

这一步不需要完整工程级 ICD，但必须有最小冻结接口定义。

### 4.2 阶段 B：代码骨架阶段同步补工程级 ICD 骨架

当开始实现代码骨架时，应同步开始工程级 ICD 的第一版。

此时至少补齐：

1. 发布方与订阅方。
2. payload 类型。
3. 字段表初版。
4. 触发条件。
5. QoS 约束。
6. 重试与失败路径。
7. 正常、异常、边界样例。

也就是说：

1. 代码骨架。
2. 测试骨架。
3. 工程级 ICD 骨架。

这三者应并行推进，而不是串行等待。

### 4.3 阶段 C：进入跨包联调前冻结工程级 ICD v1

在准备跨工作包联调之前，工程级 ICD 必须补齐到可冻结状态，至少包括：

1. 字段单位。
2. 字段范围。
3. 精度。
4. 必填性。
5. 状态机约束。
6. 异常码或失败原因。
7. 版本兼容策略。

这时工程级 ICD 才进入真正可联调状态。

## 5. 对首个开发包 MsgService 的具体建议

对于 wp07_msgservice，我建议按以下顺序推进：

1. 先建立 implementation/wp07_msgservice/ 独立工程目录。
2. 先落 TopicRegistry、SubscriptionRegistry、EnvelopeRouter 三个主模块骨架。
3. 同步编写 Formal 08 对应的工程级 ICD 初版。
4. 再补 DeliveryTracker 与 RetryAndDeadLetterService。
5. 最后补 MonitorLog 观测接线与版本兼容适配。

## 6. 一句话原则

工程级 ICD 不是代码做完后的说明书，而应是从代码骨架启动时就并行维护的接口约束文件。

## 7. 当前默认技术基线

结合当前仓库状态与用户偏好，首个开发包默认采用：

1. 编程语言：C++20。
2. 构建系统：CMake。
3. 工程目录：implementation/wp07_msgservice/。
4. schema 主来源：proto/bms/schema/message.proto。
5. 技术选型总基线见 [BMS_Technology_Stack_Baseline.md](BMS_Technology_Stack_Baseline.md)。
