# WP01 BattleCtrl 工程级 ICD 初版

## 1. 当前阶段

1. 当前版本：v0.2。
2. 当前用途：BattlePlan、计划调整、效果评估与规则辅助请求的模块完成版工程实现约束。
3. 冻结程度：模块完成待审核，可继续联调前置开发。

## 2. 当前冻结项

1. BattlePlan 必须保留 planId、taskId、missionId、platformId、constraintRef。
2. AllocationDecision 仅可只读消费，不能被改写。
3. PlatformAlert 与 DegradationAlert 只触发计划级调整，不直接代表任务完成。
4. EngagementEffectReport 必须可回接 taskId、planId 与 traceId。

## 3. 当前实现映射

1. TaskIntentAdapter：TaskConstraint/TaskPackage -> EngagementInput。
2. BattlePlanGenerator：EngagementInput + AllocationDecision + ThreatAssessment -> BattlePlan。
3. ConstraintGuard：反馈与链路异常 -> PlanAdjustmentDecision。
4. PlanAdjustmentService：BattlePlan + PlanAdjustmentDecision -> 更新后的 BattlePlan。
5. EffectAssessmentService：MissionProgress + ThreatAssessment -> EngagementEffectReport。
6. RuleAssistGateway：ThreatAssessment + EngagementInput -> InferenceRequest。

## 4. 当前验证状态

1. plan_created_test：验证 TaskPackage 到 BattlePlan 主链。
2. plan_updated_test：验证平台异常触发的计划调整链。
3. effect_report_test：验证执行效果评估输出。
4. boundary_test：验证越出任务约束时的任务回退边界。