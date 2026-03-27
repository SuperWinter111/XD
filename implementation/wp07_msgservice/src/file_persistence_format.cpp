#include "wp07_msgservice/file_persistence_format.h"

#include <filesystem>
#include <fstream>

namespace wp07_msgservice {

void FilePersistenceFormat::ensureFileHeader(const std::filesystem::path& filePath,
                                             const std::string& formatVersion,
                                             const std::string& columns) {
  if (filePath.has_parent_path()) {
    std::filesystem::create_directories(filePath.parent_path());
  }

  if (std::filesystem::exists(filePath) && std::filesystem::file_size(filePath) > 0) {
    return;
  }

  std::ofstream output(filePath, std::ios::out | std::ios::trunc);
  output << "#format=" << formatVersion << '\n';
  output << "#columns=" << columns << '\n';
}

}  // namespace wp07_msgservice