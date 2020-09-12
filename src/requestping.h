#ifndef REQUESTPING_H
#define REQUESTPING_H

#include "Poco/Net/HTTPRequestHandler.h"

class RequestPing : public Poco::Net::HTTPRequestHandler
{
public:
    RequestPing();
    void handleRequest(Poco::Net::HTTPServerRequest &requestServer, Poco::Net::HTTPServerResponse &responce);
};

#endif // REQUESTPING_H
