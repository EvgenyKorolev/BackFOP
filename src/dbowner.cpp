#include "dbowner.h"
#include "settings.h"

bool DbOwner::execCommand(const QString &sqlCommand)
{
    if (!m_db.isValid())
    {
        if (!reconnect()) return false;
    }
    QSqlQuery query(m_db);
    return query.exec(sqlCommand);
}

bool DbOwner::execCommand(const QString &sqlCommand, Table &ansverTable)
{
    if (!m_db.isValid())
    {
        if (!reconnect()) return false;
    }
    QSqlQuery query(m_db);
    bool ret =  query.exec(sqlCommand);
    while (query.next()) {
        ansverTable.push_back(QStringList());
        QSqlRecord record = query.record();
        int end = record.count();
        for (int i = 0; i < end; ++i)
        {
            ansverTable.back().push_back(record.value(i).toString());
        }
    }
    return ret;
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
