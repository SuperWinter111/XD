# BMS 容器契约矩阵

本矩阵用于支撑后续 Code Diagram 设计与多 agent 并行开发。每个容器必须先遵守契约，再进入代码实现。

## 契约原则

1. 前端不直连数据库，只通过 API Gateway / BFF 与后端交互。
2. 后端容器之间以 DDS 事件流为主，少量同步查询通过 API 完成。
3. 每个容器拥有自己的数据主权，不共享写库。
4. 现有地面站协议只出现在边缘协议桥与协同增强单元，不进入核心业务模型。
5. 仿真器优先复用真实接口契约，避免形成第二套输入语义。
6. DDS 主题定义与消息包络中的 QoS 档位必须使用统一标准档，不得在业务容器中自定义自由字符串。

## 容器矩阵

| 容器 | 主要职责 | 提供的同步接口 | 发布 DDS 主题 | 订阅 DDS 主题 | 主数据拥有权 | 禁止事项 |
| --- | --- | --- | --- | --- | --- | --- |
| HMI 前端 | 人机交互、态势展示、任务/交战操作 | 仅访问 API Gateway / BFF | 无 | UI 推送类主题通过 BFF 转发 | 无 | 不直连数据库；不直连 DDS |
| API Gateway / BFF | 聚合查询、统一鉴权、前端订阅出口 | 登录、查询、命令转发、WebSocket 推送 | ui.push.* | task.*, sit.*, battle.*, res.*, ops.* | 会话缓存、前端查询缓存 | 不写业务主库 |
| 外部接口管理分系统 | 上级、横向、前后系统协议适配 | 外部系统同步交互接口 | ext.command.*, ext.plan.*, ext.analysis.* | sit.report.*, task.report.* | 外部接口配置、契约版本 | 不直接操作平台状态 |
| 任务管理分系统 | 指令解析、任务分解、方案生成、任务调度 | 任务创建、方案查询、任务控制 | task.command.*, task.plan.*, task.report.* | ext.command.*, res.state.*, battle.effect.* | 任务单、任务分解结果、方案记录 | 不直接下发平台级控制指令 |
| 态势管理分系统 | 融合、威胁分析、态势推理、告警 | 态势查询、回放查询 | sit.track.*, sit.alert.*, sit.report.* | edge.target.*, ext.sit.*, sim.truth.* | 航迹、态势快照、告警记录 | 不直接管理资源配置 |
| 交战管控分系统 | 交战计划、编队、执行监控、效果评估 | 交战计划、临机打击请求 | battle.plan.*, battle.command.*, battle.effect.* | sit.track.*, res.state.*, edge.exec.* | 交战计划、执行记录、评估报告 | 不直接维护规则库 |
| 资源管理分系统 | 平台注册、状态、能力、调度 | 资源查询、资源调度、资源配置 | res.registry.*, res.state.*, res.allocate.* | edge.platform.*, edge.health.* | 资源档案、能力模型、分配记录 | 不直接处理原始传感器数据 |
| 知识与规则管理分系统 | 规则、模板、条令、目标知识 | 规则查询、模板查询、知识维护 | rule.changed.* | 无 | 规则、模板、条令、特征库 | 不订阅高频遥测 |
| 通信组网分系统 | 链路、组网、协议、安全、质量 | 链路配置、质量查询 | comm.link.*, comm.qos.*, comm.alert.* | edge.raw.*, edge.link.* | 链路配置、网络拓扑、通信质量记录 | 不存储业务主数据 |
| 协同增强单元分系统 | 地面站协议适配、平台代理、能力增强、任务执行 | 平台控制适配接口、边缘配置 | edge.platform.*, edge.target.*, edge.exec.*, edge.health.* | battle.command.*, task.command.*, sim.platform.* | 边缘缓存、平台会话、边缘映射表 | 不直接写核心业务数据库 |
| 用户权限与安全审计分系统 | 认证、授权、审计 | 登录、令牌、权限校验 | sec.audit.*, sec.alert.* | ops.user.*, ops.role.* | 用户、角色、权限、审计日志 | 不承接业务编排 |
| 监控与日志分系统 | 监控、告警、日志、诊断 | 监控查询、日志查询、告警确认 | ops.alert.*, ops.metric.* | comm.*, sec.*, dds.*, deploy.* | 指标、日志、告警、诊断记录 | 不参与业务决策 |
| 运维管理分系统 | 配置、自检、脚本、作业、流程 | 配置管理、作业触发、自检查询 | ops.config.*, ops.job.*, ops.selfcheck.* | ops.metric.*, deploy.* | 配置、运维任务、流程记录 | 不越权修改业务数据 |
| DDS 总线 | 事件与状态分发、QoS 控制 | 无 | 无 | 无 | 无 | 不承载业务持久化 |
| 仿真与训练环境 | 飞行/传感器/武器/环境仿真、真值、回放 | 场景控制、回放控制 | sim.platform.*, sim.sensor.*, sim.weapon.*, sim.truth.*, sim.clock.* | battle.command.*, task.plan.* | 场景定义、回放记录、真值记录 | 不替代核心业务决策 |

## 多 agent 并行开发边界

1. 每个 agent 只能修改自己负责容器的代码目录与测试目录。
2. DDS 主题定义文件与公共 schema 由平台契约 owner 统一维护。
3. 禁止 agent 自行新增跨容器同步调用；新增依赖必须先修改本矩阵。
4. 边缘适配 agent 只能接触现有地面站协议桥，不得把地面站报文结构传播到核心域模型。
