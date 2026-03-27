#pragma once
#include "wp09_authaudit/message_types.h"
namespace wp09_authaudit::test_support {
inline UserAction makeUserAction() { return UserAction{"trace-audit-001", "ops-admin", "change_config", "config-001", true}; }
inline UserAction makeStandardAction() { return UserAction{"trace-audit-002", "user-001", "view_dashboard", "dashboard-001", false}; }
inline SecurityEvent makeSecurityEvent() { return SecurityEvent{"trace-audit-001", "node-sec-001", "critical"}; }
inline OpsJobSummary makeOpsJobSummary() { return OpsJobSummary{"trace-audit-001", "job-001", "ops_job_executed"}; }
}