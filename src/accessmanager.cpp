#include "accessmanager.h"
#include "settings.h"
#include "dbowner.h"

AccessManager::AccessManager()
{

}

std::pair<QString, QString> AccessManager::testSessin(QString uuid)
{
    QString queryUid = QString("SELECT ALL FROM %1.sessions WHERE uuid = E'%2';")
            .arg(Settings::getInstance().getDbName())
            .arg(uuid);
    Table uuidTable;
    if (!DbOwner::getInstance().execCommand(queryUid, uuidTable))
    {
        return std::make_pair("", "");
    }
    if (uuidTable.size() != 1) return std::make_pair("", "");
    QString queryUser = QString("SELECT ALL FROM %1.users WHERE userid = E'%2';")
            .arg(Settings::getInstance().getDbName())
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
    QString queryInn = QString("SELECT ALL FROM %1.units WHERE ID = E'%2';")
            .arg(Settings::getInstance().getDbName())
            .arg(id);
    Table idTable;
    if (!DbOwner::getInstance().execCommand(queryInn, idTable))
    {
        return "";
    }
    if (idTable.size() != 1) return "";
    return idTable.at(0).at(1);
}

