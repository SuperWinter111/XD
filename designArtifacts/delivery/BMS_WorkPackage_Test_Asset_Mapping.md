# BMS 工作包测试资产闭环映射

本文档用于把每个工作包最终映射到：正式 ICD、契约样例目录、关键样例文件和主要联调场景，作为“整体设计完成”后的执行闭环总表。

| 工作包 | 正式 ICD | 契约样例目录 | 关键样例文件 | 联调场景 |
| --- | --- | --- | --- | --- |
| wp01_battlectrl | Formal 01, 02, 03, 04, 06, 07 | testAssets/contract/formal01_platform_execution_chain/, testAssets/contract/formal02_task_battle_execution_closure/, testAssets/contract/formal03_resource_allocation_and_reservation/, testAssets/contract/formal04_situation_and_threat/, testAssets/contract/formal06_threat_reasoning_and_rule_inference/, testAssets/contract/formal07_comm_link_and_security/ | normal_command_ack_accepted.json, normal_taskpackage_to_effect_report.json, abnormal_partial_allocation_reserved.json, normal_fused_track_to_threat_assessed.json | testAssets/integration/core_battle_loop/ |
| wp02_taskmgmt | Formal 02, 03, 06 | testAssets/contract/formal02_task_battle_execution_closure/, testAssets/contract/formal03_resource_allocation_and_reservation/, testAssets/contract/formal06_threat_reasoning_and_rule_inference/ | normal_taskpackage_to_effect_report.json, boundary_taskmgmt_not_emit_battleplan.json, normal_inference_to_recommendation_reason_trace.json | testAssets/integration/core_battle_loop/ |
| wp03_sitmgmt | Formal 04, 05, 06, 09 | testAssets/contract/formal04_situation_and_threat/, testAssets/contract/formal05_target_feature_and_status_extension/, testAssets/contract/formal06_threat_reasoning_and_rule_inference/, testAssets/contract/formal09_simulation_and_training_integration/ | normal_fused_track_to_threat_assessed.json, normal_target_feature_status_extension.json, normal_inference_to_recommendation_reason_trace.json, normal_sim_tick_flight_state_injection.json | testAssets/integration/core_battle_loop/ |
| wp04_resmgmt | Formal 03, 07 | testAssets/contract/formal03_resource_allocation_and_reservation/, testAssets/contract/formal07_comm_link_and_security/ | normal_allocation_accepted.json, abnormal_partial_allocation_reserved.json, abnormal_link_degraded_high_loss.json | testAssets/integration/core_battle_loop/ |
| wp05_enhanceunit | Formal 01, 09 | testAssets/contract/formal01_platform_execution_chain/, testAssets/contract/formal09_simulation_and_training_integration/ | normal_command_ack_accepted.json, reject_takeoff_platform_offline.json, normal_sim_tick_flight_state_injection.json | testAssets/integration/core_battle_loop/ |
| wp06_commnet | Formal 07 | testAssets/contract/formal07_comm_link_and_security/ | normal_link_quality_nominal.json, abnormal_link_degraded_high_loss.json, boundary_degradation_event_not_persistent_state.json | testAssets/integration/core_battle_loop/ |
| wp07_msgservice | Formal 08 | testAssets/contract/formal08_message_governance_and_delivery/ | normal_topic_defined_delivery_success.json, abnormal_retry_failed_dead_letter.json, boundary_delivery_receipt_not_business_done.json | testAssets/integration/core_battle_loop/ |
| wp08_knowledgerule | Formal 06 | testAssets/contract/formal06_threat_reasoning_and_rule_inference/ | normal_inference_to_recommendation_reason_trace.json, abnormal_rule_conflict_empty_recommendation.json, boundary_recommendation_not_threat_assessment.json | testAssets/integration/core_battle_loop/ |
| wp09_authaudit | Formal 10 | testAssets/contract/formal10_ops_audit_and_monitoring/ | normal_audit_and_alert_published.json, abnormal_security_escalation_incident_opened.json, boundary_monitor_not_rewrite_business_object.json | testAssets/integration/ops_governance/ |
| wp10_monitorlog | Formal 10 | testAssets/contract/formal10_ops_audit_and_monitoring/ | normal_audit_and_alert_published.json, abnormal_security_escalation_incident_opened.json, boundary_monitor_not_rewrite_business_object.json | testAssets/integration/ops_governance/ |
| wp11_opsmgmt | Formal 10 | testAssets/contract/formal10_ops_audit_and_monitoring/ | normal_audit_and_alert_published.json, abnormal_security_escalation_incident_opened.json, boundary_monitor_not_rewrite_business_object.json | testAssets/integration/ops_governance/ |
| wp12_bff_hmi | Formal 11 | testAssets/contract/formal11_bff_aggregation_and_ui_push/ | normal_dashboard_and_alert_stream_push.json, abnormal_reconnect_recover_subscription.json, boundary_bff_readonly_not_writeback.json | testAssets/integration/bff_push_and_recovery/ |
| wp13_versiondeploy | Formal 10 | testAssets/contract/formal10_ops_audit_and_monitoring/ | normal_audit_and_alert_published.json, abnormal_security_escalation_incident_opened.json, boundary_monitor_not_rewrite_business_object.json | testAssets/integration/ops_governance/ |

## 2. 使用规则

1. 每个工作包至少应能从本表追到一个正式 ICD 组。
2. 每个工作包至少应能从本表追到正常、异常、边界样例。
3. 每个工作包至少应能从本表追到一个联调场景入口。
4. 后续若新增样例文件，应先更新本表再更新工作包说明。
