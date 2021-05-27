#pragma once

#include "oatpp/core/concurrency/SpinLock.hpp"
#include "oatpp/core/Types.hpp"

#include <unordered_map>
#include <string>

namespace oatpppre {

  class StaticFilesManager {
  private:
    oatpp::String m_basePath;
  public:
    
    StaticFilesManager(const oatpp::String& basePath)
      : m_basePath(basePath)
    {}
    
    oatpp::String getFile(const oatpp::String& path);
    
    oatpp::String guessMimeType(const oatpp::String& filename);
    
  };

}