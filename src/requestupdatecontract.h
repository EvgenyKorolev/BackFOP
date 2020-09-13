#ifndef REQUESTUPDATECONTRACT_H
#define REQUESTUPDATECONTRACT_H

#include <Poco/Net/HTTPRequestHandler.h>

class RequestUpdateContract : public Poco::Net::HTTPRequestHandler
{
public:
    RequestUpdateContract();
    void handleRequest(Poco::Net::HTTPServerRequest &requestServer,
                       Poco::Net::HTTPServerResponse &responce);
};

#endif // REQUESTUPDATECONTRACT_H
