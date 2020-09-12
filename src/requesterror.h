#ifndef REQUESTERROR_H
#define REQUESTERROR_H

#include "Poco/Net/HTTPRequestHandler.h"

class RequestError : public Poco::Net::HTTPRequestHandler
{
public:
    RequestError();
    void handleRequest(Poco::Net::HTTPServerRequest &requestServer, Poco::Net::HTTPServerResponse &responce);
};

#endif // REQUESTERROR_H
