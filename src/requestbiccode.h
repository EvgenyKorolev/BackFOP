#ifndef REQUESTBICCODE_H
#define REQUESTBICCODE_H

#include <Poco/Net/HTTPRequestHandler.h>

class RequestBicCode : public Poco::Net::HTTPRequestHandler
{
public:
    RequestBicCode();
    void handleRequest(Poco::Net::HTTPServerRequest &requestServer,
                       Poco::Net::HTTPServerResponse &responce);
};

#endif // REQUESTBICCODE_H
