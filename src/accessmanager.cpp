#include "accessmanager.h"
#include "settings.h"
#include "dbowner.h"

AccessManager::AccessManager()
{

}

std::pair<QString, QString> AccessManager::testSessin(QString uuid)
{
    QString queryUid = QString("SELECT ALL FROM sessions WHERE uuid = E'%1';")
            .arg(uuid);
    Table uuidTable;
    if (!DbOwner::getInstance().execCommand(queryUid, uuidTable))
    {
        return std::make_pair("", "");
    }
    if (uuidTable.size() != 1) return std::make_pair("", "");
    QString queryUser = QString("SELECT ALL FROM users WHERE userid = E'%1';")
            .arg(uuidTable.at(0).at(0));
    Table ansverTable;
    if (!DbOwner::getInstance().execCommand(queryUser, ansverTable))
    {
        return std::make_pair("", "");
    }
    if (ansverTable.size() != 1) return std::make_pair("", "");
    return std::make_pair(ansverTable.at(0).at(7), ansverTable.at(0).at(8));
}

QString AccessManager::getInnFromId(QString id)
{
    QString queryInn = QString("SELECT ALL FROM company WHERE ID = E'%1';")
            .arg(id);
    Table idTable;
    if (!DbOwner::getInstance().execCommand(queryInn, idTable))
    {
        return "";
    }
    if (idTable.size() != 1) return "";
    return idTable.at(0).at(1);
}

