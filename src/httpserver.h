#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <Poco/Net/HTTPServer.h>

class HttpServer
{
public:
    HttpServer();
    ~HttpServer();
    void messageHandler();
private:
    Poco::Net::HTTPServer *m_instanceServer;
};

#endif // HTTPSERVER_H
