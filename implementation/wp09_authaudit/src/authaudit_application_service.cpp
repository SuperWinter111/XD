#include "wp09_authaudit/authaudit_application_service.h"
namespace wp09_authaudit {
AuthAuditApplicationService::AuthAuditApplicationService(AccessPolicyEvaluator& accessPolicyEvaluator, OperationAuditRecorder& operationAuditRecorder, SecurityCorrelationService& securityCorrelationService)
    : accessPolicyEvaluator_(accessPolicyEvaluator), operationAuditRecorder_(operationAuditRecorder), securityCorrelationService_(securityCorrelationService) {}
AuthAuditOutputs AuthAuditApplicationService::process(const UserAction& userAction, const SecurityEvent& securityEvent, const OpsJobSummary* opsJobSummary) const {
  auto accessDecisionRecord = accessPolicyEvaluator_.evaluate(userAction);
  auto auditEvent = operationAuditRecorder_.record(userAction, opsJobSummary);
  auto securityReviewRecord = securityCorrelationService_.correlate(securityEvent, auditEvent);
  return AuthAuditOutputs{accessDecisionRecord, auditEvent, securityReviewRecord};
}
}