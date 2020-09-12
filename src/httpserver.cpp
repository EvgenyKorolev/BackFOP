#include "httpserver.h"
#include "settings.h"
#include "httprequesthandlerfactory.h"

HttpServer::HttpServer()
{
    Poco::Net::HTTPServerParams* serverSettings = new Poco::Net::HTTPServerParams();
    serverSettings->setMaxQueued(Settings::getInstance().getServerMaxQueued());
    serverSettings->setMaxThreads(Settings::getInstance().getServerMaxThreads());
    m_instanceServer = new Poco::Net::HTTPServer(new HttpRequestHandlerFactory(),
                                                 Poco::Net::ServerSocket(Settings::getInstance().getServerPort()),
                                                 serverSettings);
    m_instanceServer->start();
}

HttpServer::~HttpServer()
{
    m_instanceServer->stop();
}
