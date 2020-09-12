#ifndef DBOWNER_H
#define DBOWNER_H

#include <QString>
#include <QVector>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDatabase>

class DbOwner
{
public:
    static DbOwner &getInstance()
    {
        static DbOwner _instance;
        return _instance;
    }
    bool execCommand(QString &sqlCommand);
    bool isValid();


private:
    DbOwner();
    DbOwner(const DbOwner&) = delete ;
    DbOwner(DbOwner&&) = delete ;
    ~DbOwner();
    DbOwner &operator=(const DbOwner&) = delete;
    DbOwner &operator=(DbOwner&&) = delete ;
    bool reconnect();
    bool connect();

    QSqlDatabase m_db;
};

#endif // DBOWNER_H
