#include <oatpppre/StaticFilesManager.hpp>

#include <filesystem>
#include <oatpppre/mime/mime.types.hpp>
#include <pre/file/string.hpp> 

#include <cstring>
#include <stdarg.h>

using namespace oatpppre;

//! \return a pair consisting of mimetype and content
std::pair<oatpp::String,oatpp::String> StaticFilesManager::getFile(const oatpp::String& path) {
  if(!path) {
    return std::make_pair(nullptr, nullptr);
  }
  oatpp::String filename = m_basePath + "/" + path;

  if (std::filesystem::is_directory(filename->c_str())) {
    OATPP_LOGD("StaticFilesManager::getFile", "File %s is directory", filename->c_str());
    filename = m_basePath + "/" + path + "/index.html";
    OATPP_LOGD("StaticFilesManager::getFile", "Changing for index : %s", filename->c_str());
  } 

  if (!std::filesystem::exists(filename->c_str())) {
    return std::make_pair(nullptr, nullptr);
  }

  auto mimeType = guessMimeType(filename->c_str());

  std::error_condition ec;
  auto file_content = pre::file::to_string(filename->c_str(), ec);
  oatpp::String file = file_content.data();
  return std::make_pair(mimeType, (ec) ? nullptr : file);
}

oatpp::String StaticFilesManager::guessMimeType(const oatpp::String& filename) {
  oatpp::String content_type = "application/octet-stream";
  auto extension = std::filesystem::path(filename->c_str()).extension();
  OATPP_LOGD("StaticFilesManager::guessMimeType", "extension %s", extension.generic_string().data());

  if (mime::mime_types.find(extension.generic_string()) != mime::mime_types.end()) {
    content_type = mime::mime_types.at(extension.generic_string());
  }

  return content_type;
}
