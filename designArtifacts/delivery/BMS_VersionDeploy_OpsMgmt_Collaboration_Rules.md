# BMS Version / Deploy 与 OpsMgmt 协同约束

本文档用于把 Version / Deploy 与 OpsMgmt 的协同边界固化下来，重点澄清审批权、触发权、执行权、记录权和回滚联动规则。

## 1. 核心结论

1. OpsMgmt 是长期运维治理 owner，Version / Deploy 是版本发布与部署 owner。
2. OpsMgmt 负责配置、运维任务、流程、作业和运维记录。
3. Version / Deploy 负责版本基线、发布计划、部署执行、发布验证和回滚执行。
4. 两者必须通过 config_changed、release_event 和监控告警协同，而不是相互替代。

## 2. 权限与责任对照

| 维度 | OpsMgmt | Version / Deploy |
| --- | --- | --- |
| 主责任 | 配置治理、运维流程、任务与作业 | 版本管理、发布流程、部署执行、回滚 |
| 审批权 | 配置变更、运维流程审批 | 发布审批流程 owner，但可依赖 OpsMgmt 流程协同 |
| 触发权 | 可触发配置生效、作业、自检 | 可触发构建、部署、回滚 |
| 执行权 | 运维作业和流程执行 | 发布和回滚执行 |
| 记录权 | 配置、任务、作业、流程记录 | 版本、发布、回滚、依赖和环境检测记录 |
| 输入信号 | MonitorMetric, MonitorAlert, AuditEvent, release_event | config_changed, MonitorAlert |

## 3. 协同主链

### 3.1 发布前

1. OpsMgmt 提供配置上下文与变更审批结果。
2. Version / Deploy 基于版本基线、依赖检查和环境检测完成发布前验证。
3. 若配置变更与发布绑定，必须先有可追溯的 config_changed 记录。

### 3.2 发布中

1. Version / Deploy 负责发布执行和 release_event 输出。
2. OpsMgmt 负责跟踪运维影响、记录流程状态，并在需要时协调运维任务。

### 3.3 发布后

1. MonitorLog 输出 monitor/alert 和监控结果。
2. OpsMgmt 负责根据告警触发处置流程。
3. Version / Deploy 负责根据处置结论执行回滚或补救发布。

## 4. 回滚规则

1. 回滚执行权归 Version / Deploy。
2. 回滚触发可来自：
   1. 发布验证失败。
   2. MonitorAlert 达到回滚阈值。
   3. OpsMgmt 运维处置流程明确要求回滚。
3. 回滚完成后必须输出 release_event，并由 OpsMgmt 落运维记录。

## 5. 禁止事项

1. 禁止 OpsMgmt 直接替代 Version / Deploy 执行版本回滚。
2. 禁止 Version / Deploy 直接替代 OpsMgmt 执行长期运维流程审批。
3. 禁止任何一方越权改写业务主域对象。
4. 禁止在未记录 config_changed 或 release_event 的情况下做隐式配置或发布变更。

## 6. 最小联调要求

1. 配置变更 -> 发布执行 -> release_event 正常样例 1 套。
2. 发布失败 -> 运维告警 -> 回滚执行样例 1 套。
3. 环境阻断 -> 发布未执行样例 1 套。
