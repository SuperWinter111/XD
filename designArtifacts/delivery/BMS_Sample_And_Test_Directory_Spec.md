# BMS 样例与测试目录规范

本文档用于约束后续样例 payload、mock 数据、契约测试和联调记录在仓库中的目录组织方式，避免工作包已经具备，但测试资产仍然散落无序。

## 1. 目标

1. 让每个工作包都能找到自己的样例与测试资产位置。
2. 让每个正式 ICD 都能映射到一组明确的测试样例目录。
3. 让工程师和 agent 生成的样例文件具备统一命名与归档规则。

## 2. 推荐目录结构

建议后续在仓库中新增如下目录结构：

```text
testAssets/
  contract/
    formal01_platform_execution_chain/
    formal02_task_battle_execution_closure/
    formal03_resource_allocation_and_reservation/
    formal04_situation_and_threat/
    formal05_target_feature_and_status_extension/
    formal06_threat_reasoning_and_rule_inference/
    formal07_comm_link_and_security/
    formal08_message_governance_and_delivery/
    formal09_simulation_and_training_integration/
    formal10_ops_audit_and_monitoring/
    formal11_bff_aggregation_and_ui_push/
  workPackages/
    wp01_battlectrl/
    wp02_taskmgmt/
    wp03_sitmgmt/
    wp04_resmgmt/
    wp05_enhanceunit/
    wp06_commnet/
    wp07_msgservice/
    wp08_knowledgerule/
    wp09_authaudit/
    wp10_monitorlog/
    wp11_opsmgmt/
    wp12_bff_hmi/
    wp13_versiondeploy/
  integration/
    core_battle_loop/
    ops_governance/
    bff_push_and_recovery/
  mocks/
    platform/
    simulation/
    resource/
    message/
    monitor/
  reports/
    contract/
    integration/
    regression/
```

## 3. 每类目录放什么

### 3.1 contract

按正式 ICD 分组，存放：

1. 正常样例。
2. 异常样例。
3. 边界负样例。
4. 必要时的拒绝样例、重试样例、回滚样例。

### 3.2 workPackages

按工作包分组，存放：

1. 本工作包专属 mock 数据。
2. 本工作包测试输入输出样例。
3. 本工作包的联调前置说明。
4. 本工作包的验收记录模板。

### 3.3 integration

按跨分系统场景分组，存放：

1. 主业务闭环场景样例。
2. 运维治理链路样例。
3. BFF 推送与重连恢复样例。
4. 跨分系统联调执行记录。

### 3.4 mocks

按外部依赖或输入源分组，存放：

1. 平台侧 mock。
2. 仿真侧 mock。
3. 资源裁定 mock。
4. 消息治理 mock。
5. 监控和告警 mock。

### 3.5 reports

存放：

1. 契约测试报告。
2. 联调记录。
3. 回归测试结果。

## 4. 文件命名规则

推荐采用以下命名模式：

1. 正常样例：normal_*.json
2. 异常样例：abnormal_*.json
3. 边界样例：boundary_*.json
4. 拒绝样例：reject_*.json
5. 回放或时序说明：trace_*.md
6. 验收记录：acceptance_*.md

示例：

1. normal_command_ack_accepted.json
2. abnormal_link_degraded_high_loss.json
3. boundary_delivery_receipt_not_business_done.json
4. trace_core_battle_loop.md

## 5. 样例最小字段要求

所有跨分系统样例至少必须包含：

1. trace_id。
2. schema_version。
3. event_time。
4. source_id。
5. 与 payload 对应的主业务 key 字段。

## 6. 映射规则

1. 每个正式 ICD 目录至少包含 1 套正常样例、1 套异常样例、1 套边界负样例。
2. 每个工作包目录至少映射到其对应的正式 ICD 目录。
3. 每个 integration 目录至少映射到联调矩阵中的一条链路。
4. 每次回归测试结果必须归档到 reports 目录。

## 7. 使用原则

1. 样例与测试目录是执行资产，不替代正式 ICD 和工作包文档。
2. 新增公共样例前，必须先确认 owner rule 和变更治理要求。
3. 若正式 ICD 或 topic 发生变化，必须同步更新对应目录下的样例。

## 8. 当前已落地的归档基线

当前仓库已落地完整测试资产归档基线，位置如下：

1. testAssets/contract/formal01_platform_execution_chain/ 到 formal11_bff_aggregation_and_ui_push/
2. testAssets/workPackages/wp01_battlectrl/ 到 wp13_versiondeploy/
3. testAssets/integration/core_battle_loop/
4. testAssets/integration/ops_governance/
5. testAssets/integration/bff_push_and_recovery/
6. testAssets/mocks/platform/、resource/、simulation/、message/、monitor/
7. testAssets/reports/contract/、integration/、regression/
