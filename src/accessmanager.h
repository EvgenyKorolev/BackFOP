#ifndef ACCESSMANAGER_H
#define ACCESSMANAGER_H

#include <QString>
#include <utility>

class AccessManager
{
public:
    AccessManager();
    static std::pair<QString, QString> testSessin(QString uuid);
    static QString getInnFromId(QString id);
};

#endif // ACCESSMANAGER_H
