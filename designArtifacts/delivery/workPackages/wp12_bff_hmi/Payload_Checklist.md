# WP12 BFF_HMI Payload 核对表

## 1. 重点 payload

1. UiDashboardResponse。
2. UiPushEnvelope。
3. UiTaskSummary。
4. UiSituationSnapshot。
5. UiBattleOverview。
6. UiResourceOverview。
7. UiAlertItem。

## 2. 字段级核对重点

1. UiDashboardResponse：必须明确多域来源和刷新时间点。
2. UiPushEnvelope：必须保留 channel、view_type、trace_id 和 payload 对应关系。
3. UiTaskSummary、UiSituationSnapshot、UiBattleOverview、UiResourceOverview：必须保持只读聚合语义。
4. UiAlertItem：必须对齐告警类型、严重等级和来源域。

## 3. 常见错误

1. 在 UiPushEnvelope 中混装不属于当前视图的 payload。
2. 把 UI 聚合对象回写成业务权威对象。
3. 前端视图缺少 trace_id 或刷新时间，导致无法追溯。
