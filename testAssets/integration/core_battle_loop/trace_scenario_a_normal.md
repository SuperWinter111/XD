# 场景 A 正常任务闭环追踪说明

trace_id: trace-scenario-a-normal-001

建议链路：

1. bms/core/command/task/command_received
2. bms/core/command/task/decomposed
3. bms/core/command/resource/allocation_requested
4. bms/core/command/resource/allocation_committed
5. bms/core/command/task/plan_created
6. bms/core/command/battle/plan_created
7. bms/edge/platform/command/flight_plan_upload
8. bms/edge/platform/event/command_ack
9. bms/edge/platform/event/mission_progress
10. bms/core/command/battle/effect_report

联调参与方：

1. TaskMgmt
2. ResMgmt
3. BattleCtrl
4. EnhanceUnit
