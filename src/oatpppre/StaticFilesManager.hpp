#pragma once

#include "oatpp/core/concurrency/SpinLock.hpp"
#include "oatpp/core/Types.hpp"

#include <unordered_map>
#include <string>
#include <utility>

namespace oatpppre {

  class StaticFilesManager {
  private:
    oatpp::String m_basePath;
  public:
    
    StaticFilesManager(const oatpp::String& basePath)
      : m_basePath(basePath)
    {}
    
    std::pair<oatpp::String,oatpp::String> getFile(const oatpp::String& path);
    
    oatpp::String guessMimeType(const oatpp::String& filename);
    
  };

}