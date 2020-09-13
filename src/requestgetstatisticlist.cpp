#include "requestgetstatisticlist.h"
#include "accessmanager.h"
#include "settings.h"
#include "dbowner.h"
#include "contract.h"

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <QDomDocument>
#include <QPair>

struct OstRu
{
    QString bankName;
    QString comment;
    int moneyCount;
};


RequestGetStatisticList::RequestGetStatisticList() : Poco::Net::HTTPRequestHandler()
{

}

void RequestGetStatisticList::handleRequest(Poco::Net::HTTPServerRequest &requestServer, Poco::Net::HTTPServerResponse &responce)
{
    std::string name = requestServer.getURI();
    size_t num = name.find_last_of('/') + 1;
    name = name.substr(num, name.size() - num);
    QDomDocument docRequest = QDomDocument(QString(name.c_str()));
    QDomElement root = docRequest.firstChildElement("statistic");
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

    QString query = QString("SELECT ALL FROM contracts WHERE inn = E'%2';")
            .arg(Settings::getInstance().getDbName())
            .arg(root.attribute("inn"));
    Table ansverTable;
    if (!DbOwner::getInstance().execCommand(query, ansverTable))
    {
        responce.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        QByteArray ret("404 Error");
        responce.sendBuffer(ret.data(), ret.size());
        return;
    }
    QMap<QPair<QString, QString>, OstRu> ansverData;
    auto it = ansverTable.begin();
    while (it != ansverTable.end())
    {
        if(!ansverData.contains(QPair<QString, QString>(it->at(2), it->at(9))))
        {
            ansverData[QPair<QString, QString>(it->at(2), it->at(9))].bankName = it->at(3);
            ansverData[QPair<QString, QString>(it->at(2), it->at(9))].comment = it->at(4);
            ansverData[QPair<QString, QString>(it->at(2), it->at(9))].moneyCount = it->at(10).toInt();
        }
        else
        {
            ansverData[QPair<QString, QString>(it->at(2), it->at(9))].moneyCount += it->at(10).toInt();
        }
        ++it;
    }
    QDomDocument docAnswer = QDomDocument();
    QDomElement rootAnswer = docRequest.firstChildElement("ost");
    docAnswer.appendChild(rootAnswer);
    auto iter = ansverData.begin();
    int number{0};
    while (iter != ansverData.end())
    {
        QDomElement answer = docRequest.firstChildElement(QString("ost%1").arg(number));
        answer.setAttribute("inn", root.attribute("inn"));
        answer.setAttribute("bic", iter.key().first);
        answer.setAttribute("bankName", iter.value().bankName);
        answer.setAttribute("comment", iter.value().comment);
        answer.setAttribute("moneyCod", iter.key().second);
        answer.setAttribute("moneyCount", QString::number(iter.value().moneyCount));
        rootAnswer.appendChild(answer);
        ++iter;
        ++number;
    }
    responce.setStatus(Poco::Net::HTTPResponse::HTTP_FOUND);
    QByteArray ret = docAnswer.toString().toUtf8();
    responce.sendBuffer(ret.data(), ret.size());
}
