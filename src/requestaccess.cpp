#include "requestaccess.h"
#include "settings.h"
#include "dbowner.h"
#include "contract.h"

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <QDomDocument>

RequestAccess::RequestAccess() : Poco::Net::HTTPRequestHandler()
{

}

void RequestAccess::handleRequest(Poco::Net::HTTPServerRequest &requestServer, Poco::Net::HTTPServerResponse &responce)
{
    std::string name = requestServer.getURI();
    size_t num = name.find_last_of('/') + 1;
    name = name.substr(num, name.size() - num);
    QDomDocument docRequest = QDomDocument(QString(name.c_str()));
    QDomElement root = docRequest.firstChildElement("userAccess");
    QString query = QString("SELECT ALL FROM %1.contracts WHERE login = E'%2' AND passw = E'%3';")
            .arg(Settings::getInstance().getDbName())
            .arg(root.attribute("login"))
            .arg(root.attribute("pass"));
    Table ansverTable;
    if (!DbOwner::getInstance().execCommand(query, ansverTable))
    {
        responce.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        QByteArray ret("404 forbidden");
        responce.sendBuffer(ret.data(), ret.size());
        return;
    }
    if (ansverTable.size() != 1)
    {
        responce.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        QByteArray ret("404 forbidden");
        responce.sendBuffer(ret.data(), ret.size());
        return;
    }
    QDomDocument docAnswer = QDomDocument();
    QDomElement rootAnswer = docRequest.firstChildElement("user");
    docAnswer.appendChild(rootAnswer);
        rootAnswer.setAttribute("login", ansverTable.at(0).at(0));
        rootAnswer.setAttribute("name", ansverTable.at(0).at(1));
        rootAnswer.setAttribute("surname", ansverTable.at(0).at(2));
        rootAnswer.setAttribute("fathername", ansverTable.at(0).at(3));
        rootAnswer.setAttribute("position", ansverTable.at(0).at(4));
        rootAnswer.setAttribute("unitname", ansverTable.at(0).at(5));
        rootAnswer.setAttribute("role", ansverTable.at(0).at(6));
    responce.setStatus(Poco::Net::HTTPResponse::HTTP_FOUND);
    QByteArray ret = docAnswer.toString().toUtf8();
    responce.sendBuffer(ret.data(), ret.size());
}
