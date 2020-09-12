#ifndef REQUESTGETCONTRACT_H
#define REQUESTGETCONTRACT_H

#include <Poco/Net/HTTPRequestHandler.h>

class RequestGetContract : public Poco::Net::HTTPRequestHandler
{
public:
    RequestGetContract();
    void handleRequest(Poco::Net::HTTPServerRequest &requestServer,
                       Poco::Net::HTTPServerResponse &responce);
};

#endif // REQUESTGETCONTRACT_H
