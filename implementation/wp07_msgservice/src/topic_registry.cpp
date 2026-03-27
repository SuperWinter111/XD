#include "wp07_msgservice/topic_registry.h"

namespace wp07_msgservice {

bool TopicRegistry::registerTopic(const TopicDefinition& topicDefinition) {
  if (topicDefinition.topic.empty() || topicDefinition.payloadType.empty() ||
      topicDefinition.ownerTeam.empty() || topicDefinition.schemaUri.empty() ||
      topicDefinition.retentionMs <= 0) {
    return false;
  }

  topics_[topicDefinition.topic] = topicDefinition;
  return true;
}

std::optional<TopicDefinition> TopicRegistry::findTopic(const std::string& topic) const {
  const auto it = topics_.find(topic);
  if (it == topics_.end()) {
    return std::nullopt;
  }

  return it->second;
}

std::size_t TopicRegistry::size() const { return topics_.size(); }

}  // namespace wp07_msgservice
