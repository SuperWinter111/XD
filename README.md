# BMS 战斗管理系统 — 架构师视角全貌

> **一句话定位：** BMS（Battle Management System）是一套面向无人集群作战的分布式战斗管理平台，承上启下——向上对接上级指控系统，向下指挥无人平台集群，横向协同 KH/KD 友方系统，对内实现从任务受领、计划生成、资源调配、态势感知到交战执行的完整作战闭环。

---

## 目录

1. [系统定位与背景](#1-系统定位与背景)
2. [架构全景（六层容器模型）](#2-架构全景六层容器模型)
3. [十三个分系统速览](#3-十三个分系统速览)
4. [核心业务主链路](#4-核心业务主链路)
5. [关键架构决策](#5-关键架构决策)
6. [数据所有权基线](#6-数据所有权基线)
7. [消息契约与接口体系](#7-消息契约与接口体系)
8. [技术栈基线](#8-技术栈基线)
9. [工程目录结构](#9-工程目录结构)
10. [工作包与开发组织](#10-工作包与开发组织)
11. [测试与验证体系](#11-测试与验证体系)
12. [推荐阅读路径](#12-推荐阅读路径)

---

## 1. 系统定位与背景

### 外部接口关系（C4 L0 景观视图）

```
上级指控系统 ──── 指令/态势 ────►┐
筹划系统     ──── 筹划输入 ────►│
KH 协同系统  ──── 态势共享 ────►│
KD 协同系统  ──── 态势共享 ────►│  ┌──────────────┐  ──► 无人平台任务系统
                                 └─►│  BMS  系 统  │       (飞行/传感/武器)
                                    └──────────────┘
数据分析系统 ◄──── 数据输出 ────────┘
```

### 用户群体

| 类型 | 角色 |
|------|------|
| 业务管理人员 | 指挥决策、态势研判 |
| 业务使用人员 | 任务下达、交战操作 |
| 运维人员 | 日常监控、故障排查、备份恢复 |
| 系统管理员 | 安装、配置、升级 |
| 开发/测试人员 | 部署代码、监控指标、问题诊断 |

---

## 2. 架构全景（六层容器模型）

系统采用 **C4 模型**进行架构描述，容器层（L2）将 BMS 内部划分为六个层次，共 **13 个分系统**：

```
┌───────────────────────────────────────────────────────────┐
│                        BMS 系统边界                        │
│                                                           │
│  L1 外部交互层                                             │
│  ┌──────────────────────────────────────────┐             │
│  │  外部接口管理分系统 (WP00)                │             │
│  └──────────────────────────────────────────┘             │
│                                                           │
│  L2 人机交互层                                             │
│  ┌──────────────────────────────────────────┐             │
│  │  人机交互分系统 / BFF (WP12)              │             │
│  └──────────────────────────────────────────┘             │
│                                                           │
│  L3 业务应用层                                             │
│  ┌──────────┐ ┌──────────┐ ┌──────────┐ ┌──────────┐     │
│  │任务管理  │ │态势管理  │ │交战管控  │ │资源管理  │     │
│  │(WP02)   │ │(WP03)   │ │(WP01)   │ │(WP04)   │     │
│  └──────────┘ └──────────┘ └──────────┘ └──────────┘     │
│                                                           │
│  L4 平台服务层                                             │
│  ┌──────────┐ ┌──────────┐ ┌──────────┐                  │
│  │消息服务  │ │知识规则  │ │数据库    │                  │
│  │(WP07)   │ │(WP08)   │ │管理      │                  │
│  └──────────┘ └──────────┘ └──────────┘                  │
│                                                           │
│  L5 通信与接入层                                           │
│  ┌──────────────────┐ ┌──────────────────────┐           │
│  │  通信组网 (WP06) │ │  协同增强单元 (WP05) │           │
│  └──────────────────┘ └──────────────────────┘           │
│                                                           │
│  L6 运维保障层                                             │
│  ┌────────┐ ┌────────┐ ┌────────┐ ┌────────┐            │
│  │权限审计│ │监控日志│ │运维管理│ │版本部署│            │
│  │(WP09) │ │(WP10) │ │(WP11) │ │(WP13) │            │
│  └────────┘ └────────┘ └────────┘ └────────┘            │
└───────────────────────────────────────────────────────────┘
```

**设计图纸位置：** [`plantumlC4/`](plantumlC4/) 目录包含全套 PlantUML C4 图（L0 景观 → L1 上下文 → L2 容器 → L3 组件 → 动态序列图 → 部署图）。

---

## 3. 十三个分系统速览

### L3 业务核心（四大业务引擎）

| 分系统 | 工作包 | 核心职责 | 关键输出对象 |
|--------|--------|----------|-------------|
| **任务管理** | WP02 | 解析上级指令、任务分解、约束建模、任务全生命周期调度 | `TaskPackage`, `TaskConstraint`, `TaskGraph` |
| **交战管控** | WP01 | 编队管理、交战计划生成、执行监控、效果评估、计划调整 | `BattlePlan`, `EngagementEffectReport` |
| **态势管理** | WP03 | 多源目标融合、威胁评估、态势图合成、目标特征管理 | `FusedTrack`, `ThreatAssessment`, `SituationPicture` |
| **资源管理** | WP04 | 无人平台注册、能力建模、资源匹配与裁定、健康评估 | `AllocationDecision`, `ResourceStateSnapshot` |

### L1/L2 接口与交互

| 分系统 | 工作包 | 核心职责 |
|--------|--------|----------|
| **外部接口管理** | WP00 | 上级/横向/前后协同系统的协议适配、监控与熔断 |
| **人机交互 / BFF** | WP12 | 全局操作界面、态势地图、仪表聚合推送、多屏显示 |

### L4 平台服务

| 分系统 | 工作包 | 核心职责 |
|--------|--------|----------|
| **消息服务** | WP07 | Topic 登记、订阅治理、消息路由分发、重试与死信管理 |
| **知识与规则** | WP08 | 作战规则集、战术模板、推理引擎、推荐结果输出 |
| **数据库管理** | — | 实时/历史/时空/GIS 数据的多库管理与所有权管控 |

### L5 通信与接入

| 分系统 | 工作包 | 核心职责 |
|--------|--------|----------|
| **通信组网** | WP06 | 链路状态监控、拓扑管理、质量评估、安全事件上报 |
| **协同增强单元** | WP05 | 无人平台命令翻译、边缘状态上报、能力汇聚、仿真桥接 |

### L6 运维保障

| 分系统 | 工作包 | 核心职责 |
|--------|--------|----------|
| **权限与安全审计** | WP09 | 认证、授权、操作审计、安全合规 |
| **监控与日志** | WP10 | 指标采集、告警聚合、日志索引、链路追踪 |
| **运维管理** | WP11 | 健康检查、备份、容量规划、运维任务 |
| **版本与部署** | WP13 | 发布管理、版本控制、CI/CD 编排 |

---

## 4. 核心业务主链路

### 4.1 主战闭环（Command Chain）

```
上级指控
  │  MissionCommand
  ▼
外部接口管理
  │  转发至消息总线
  ▼
任务管理 (WP02)
  │  TaskPackage（分解后的任务包）
  ▼
交战管控 (WP01)
  │  AllocationRequest → 资源管理 → AllocationDecision
  │  BattlePlan（包含编队、航路、传感器/武器参数）
  ▼
协同增强单元 (WP05)
  │  PlatformCommand（翻译为平台可识别指令）
  ▼
无人平台执行
  │  ExecutionStateSnapshot / PlatformAlert
  ▼
交战管控 (WP01)
  │  EngagementEffectReport
  ▼
任务管理 (WP02)  →  任务闭环确认
```

### 4.2 感知链路（Sensing Chain）

```
无人平台传感器
  │  TargetTrack / PayloadState
  ▼
协同增强单元 (WP05)
  │  上报原始目标轨迹
  ▼
态势管理 (WP03)
  │  多源融合 → FusedTrack → ThreatAssessment
  ▼
交战管控 (WP01)  ←  驱动计划调整或触发重规划
```

### 4.3 异常处理策略（双轨恢复）

系统在执行期异常处理上遵循**双轨原则**，这是本系统最核心的语义边界之一：

```
执行异常
  │
  ├─ 是否突破任务约束边界？
  │
  ├─ 否 → 计划级调整（BattleCtrl 内部消化）
  │           发布 plan_updated，无需回溯任务
  │
  └─ 是 → 任务级重构（升级至 TaskMgmt）
              任务重建 → 新 TaskPackage → 重新规划
```

---

## 5. 关键架构决策

### 决策一：任务（Task）与计划（Plan）严格语义分离

| 概念 | 回答的问题 | 归属分系统 | 代表对象 |
|------|------------|-----------|---------|
| **Task（任务）** | 做什么、何时完成、用什么效能衡量 | TaskMgmt | `TaskPackage`, `TaskConstraint` |
| **Plan（计划）** | 谁去做、走哪条路、用什么参数 | BattleCtrl | `BattlePlan`, `RouteSegment`, `WeaponProfile` |

> 这一分离防止了"目标"和"方案"的概念混淆，也使任务调度与执行规划可以独立演进。

### 决策二：DDS 发布-订阅消息总线

所有分系统间通信通过**注册 Topic 的 Pub/Sub 机制**完成，无私有旁路。消息服务（WP07）是唯一的 Topic 登记中心，负责：
- Topic 定义与 Schema 版本管理
- 订阅绑定治理
- 投递确认与死信队列
- 消息持久化

### 决策三：端口-适配器（Ports & Adapters）实现层架构

每个工作包的 C++ 实现均遵循四层结构：

```
domain/     ← 核心业务逻辑与领域对象（不依赖任何外部库）
application/← 用例编排、流程调度
adapter/    ← DDS、数据库、日志等具体技术适配
tests/      ← 契约驱动的单元与集成测试
```

### 决策四：Agent-Ready 工作包

每个工作包的设计输出均满足"可由 AI Agent 或工程师独立领取并实现"的标准，包含：
- 完整的接口控制文档（ICD）
- Protobuf 契约样例（正常/异常/边界）
- C++ 代码骨架
- 完成定义与验收标准

---

## 6. 数据所有权基线

系统通过**主拥有者（Owner）规则**杜绝跨分系统越权写入：

| 对象域 | 主拥有者 | 非 Owner 仅可 |
|--------|---------|--------------|
| 任务域（TaskPackage 等） | TaskMgmt | 消费、引用、基于约束生成下游计划 |
| 计划/交战域（BattlePlan 等） | BattleCtrl | 读取并翻译为边缘动作 |
| 资源域（AllocationDecision 等） | ResMgmt | 发起申请并消费裁定结果 |
| 态势域（FusedTrack 等） | SitMgmt | 读取和引用 |
| 知识规则域（InferenceResult 等） | KnowledgeRule | 读取或发起推理请求 |
| 边缘执行域（PlatformCommand 等） | EnhanceUnit | BattleCtrl 下发命令，ResMgmt/SitMgmt 消费上报 |
| 通信域（TopologySnapshot 等） | CommNet | 业务层消费链路与安全结论 |
| 消息治理域（TopicDefinition 等） | MsgService | 按登记关系发布订阅 |
| 审计/监控域 | AuthAudit / MonitorLog | OpsMgmt、HMI 读取展示 |
| 前端聚合域（UiDashboardResponse） | BFF | HMI 读取展示，BFF 不反写业务主对象 |

> **核心约束：** 非 Owner 只能读取、缓存、裁剪或生成派生视图，**不能反向覆盖主对象**。跨分系统写入只能通过正式 ICD 登记的 Topic 完成。

完整规则见：[`designArtifacts/delivery/BMS_Owner_Rule_Baseline.md`](designArtifacts/delivery/BMS_Owner_Rule_Baseline.md)

---

## 7. 消息契约与接口体系

### Protobuf Schema（17 个文件）

位于 [`proto/bms/schema/`](proto/bms/schema/)，涵盖系统全部跨边界消息：

| Schema 文件 | 覆盖领域 |
|-------------|---------|
| `common.proto` | 公共枚举、消息头、QoS 等级 |
| `task.proto` | 任务指令、约束、任务包 |
| `battle.proto` | 交战计划、航路、传感器/武器配置 |
| `execution.proto` | 执行状态快照、执行异常 |
| `situation.proto` | 融合目标、威胁评估、目标特征 |
| `resource.proto` | 资源申请、裁定、状态快照 |
| `message.proto` | 消息包络、Topic 定义、投递回执 |
| `knowledge.proto` | 推理请求、推荐项 |
| `comm.proto` | 拓扑快照、链路质量、安全事件 |
| `persistence.proto` | 所有权策略、实时/归档记录 |
| `platform.proto` | 平台飞行/导航/任务状态 |
| `platform_command.proto` | 飞行计划上传、起飞、返航指令 |
| `simulation.proto` | 仿真场景控制、仿真飞行/传感/武器状态 |
| `audit.proto` | 审计事件、安全告警 |
| `monitor.proto` | 指标点、监控告警 |
| `ops.proto` | 备份快照、DB 指标 |
| `bff.proto` | UI 汇总视图、仪表推送包络 |

---

## 8. 技术栈基线

| 维度 | 选型 |
|------|------|
| 主语言 | **C++20** |
| 构建系统 | **CMake 3.20+** |
| Schema / IDL | **Protocol Buffers（proto3）** |
| 消息中间件 | **DDS** （具体供应商待联调前确认） |
| 持久化 | **SQLite3**（可替换为文件适配器） |
| 单元测试 | **GoogleTest**（首批骨架使用零依赖 smoke test） |
| 架构图 | **PlantUML C4 Model** |
| 代码组织 | 按工作包 `implementation/wpXX_xxx/` 独立子目录 |

---

## 9. 工程目录结构

```
XD/
├── README.md                          ← 本文件（架构速览入口）
├── BMS_Design_Artifact_Guide.md       ← 全部设计产物导航
│
├── plantumlC4/                        ← C4 架构图（L0~L3 + 动态图 + 部署图）
│
├── proto/bms/schema/                  ← 17 个 Protobuf Schema 文件
│
├── sysFunctionalRequirements/         ← 系统功能需求（.md + .xmind）
│
├── designArtifacts/
│   ├── contracts/                     ← 接口对象目录、容器契约矩阵、语义定义
│   ├── delivery/                      ← 设计治理基线、工作包、联调矩阵（30+ 文档）
│   │   ├── workPackages/              ← WP01~WP13 各工作包设计文档
│   │   └── README.md                  ← 文档分类导航（建议从此进入）
│   ├── schema/                        ← Schema IDL 基线
│   ├── icd/                           ← 接口控制文档
│   └── review/                        ← 设计评审产物
│
├── implementation/                    ← C++ 实现代码（按工作包组织）
│   ├── wp01_battlectrl/               ← 交战管控（骨架已就绪）
│   ├── wp02_taskmgmt/                 ← 任务管理（骨架已就绪）
│   ├── wp03_sitmgmt/                  ← 态势管理（骨架已就绪）
│   ├── wp04_resmgmt/                  ← 资源管理（骨架已就绪）
│   ├── wp05_enhanceunit/              ← 协同增强单元（骨架已就绪）
│   ├── wp06_commnet/                  ← 通信组网（骨架已就绪）
│   ├── wp07_msgservice/               ← 消息服务（**已完整实现**）
│   ├── wp08_knowledgerule/            ← 知识规则（骨架已就绪）
│   ├── wp09_authaudit/                ← 权限审计（骨架已就绪）
│   └── wp10_monitorlog/               ← 监控日志（骨架已就绪）
│
├── testAssets/                        ← 测试资产（契约样例、集成追踪、Mock 服务）
│   ├── formal01~formal11/             ← 11 个正式契约测试专题
│   ├── integration_traces/            ← 主战闭环 / BFF 推送 / 运维治理追踪
│   ├── mockServices/                  ← 5 类 Mock 服务骨架
│   └── reports/                       ← 契约/集成/回归测试报告
│
└── oldSysReference/                   ← 历史系统参考（只读）
```

---

## 10. 工作包与开发组织

系统被拆分为 **13 个可独立领取的工作包**，每个工作包具备：

```
workPackages/wpXX_xxx/
├── BMS_Work_Package_XX_*.md          ← 主设计文档（目标、范围、接口契约）
├── ICD_Package/                      ← 接口控制文档与消息定义
├── Payload_Checklist/                ← 字段约束与样例
├── AGENT_HANDOFF/                    ← AI Agent 直接可用的实现规范包
└── TODO/                             ← 实现待办清单
```

### 当前实现状态

| 状态 | 工作包 |
|------|--------|
| ✅ 完整实现 | WP07 消息服务（含 SQLite 持久化、单元测试） |
| 🔨 骨架已就绪 | WP01~WP06, WP08~WP10 |
| 📐 设计完成 | WP11 运维管理、WP12 BFF/HMI、WP13 版本部署 |

---

## 11. 测试与验证体系

### 三层测试架构

```
契约测试（formal01~11）
  ↓ 验证单个消息格式与字段约束
集成追踪（integration_traces）
  ↓ 验证跨分系统消息序列与 trace_id 连续性
回归测试（reports/regression）
  ↓ 验证全链路业务闭环
```

### 五大集成场景

| 场景 | 描述 |
|------|------|
| **场景 A** 正常闭环 | MissionCommand → TaskPackage → BattlePlan → 执行 → 效果报告 |
| **场景 B** 资源约束 | 部分资源满足，任务约束重评估 |
| **场景 C** 计划调整 | 链路降级/平台告警触发 `plan_updated`（不回溯任务） |
| **场景 D** 任务重构 | 异常超出任务约束 → TaskMgmt 重建任务 |
| **场景 E** 态势驱动 | FusedTrack + ThreatAssessment 驱动 BattleCtrl 输入更新 |

---

## 12. 推荐阅读路径

### 快速理解系统（30 分钟）

1. **本文件**（架构全貌）
2. [`sysFunctionalRequirements/sysFunctionalRequirements.md`](sysFunctionalRequirements/sysFunctionalRequirements.md) — 系统做什么
3. [`plantumlC4/C4_L2_Container.puml`](plantumlC4/C4_L2_Container.puml) — 容器全图（用 PlantUML 渲染）
4. [`designArtifacts/delivery/BMS_System_Design_Goal.md`](designArtifacts/delivery/BMS_System_Design_Goal.md) — 设计原则

### 准备开发一个工作包（1 小时）

1. [`designArtifacts/delivery/BMS_Owner_Rule_Baseline.md`](designArtifacts/delivery/BMS_Owner_Rule_Baseline.md) — 所有权约束
2. [`designArtifacts/delivery/BMS_Completion_Definition.md`](designArtifacts/delivery/BMS_Completion_Definition.md) — 完成定义
3. [`designArtifacts/delivery/README.md`](designArtifacts/delivery/README.md) — 文档分类导航
4. [`designArtifacts/delivery/workPackages/wpXX_xxx/`](designArtifacts/delivery/workPackages/) — 对应工作包目录
5. [`implementation/wpXX_xxx/`](implementation/) — 代码骨架
6. [`testAssets/`](testAssets/) — 契约样例与 Mock 服务

### 进行架构决策或变更

1. [`designArtifacts/delivery/BMS_Change_Governance.md`](designArtifacts/delivery/BMS_Change_Governance.md) — 变更治理
2. [`designArtifacts/delivery/BMS_Design_Completion_Baseline.md`](designArtifacts/delivery/BMS_Design_Completion_Baseline.md) — 设计完成基线
3. [`designArtifacts/contracts/BMS_Container_Contract_Matrix.md`](designArtifacts/contracts/BMS_Container_Contract_Matrix.md) — 契约矩阵

---

## 总结

BMS 是一个**设计先行、契约驱动、工作包粒度清晰**的现代分布式系统。其核心工程价值体现在：

- 🏗️ **六层架构清晰分隔**：外部接口 / 人机交互 / 业务应用 / 平台服务 / 通信接入 / 运维保障各层职责互不侵越
- 🔐 **所有权基线强约束**：主数据只有一个权威拥有者，杜绝多人/多 Agent 并行开发时的数据污染
- 📦 **13 个独立工作包**：每包可由工程师或 AI Agent 独立领取、实现、测试
- 📋 **契约先于实现**：Protobuf schema + ICD + 测试样例构成完整实现规范，减少隐式依赖
- 🔄 **双轨异常恢复**：计划级调整与任务级重构的清晰分界，保障系统韧性

> 如需进一步了解某个分系统、某条链路或某项架构决策，请参考 [`BMS_Design_Artifact_Guide.md`](BMS_Design_Artifact_Guide.md) 获取完整设计产物导航。
