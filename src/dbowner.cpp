#include "dbowner.h"
#include "settings.h"

bool DbOwner::execCommand(QSqlQuery &sqlCommand)
{
    if (!m_db.isValid())
    {
        if (!reconnect()) return false;
    }
    QSqlQuery query(m_db);
    return query.exec();
}

bool DbOwner::isValid()
{
    return m_db.isValid();
}

DbOwner::DbOwner()
{
    connect();
}

DbOwner::~DbOwner()
{

}

bool DbOwner::reconnect()
{

}

bool DbOwner::connect()
{
    m_db = QSqlDatabase::addDatabase("QPSQL", Settings::getInstance().getDbName());
    m_db.setHostName(Settings::getInstance().getDbServerName());
    m_db.setDatabaseName(Settings::getInstance().getDbName());
    m_db.setUserName(Settings::getInstance().getDbUserLogin());
    m_db.setPassword(Settings::getInstance().getDbUserPass());
    return m_db.open();
}
