#pragma once
#include "wp09_authaudit/message_types.h"
namespace wp09_authaudit { class SecurityCorrelationService { public: SecurityReviewRecord correlate(const SecurityEvent& securityEvent, const AuditEvent& auditEvent) const; }; }