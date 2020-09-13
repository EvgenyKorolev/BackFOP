#ifndef REQUESTGETSTATISTICLIST_H
#define REQUESTGETSTATISTICLIST_H

#include <Poco/Net/HTTPRequestHandler.h>

class RequestGetStatisticList : public Poco::Net::HTTPRequestHandler
{
public:
    RequestGetStatisticList();
    void handleRequest(Poco::Net::HTTPServerRequest &requestServer,
                       Poco::Net::HTTPServerResponse &responce);
};

#endif // REQUESTGETSTATISTICLIST_H
