#ifndef HTTPREQUESTHANDLERFACTORY_H
#define HTTPREQUESTHANDLERFACTORY_H

#include <Poco/Net/HTTPRequestHandlerFactory.h>

class HttpRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
    HttpRequestHandlerFactory();
    Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request);
};

#endif // HTTPREQUESTHANDLERFACTORY_H
