#pragma once
#include "wp09_authaudit/message_types.h"
namespace wp09_authaudit { class OperationAuditRecorder { public: AuditEvent record(const UserAction& userAction, const OpsJobSummary* opsJobSummary) const; }; }