#include "requestping.h"

#include <Poco/Net/HTTPServerResponse.h>
#include <QByteArray>

RequestPing::RequestPing() : Poco::Net::HTTPRequestHandler()
{

}

void RequestPing::handleRequest(Poco::Net::HTTPServerRequest &requestServer, Poco::Net::HTTPServerResponse &responce)
{
    (void)requestServer;
    responce.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    responce.set("Acces-Control-Allow-Origin", "*");
    responce.set("Content-type:", "text/html");
    QByteArray ret("pong");
    responce.sendBuffer(ret.data(), ret.size());
}
