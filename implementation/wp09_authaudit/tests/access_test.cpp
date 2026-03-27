#include <cassert>
#include "test_support.h"
#include "wp09_authaudit/authaudit_application_service.h"
using namespace wp09_authaudit;
int main() { AccessPolicyEvaluator a; OperationAuditRecorder b; SecurityCorrelationService c; AuthAuditApplicationService s(a,b,c); const auto out = s.process(test_support::makeUserAction(), test_support::makeSecurityEvent(), nullptr); assert(out.accessDecisionRecord.allowed); return 0; }