#include "requestgetcontract.h"
#include "accessmanager.h"
#include "settings.h"
#include "dbowner.h"
#include "contract.h"

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <QDomDocument>

RequestGetContract::RequestGetContract() : Poco::Net::HTTPRequestHandler()
{

}

void RequestGetContract::handleRequest(Poco::Net::HTTPServerRequest &requestServer, Poco::Net::HTTPServerResponse &responce)
{
    std::string name = requestServer.getURI();
    size_t num = name.find_last_of('/');
    num = name.find_last_of('/', num - 1) + 1;
    name = name.substr(num, name.size() - num);
    QDomDocument docRequest;
    docRequest.setContent(QString(name.c_str()));
    QDomElement root = docRequest.firstChildElement("contract");
    auto tmp = AccessManager::testSessin(root.attribute("uuid"));
    QString unit = tmp.first;
    QString role = tmp.second;
    QString inn = AccessManager::getInnFromId(unit);
    if (inn != root.attribute("inn"))
    {
        responce.setStatus(Poco::Net::HTTPResponse::HTTP_FOUND);
        responce.set("Acces-Control-Allow-Origin", "*");
        responce.set("Content-type:", "text/html");
        QByteArray ret("404 forbidden");
        responce.sendBuffer(ret.data(), ret.size());
        return;
    }
    QString whereReq;
    bool needEnd{false};
    if (root.attribute("inn") != "")
    {
        whereReq += QString(" inn = E'%1'").arg(root.attribute("inn"));
        needEnd = true;
    }
    if (root.attribute("bic") != "")
    {
        if (needEnd) whereReq += " AND ";
        whereReq += QString("bic = E'%1' ").arg(root.attribute("bic"));
        needEnd = true;
    }
    if (root.attribute("bankName") != "")
    {
        if (needEnd) whereReq += " AND ";
        whereReq += QString("bankName = E'%1'").arg(root.attribute("bankName"));
        needEnd = true;
    }
    if (root.attribute("comment") != "")
    {
        if (needEnd) whereReq += " AND ";
        whereReq += QString("comment = E'%1'").arg(root.attribute("comment"));
        needEnd = true;
    }
    if (root.attribute("startContract") != "")
    {
        if (needEnd) whereReq += " AND ";
        whereReq += QString("startContract = E'%1'").arg(root.attribute("startContract"));
        needEnd = true;
    }
    if (root.attribute("activateContract") != "")
    {
        if (needEnd) whereReq += " AND ";
        whereReq += QString("activateContract = E'%1'").arg(root.attribute("activateContract"));
        needEnd = true;
    }
    if (root.attribute("endContract") != "")
    {
        if (needEnd) whereReq += " AND ";
        whereReq += QString("endContract = E'%1'").arg(root.attribute("endContract"));
        needEnd = true;
    }
    if (root.attribute("interest") != "")
    {
        if (needEnd) whereReq += " AND ";
        whereReq += QString("interest = E'%1'").arg(root.attribute("interest"));
        needEnd = true;
    }
    if (root.attribute("moneyCod") != "")
    {
        if (needEnd) whereReq += " AND ";
        whereReq += QString("moneyCod = E'%1'").arg(root.attribute("moneyCod"));
        needEnd = true;
    }
    if (root.attribute("moneyCount") != "")
    {
        if (needEnd) whereReq += " AND ";
        whereReq += QString("moneyCount = E'%1'").arg(root.attribute("moneyCount"));
        needEnd = true;
    }
    QString query = QString("SELECT * FROM contracts WHERE %1;")
            .arg(whereReq);
    Table ansverTable;
    if (!DbOwner::getInstance().execCommand(query, ansverTable))
    {
        responce.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        responce.set("Acces-Control-Allow-Origin", "*");
        responce.set("Content-type:", "text/html");
        QByteArray ret("404 Error");
        responce.sendBuffer(ret.data(), ret.size());
        return;
    }
    QDomDocument docAnswer = QDomDocument();
    QDomElement rootAnswer = docRequest.firstChildElement("contracts");
    docAnswer.appendChild(rootAnswer);
    auto it = ansverTable.begin();
    int number{0};
    while (it != ansverTable.end())
    {
        QDomElement answer = docRequest.firstChildElement(QString("contracts%1").arg(number));
        answer.setAttribute("id", it->at(0));
        answer.setAttribute("inn", it->at(1));
        answer.setAttribute("bic", it->at(2));
        answer.setAttribute("bankName", it->at(3));
        answer.setAttribute("comment", it->at(4));
        answer.setAttribute("startContract", it->at(5));
        answer.setAttribute("activateContract", it->at(6));
        answer.setAttribute("endContract", it->at(7));
        answer.setAttribute("interest", it->at(8));
        answer.setAttribute("moneyCod", it->at(9));
        answer.setAttribute("moneyCount", it->at(10));
        rootAnswer.appendChild(answer);
        ++it;
        ++number;
    }
    responce.setStatus(Poco::Net::HTTPResponse::HTTP_FOUND);
    responce.set("Acces-Control-Allow-Origin", "*");
    responce.set("Content-type:", "text/html");
    QByteArray ret = docAnswer.toString().toUtf8();
    responce.sendBuffer(ret.data(), ret.size());
}
