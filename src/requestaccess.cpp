#include "requestaccess.h"
#include "settings.h"
#include "dbowner.h"
#include "contract.h"

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPCookie.h>
#include <QDomDocument>
#include <QDateTime>
#include <QUuid>

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
    QString query = QString("SELECT ALL FROM users WHERE login = E'%2' AND passw = E'%3';")
            .arg(Settings::getInstance().getDbName())
            .arg(root.attribute("login"))
            .arg(root.attribute("pass"));
    Table ansverTable;
    if (!DbOwner::getInstance().execCommand(query, ansverTable))
    {
        responce.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        responce.set("Acces-Control-Allow-Origin", "*");
        responce.set("Content-type:", "text/html");
        QByteArray ret("404 forbidden");
        responce.sendBuffer(ret.data(), ret.size());
        return;
    }
    if (ansverTable.size() != 1)
    {
        responce.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        responce.set("Acces-Control-Allow-Origin", "*");
        responce.set("Content-type:", "text/html");
        QByteArray ret("404 forbidden");
        responce.sendBuffer(ret.data(), ret.size());
        return;
    }
    QUuid uid(QString::number(QDateTime::currentMSecsSinceEpoch()));
    QString uuid = uid.toString();
    QString querySave = QString("INSERT INTO sessions (userid, uuid, time) "
                            "VALUES(E'%2', E'%3', E'%4');")
            .arg(Settings::getInstance().getDbName())
            .arg(ansverTable.at(0).at(0))
            .arg(uuid)
            .arg(QString::number(QDateTime::currentMSecsSinceEpoch()));
    QDomDocument docAnswer = QDomDocument();
    QDomElement rootAnswer = docRequest.firstChildElement("user");
    docAnswer.appendChild(rootAnswer);
        rootAnswer.setAttribute("login", ansverTable.at(0).at(1));
        rootAnswer.setAttribute("surname", ansverTable.at(0).at(2));
        rootAnswer.setAttribute("name", ansverTable.at(0).at(3));
        rootAnswer.setAttribute("fathername", ansverTable.at(0).at(4));
        rootAnswer.setAttribute("position", ansverTable.at(0).at(6));
        rootAnswer.setAttribute("unitname", ansverTable.at(0).at(7));
        rootAnswer.setAttribute("role", ansverTable.at(0).at(8));
        rootAnswer.setAttribute("session", uuid);
    responce.setStatus(Poco::Net::HTTPResponse::HTTP_FOUND);
    responce.set("Acces-Control-Allow-Origin", "*");
    responce.set("Content-type:", "text/html");
    Poco::Net::HTTPCookie cookie("session", uuid.toStdString());
    responce.addCookie(cookie);
    QByteArray ret = docAnswer.toString().toUtf8();
    responce.sendBuffer(ret.data(), ret.size());
}
