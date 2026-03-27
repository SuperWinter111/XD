#pragma once
#include <string>
namespace wp09_authaudit {
struct UserAction { std::string traceId; std::string actorId; std::string action; std::string targetId; bool privileged{false}; };
struct SecurityEvent { std::string traceId; std::string sourceNodeId; std::string severity; };
struct OpsJobSummary { std::string traceId; std::string jobId; std::string operation; };
struct AccessDecisionRecord { std::string traceId; std::string actorId; std::string action; bool allowed{false}; std::string rationale; };
struct AuditEvent { std::string traceId; std::string actorId; std::string action; std::string targetId; std::string eventType; };
struct SecurityReviewRecord { std::string traceId; std::string sourceNodeId; std::string reviewLevel; std::string referenceAction; };
}