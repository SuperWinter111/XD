#pragma once
#include "wp09_authaudit/access_policy_evaluator.h"
#include "wp09_authaudit/operation_audit_recorder.h"
#include "wp09_authaudit/security_correlation_service.h"
namespace wp09_authaudit {
struct AuthAuditOutputs { AccessDecisionRecord accessDecisionRecord; AuditEvent auditEvent; SecurityReviewRecord securityReviewRecord; };
class AuthAuditApplicationService {
 public:
  AuthAuditApplicationService(AccessPolicyEvaluator& accessPolicyEvaluator, OperationAuditRecorder& operationAuditRecorder, SecurityCorrelationService& securityCorrelationService);
  AuthAuditOutputs process(const UserAction& userAction, const SecurityEvent& securityEvent, const OpsJobSummary* opsJobSummary) const;
 private:
  AccessPolicyEvaluator& accessPolicyEvaluator_;
  OperationAuditRecorder& operationAuditRecorder_;
  SecurityCorrelationService& securityCorrelationService_;
};
}