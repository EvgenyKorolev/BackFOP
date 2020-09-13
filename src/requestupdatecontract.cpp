#include "requestupdatecontract.h"
#include "accessmanager.h"
#include "settings.h"
#include "dbowner.h"
#include "contract.h"

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <QDomDocument>

RequestUpdateContract::RequestUpdateContract()
{

}

void RequestUpdateContract::handleRequest(Poco::Net::HTTPServerRequest &requestServer, Poco::Net::HTTPServerResponse &responce)
{
    std::string name = requestServer.getURI();
    size_t num = name.find_last_of('/') + 1;
    name = name.substr(num, name.size() - num);
    QDomDocument docRequest = QDomDocument(QString(name.c_str()));
    QDomElement root = docRequest.firstChildElement("contract");
    auto tmp = AccessManager::testSessin(root.attribute("uuid"));
    QString unit = tmp.first;
    QString role = tmp.second;
    QString inn = AccessManager::getInnFromId(unit);
    if (inn != root.attribute("inn"))
    {
        responce.setStatus(Poco::Net::HTTPResponse::HTTP_FOUND);
        QByteArray ret("404 forbidden");
        responce.sendBuffer(ret.data(), ret.size());
        return;
    }
    QString updateReq;
    if (root.attribute("inn") != "")
    {
        updateReq += QString(" inn = E'%1' ").arg(root.attribute("inn"));
    }
    if (root.attribute("bic") != "")
    {
        updateReq += QString("bic = E'%1' ").arg(root.attribute("bic"));
    }
    if (root.attribute("bankName") != "")
    {
        updateReq += QString("bankName = E'%1' ").arg(root.attribute("bankName"));
    }
    if (root.attribute("comment") != "")
    {
        updateReq += QString("comment = E'%1' ").arg(root.attribute("comment"));
    }
    if (root.attribute("startContract") != "")
    {
        updateReq += QString("startContract = E'%1' ").arg(root.attribute("startContract"));
    }
    if (root.attribute("activateContract") != "")
    {
        updateReq += QString("activateContract = E'%1' ").arg(root.attribute("activateContract"));
    }
    if (root.attribute("endContract") != "")
    {
        updateReq += QString("endContract = E'%1' ").arg(root.attribute("endContract"));
    }
    if (root.attribute("interest") != "")
    {
        updateReq += QString("interest = E'%1' ").arg(root.attribute("interest"));
    }
    if (root.attribute("moneyCod") != "")
    {
        updateReq += QString("moneyCod = E'%1' ").arg(root.attribute("moneyCod"));
    }
    if (root.attribute("moneyCount") != "")
    {
        updateReq += QString("moneyCount = E'%1' ").arg(root.attribute("moneyCount"));
    }
    QString query = QString("UPDATE contracts SET %2 WHERE inn = E'%3');")
            .arg(Settings::getInstance().getDbName())
            .arg(updateReq)
            .arg(root.attribute("id"));
    if (!DbOwner::getInstance().execCommand(query))
    {
        responce.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        QByteArray ret("404 Error");
        responce.sendBuffer(ret.data(), ret.size());
        return;
    }
    responce.setStatus(Poco::Net::HTTPResponse::HTTP_FOUND);
    QByteArray ret("200 OK");
    responce.sendBuffer(ret.data(), ret.size());
}
