#include <cassert>
#include "test_support.h"
#include "wp09_authaudit/authaudit_application_service.h"
using namespace wp09_authaudit;
int main() { AccessPolicyEvaluator a; OperationAuditRecorder b; SecurityCorrelationService c; AuthAuditApplicationService s(a,b,c); const auto job = test_support::makeOpsJobSummary(); const auto out = s.process(test_support::makeUserAction(), test_support::makeSecurityEvent(), &job); assert(out.auditEvent.eventType == "ops_job_executed"); return 0; }