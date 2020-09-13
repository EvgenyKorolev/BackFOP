#include "requestsetcontract.h"
#include "accessmanager.h"
#include "settings.h"
#include "dbowner.h"
#include "contract.h"

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <QDomDocument>

RequestSetContract::RequestSetContract() : Poco::Net::HTTPRequestHandler()
{

}

void RequestSetContract::handleRequest(Poco::Net::HTTPServerRequest &requestServer, Poco::Net::HTTPServerResponse &responce)
{
    std::string name = requestServer.getURI();
    size_t num = name.find_last_of('/') + 1;
    name = name.substr(num, name.size() - num);
    QDomDocument docRequest = QDomDocument(QString(name.c_str()));
    QDomElement root = docRequest.firstChildElement("contract");
    Contract contract;
    contract.inn = root.attribute("inn");
    contract.bic = root.attribute("bic");
    contract.bankName = root.attribute("bankName");
    contract.comment = root.attribute("comment");
    contract.startContract = root.attribute("startContract");
    contract.activateContract = root.attribute("activateContract");
    contract.endContract = root.attribute("endContract");
    contract.interest = root.attribute("interest");
    contract.moneyCod = root.attribute("moneyCod");
    contract.moneyCount = root.attribute("moneyCount");
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
    if (contract.inn == "" || contract.bic == "" || contract.bankName == "" ||
            contract.startContract == "" || contract.activateContract == "" ||
            contract.endContract =="" || contract.interest == "" || contract.moneyCod == "" ||
            contract.moneyCount == "")
    {
        responce.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        QByteArray ret("404 Error format");
        responce.sendBuffer(ret.data(), ret.size());
        return;
    }
    QString query = QString("INSERT INTO contracts (inn, bic, bankName, comment, startContract, "
                            "activateContract, endContract, interest, moneyCod, moneyCount) "
                            "VALUES(E'%2', E'%3', E'%4', E'%5', E'%6', E'%7', E'%8', E'%9', E'%10', "
                            "E'%11');")
            .arg(Settings::getInstance().getDbName())
            .arg(contract.inn)
            .arg(contract.bic)
            .arg(contract.bankName)
            .arg(contract.comment)
            .arg(contract.startContract)
            .arg(contract.activateContract)
            .arg(contract.endContract)
            .arg(contract.interest)
            .arg(contract.moneyCod)
            .arg(contract.moneyCount);
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
