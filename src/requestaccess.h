#ifndef REQUESTACCESS_H
#define REQUESTACCESS_H

#include <Poco/Net/HTTPRequestHandler.h>

class RequestAccess : public Poco::Net::HTTPRequestHandler
{
public:
    RequestAccess();
    void handleRequest(Poco::Net::HTTPServerRequest &requestServer,
                       Poco::Net::HTTPServerResponse &responce);
};

#endif // REQUESTACCESS_H
