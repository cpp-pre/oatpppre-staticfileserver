#pragma once

#include "oatpp/web/server/api/ApiController.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/web/protocol/http/outgoing/StreamingBody.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include <oatpppre/StaticFilesHandler.hpp>
#include <oatpppre/StaticFilesManager.hpp>

#include <cassert>

namespace oatpppre {

  class StaticFilesHandler : public oatpp::web::server::HttpRequestHandler {
  public:

    /**
     * \brief Serves files at the given url
     * \param route the route must end with a globbing pattern ( e.g. "/resources/*")
     * \param basePath path on disk where the files are located
     */
    static inline auto mountAtRoute(
      std::shared_ptr<oatpp::web::server::HttpRouter> router, oatpp::String route, oatpp::String basePath) {
      OATPP_ASSERT(*route->std_str().rbegin() == '*');
      auto staticFileHandler = std::make_shared<StaticFilesHandler>(route, basePath);
      router->route("GET", route, staticFileHandler);
      return staticFileHandler;
    }

    StaticFilesHandler(oatpp::String route, oatpp::String basePath = ".")
      : m_route{route}
        , m_filesManager{basePath}
    {}

    /**
     * Handle incoming request and return outgoing response.
     */
    std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& request) override {
      auto filename = request->getPathTail();
      auto content_type = m_filesManager.guessMimeType(filename);
      OATPP_LOGD("Server", "Looking for File %s.", filename->c_str());
      auto file = m_filesManager.getFile(filename);

      if (file != nullptr) {
        OATPP_LOGD("Server", "File %s found returning it with content type %s", filename->c_str(), content_type->c_str());
        auto response = ResponseFactory::createResponse(Status::CODE_200, file);
        response->putHeader(Header::CONTENT_TYPE, content_type);
        return response;
      } else {
        return ResponseFactory::createResponse(Status::CODE_404, filename + " - Not found");
      }
    }

    private:
    oatpp::String m_route;
    StaticFilesManager m_filesManager;
  };

}