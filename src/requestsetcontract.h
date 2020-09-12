#ifndef REQUESTSETCONTRACT_H
#define REQUESTSETCONTRACT_H

#include <Poco/Net/HTTPRequestHandler.h>

class RequestSetContract : public Poco::Net::HTTPRequestHandler
{
public:
    RequestSetContract();
    void handleRequest(Poco::Net::HTTPServerRequest &requestServer,
                       Poco::Net::HTTPServerResponse &responce);
};

#endif // REQUESTSETCONTRACT_H
