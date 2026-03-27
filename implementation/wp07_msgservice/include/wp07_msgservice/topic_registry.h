#pragma once

#include <optional>
#include <string>
#include <unordered_map>

#include "wp07_msgservice/message_types.h"

namespace wp07_msgservice {

class TopicRegistry {
 public:
  bool registerTopic(const TopicDefinition& topicDefinition);
  std::optional<TopicDefinition> findTopic(const std::string& topic) const;
  std::size_t size() const;

 private:
  std::unordered_map<std::string, TopicDefinition> topics_;
};

}  // namespace wp07_msgservice
