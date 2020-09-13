#include "httprequesthandlerfactory.h"

#include "Poco/Net/HTTPServerRequest.h"

#include "requesterror.h"
#include "requestping.h"
#include "requestbiccode.h"
#include "requestsetcontract.h"
#include "requestgetcontract.h"
#include "requestupdatecontract.h"
#include "requestgetstatisticlist.h"

HttpRequestHandlerFactory::HttpRequestHandlerFactory()
{

}

Poco::Net::HTTPRequestHandler *HttpRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest &request)
{
    if (!request.getURI().find("/api/ping/"))
        return new RequestPing();
    else if (!request.getURI().find("/api/NameToBic/"))
        return new RequestBicCode();
    else if (!request.getURI().find("/api/setContract/"))
        return new RequestSetContract();
    else if (!request.getURI().find("/api/getContracts/"))
        return new RequestGetContract();
    else if (!request.getURI().find("/api/updatetContract/"))
        return new RequestUpdateContract();
    else if (!request.getURI().find("/api/getStatistics/"))
        return new RequestGetStatisticList();


//    else if (!request.getURI().find("/api/delContract/"))
//        return new RequestSetContract();
//    else if (!request.getURI().find("/api/getConsolidated/"))
//        return new RequestSetContract();
//    else if (!request.getURI().find("/api/getCompany/"))
//        return new RequestSetContract();
//    else if (!request.getURI().find("/api/setCompany/"))
//        return new RequestSetContract();
//    else if (!request.getURI().find("/api/updateCompany/"))
//        return new RequestSetContract();
//    else if (!request.getURI().find("/api/delCompany/"))
//        return new RequestSetContract();
//    else if (!request.getURI().find("/api/getCompanyList/"))
//        return new RequestSetContract();
//    else if (!request.getURI().find("/api/getUser/"))
//        return new RequestSetContract();
//    else if (!request.getURI().find("/api/setUser/"))
//        return new RequestSetContract();
//    else if (!request.getURI().find("/api/updateUser/"))
//        return new RequestSetContract();
//    else if (!request.getURI().find("/api/delUser/"))
//        return new RequestSetContract();
//    else if (!request.getURI().find("/api/getUserList/"))
//        return new RequestSetContract();
    else
        return new RequestError();
}
