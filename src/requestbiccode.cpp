#include "requestbiccode.h"
#include "settings.h"

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/URI.h>
#include <QByteArray>
#include <iostream>

RequestBicCode::RequestBicCode() : Poco::Net::HTTPRequestHandler()
{

}

void RequestBicCode::handleRequest(Poco::Net::HTTPServerRequest &requestServer, Poco::Net::HTTPServerResponse &responce)
{
    std::string name = requestServer.getURI();
    size_t num = name.find_last_of('/');
    num = name.find_last_of('/', num - 1) + 1;
    name = name.substr(num, name.size() - num);
    try
    {
        Poco::URI uri(Settings::getInstance().getCbrNameToBicResurce().toStdString().c_str());
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        std::string path(uri.getPathAndQuery());
        //path += std::string("?name=") + name + std::string("&bic=%D0%90%D0%92%D0%A2%D0%9E");
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET,
                                   path, Poco::Net::HTTPMessage::HTTP_1_1);
        std::cout << "Send request to CRB to " << path << std::endl;
        session.sendRequest(request);
        std::cout << "Sended request to CRB to " << path << std::endl;
        Poco::Net::HTTPResponse res;
        std::cout << res.getStatus() << " " << res.getReason() << std::endl;

        std::istream &is = session.receiveResponse(res);
        Poco::StreamCopier::copyStream(is, std::cout);
    } catch (...)
    {
        responce.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        responce.set("Acces-Control-Allow-Origin", "*");
        responce.set("Content-type:", "text/html");
        QByteArray ret("404");
        responce.sendBuffer(ret.data(), ret.size());
    }




    responce.setStatus(Poco::Net::HTTPResponse::HTTP_FOUND);
    responce.set("Acces-Control-Allow-Origin", "*");
    responce.set("Content-type:", "text/html");
    QByteArray ret("pong");
    responce.sendBuffer(ret.data(), ret.size());
}
