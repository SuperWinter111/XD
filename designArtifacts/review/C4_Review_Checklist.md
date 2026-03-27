# BMS C4 模型审查清单

本清单用于在架构评审、里程碑审查和 Code Diagram 设计前，对当前 C4 模型进行统一审查。

## 一、审查顺序

1. 先看 System Landscape。
2. 再看 Context Diagram。
3. 再看唯一主 Container Diagram。
4. 再看各 Container 的 Component Diagram。
5. 再看 Dynamic Diagram。
6. 再看 Deployment View。

## 二、System Landscape 审查点

检查文件：[plantumlC4/C4_L0_Landscape.puml](plantumlC4/C4_L0_Landscape.puml)

1. 系统边界是否完整。
2. 外部系统是否齐全且无重复。
3. 内部分系统命名是否统一为“XX分系统”。
4. 是否把部署细节或仿真内部结构错误放进全景图。

## 三、Context Diagram 审查点

检查文件：[plantumlC4/C4_L1_Context.puml](plantumlC4/C4_L1_Context.puml)

1. 用户角色是否齐全。
2. BMS 与外部系统的关系是否正确。
3. 无人平台任务系统是否保持统一语义。
4. 实验室数字模型是否没有破坏主上下文边界。
5. 协议说明是否保持在关系描述层，而不是内部实现层。

## 四、主 Container Diagram 审查点

检查文件：[plantumlC4/C4_L2_Container.puml](plantumlC4/C4_L2_Container.puml)

1. 是否只有一张主 Container Diagram。
2. 人机交互层是否只保留一个“人机交互分系统”容器。
3. 各容器粒度是否一致。
4. 业务容器与平台服务容器边界是否稳定。
5. 是否存在明显不合理的跨层依赖。
6. 容器命名、说明和关系方向是否统一。

## 五、Component Diagram 审查点

建议优先顺序：

1. [plantumlC4/C4_L3_Component_11_EnhanceUnit.puml](plantumlC4/C4_L3_Component_11_EnhanceUnit.puml)
2. [plantumlC4/C4_L3_Component_03_TaskMgmt.puml](plantumlC4/C4_L3_Component_03_TaskMgmt.puml)
3. [plantumlC4/C4_L3_Component_04_SitMgmt.puml](plantumlC4/C4_L3_Component_04_SitMgmt.puml)
4. [plantumlC4/C4_L3_Component_05_BattleCtrl.puml](plantumlC4/C4_L3_Component_05_BattleCtrl.puml)
5. [plantumlC4/C4_L3_Component_06_ResMgmt.puml](plantumlC4/C4_L3_Component_06_ResMgmt.puml)
6. [plantumlC4/C4_L3_Component_02_HMI.puml](plantumlC4/C4_L3_Component_02_HMI.puml)
7. [plantumlC4/C4_L3_Component_07_MsgService.puml](plantumlC4/C4_L3_Component_07_MsgService.puml)
8. [plantumlC4/C4_L3_Component_10_CommNet.puml](plantumlC4/C4_L3_Component_10_CommNet.puml)

每张图都检查：

1. 组件职责是否单一。
2. 是否出现循环依赖。
3. 是否把外部容器内部细节错误引入本图。
4. 是否保留后续 Code Diagram 的清晰边界。

## 六、Dynamic Diagram 审查点

检查文件：

1. [plantumlC4/C4_Dynamic_01_CommandChain.puml](plantumlC4/C4_Dynamic_01_CommandChain.puml)
2. [plantumlC4/C4_Dynamic_02_SensingChain.puml](plantumlC4/C4_Dynamic_02_SensingChain.puml)
3. [plantumlC4/C4_Dynamic_03_KillChain.puml](plantumlC4/C4_Dynamic_03_KillChain.puml)
4. [plantumlC4/C4_Dynamic_04_ReplanRecovery.puml](plantumlC4/C4_Dynamic_04_ReplanRecovery.puml)

检查项：

1. 动态流程是否能被主 Container Diagram 支撑。
2. 是否存在动态图中出现、但静态图没有的依赖。
3. 关键消息链是否闭环。
4. 是否遗漏重要确认、执行反馈或评估环节。
5. 是否完整表达计划调整、任务重构与人工介入的回退闭环。

## 七、Deployment View 审查点

检查文件：

1. [plantumlC4/C4_Deployment_01_LabSingleServer.puml](plantumlC4/C4_Deployment_01_LabSingleServer.puml)
2. [plantumlC4/C4_Deployment_02_Engineering_DualNano.puml](plantumlC4/C4_Deployment_02_Engineering_DualNano.puml)

检查项：

1. 实验室部署与工程部署是否采用同一业务语义。
2. 双 Nano 分工是否清晰。
3. 边缘与核心职责是否一致。
4. 数字模型是否只作为实验室实现形态出现。
5. DDS 桥接和跨板通信是否清晰。

## 八、审查结论格式

每次审查建议按以下格式记录：

1. 发现的问题。
2. 影响范围。
3. 建议修改图文件。
4. 是否影响后续 Code Diagram。
5. 是否影响 agent 并行分工。
