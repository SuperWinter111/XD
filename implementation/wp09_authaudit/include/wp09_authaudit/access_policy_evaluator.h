#pragma once
#include "wp09_authaudit/message_types.h"
namespace wp09_authaudit { class AccessPolicyEvaluator { public: AccessDecisionRecord evaluate(const UserAction& userAction) const; }; }