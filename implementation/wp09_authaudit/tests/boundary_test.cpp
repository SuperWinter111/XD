#include <cassert>
#include "test_support.h"
#include "wp09_authaudit/authaudit_application_service.h"
using namespace wp09_authaudit;
int main() { AccessPolicyEvaluator a; OperationAuditRecorder b; SecurityCorrelationService c; AuthAuditApplicationService s(a,b,c); const auto out = s.process(test_support::makeStandardAction(), test_support::makeSecurityEvent(), nullptr); assert(out.auditEvent.eventType == "user_action"); assert(out.accessDecisionRecord.rationale == "standard_allow"); return 0; }