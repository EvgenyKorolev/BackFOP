#include "requesterror.h"

#include <Poco/Net/HTTPServerResponse.h>
#include <QByteArray>

RequestError::RequestError() : Poco::Net::HTTPRequestHandler()
{

}

void RequestError::handleRequest(Poco::Net::HTTPServerRequest &requestServer,
                                 Poco::Net::HTTPServerResponse &responce)
{
    (void)requestServer;
    responce.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    QByteArray ret("404");
    responce.sendBuffer(ret.data(), ret.size());
}
