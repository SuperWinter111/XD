# WP07 MsgService 实现工程

本目录是 wp07_msgservice 的独立实现工程。

## 1. 对应设计输入

1. ../../designArtifacts/delivery/workPackages/wp07_msgservice/BMS_Work_Package_07_MsgService.md
2. ../../designArtifacts/delivery/workPackages/wp07_msgservice/ICD_Package.md
3. ../../designArtifacts/delivery/workPackages/wp07_msgservice/Payload_Checklist.md
4. ../../designArtifacts/delivery/workPackages/wp07_msgservice/AGENT_HANDOFF.md

## 2. 当前工程范围

1. TopicRegistry 骨架。
2. SubscriptionRegistry 骨架。
3. SubscriptionGovernanceService 骨架。
4. SubscriptionAuditRepository 接口与内存适配器。
5. EnvelopeRouter 骨架。
6. DeliveryTracker 骨架。
7. RetryAndDeadLetterService 骨架。
8. RetryScheduleRepository 接口与内存适配器。
9. MsgServiceApplicationService 编排层。
10. Use case 输入命令模型。
11. 外部入口 DTO 与 CommandMapper。
12. CommandHandler 入口编排层。
13. API-facing Response DTO 与 ResponseMapper。
14. 默认持久化仓储工厂。
15. 分文件单元测试结构。
16. 工程级 ICD 初版。

当前已补入文件适配器占位实现：

1. FileSubscriptionAuditRepository。
2. FileRetryScheduleRepository。

当前已补入 SQLite-ready adapter 骨架：

1. SqliteSubscriptionAuditRepository。
2. SqliteRetryScheduleRepository。
3. 默认持久化策略指向 sqlite。
4. 当前工程已支持通过 CMake 原生 SQLite3 包或 vcpkg 安装产物自动发现并参与构建。

当前 SQLite 接入状态：

1. 已在当前 Windows 环境安装 vcpkg 的 sqlite3:x64-windows。
2. 当前 CMake 会优先尝试原生 `find_package(SQLite3)`。
3. 若未命中，则回退检查 `VCPKG_ROOT/installed/x64-windows` 与 `C:/vcpkg/installed/x64-windows`。
4. 命中后自动启用 `BMS_MSGSERVICE_HAS_SQLITE=1` 与 sqlite adapters 编译。

当前 SQLite 运行库分发基线：

1. `sqlite3.dll` 采用随程序目录分发，不依赖系统 PATH。
2. 本模块内测试目标已在构建后自动复制 `sqlite3.dll` 到各自输出目录。
3. 上层可执行程序接入时，应在其 CMake 目标上调用 `bms_msgservice_attach_sqlite_runtime(<target>)`。
4. 安装阶段应调用 `bms_msgservice_install_sqlite_runtime(bin)`，使 `sqlite3.dll` 与程序主可执行文件同目录安装。
5. `msgservice.sqlite3` 数据文件与程序运行目录下的业务数据目录共同部署，不与动态库混放为系统级共享组件。

当前 SQLite 验证基线：

1. 已新增 `wp07_msgservice_sqlite_integration_test`。
2. 该测试经由 `MsgServiceApplicationService` 驱动 SQLite 仓储落库。
3. 测试通过 `MsgServiceRepositoryFactory` 默认 backend 路径创建 SQLite 仓储。
4. 测试会直接打开 `msgservice.sqlite3` 并校验 `subscription_audit` 与 `retry_schedule` 表记录数。
5. 测试会校验 rejected 订阅审计、成功订阅端点、失败原因与下一次重试时间等关键字段值。

当前文件适配器持久化格式已冻结：

1. 首行写入 #format=version。
2. 次行写入 #columns=fixed-order。
3. 数据行使用稳定的 | 分隔顺序。

当前 file adapter 定位：

1. 正式轻量部署形态。
2. 不是仅供调试的临时落盘。

## 3. 后续扩展

1. 审计持久化 adapter。
2. 调度器对外接口 adapter。
3. MonitorLog 观测对接。
4. proto 生成代码接入。
5. 错误码映射策略。
