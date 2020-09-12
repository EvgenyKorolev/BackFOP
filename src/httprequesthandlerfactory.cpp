#include "httprequesthandlerfactory.h"

#include "Poco/Net/HTTPServerRequest.h"

#include "requesterror.h"
#include "requestping.h"

HttpRequestHandlerFactory::HttpRequestHandlerFactory()
{

}

Poco::Net::HTTPRequestHandler *HttpRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest &request)
{
    if (!request.getURI().find("/api/ping/"))
        return new RequestPing();
    else
        return new RequestError();
}
