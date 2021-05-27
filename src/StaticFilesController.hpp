#pragma once

#include "oatpp/web/server/api/ApiController.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/web/protocol/http/outgoing/StreamingBody.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include <StaticFilesManager.hpp>

#include <iostream>

#include OATPP_CODEGEN_BEGIN(ApiController)


class StaticFilesHandler : public oatpp::web::server::HttpRequestHandler {
  StaticFilesManager m_filesManager{"."};
public:

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

};

/**
 * StaticFilesController for Static file serving. Extends &id:oatpp::web::server::api::ApiController;. <br>
 * Should be used with oatpp Simple API and multithreaded server. <br>
 *   <li>&id:ENDPOINT;("GET", "/{filename}", getResource) - Serve Swagger-UI resources.</li>
 * </ul>
 */
class StaticFilesController : public oatpp::web::server::api::ApiController {
private:
public:
  StaticFilesController(const std::shared_ptr<ObjectMapper>& objectMapper)
    : oatpp::web::server::api::ApiController(objectMapper)
  {}

  static std::shared_ptr<StaticFilesController> createShared(
    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
  ){
    return std::make_shared<StaticFilesController>(objectMapper);
  }

 
  ENDPOINT("GET", "/hello/{filename}", getHello, PATH(String, filename)) {
    return createResponse(Status::CODE_200, filename);
  }

  
};
  
#include OATPP_CODEGEN_END(ApiController)
