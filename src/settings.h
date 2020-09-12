#ifndef SETTINGS_H
#define SETTINGS_H

#include "ConstDefine.h"

#include <QSettings>
#include <QHostAddress>

class Settings
{
public:
    static Settings &getInstance()
    {
        static Settings _instance;
        return _instance;
    }
    void loadSettings();

    quint32 getDbPort();
    void setDbPort(quint32 port);
    QString getDbName();
    void setDbName(const QString &dbName);
    QString getDbServerName();
    void setDbServerName(const QString &dbServerName);
    QHostAddress getDbServerAddress();
    void setDbServerAddress(const QHostAddress &dbServerAddress);
    QString getDbUserLogin();
    void setDbUserLogin(const QString &dbUserLogin);
    QString getDbUserPass();
    void setDbUserPass(const QString &dbUserPass);

    int getServerMaxQueued();
    void setServerMaxQueued(int maxQueued);
    int getServerMaxThreads();
    void setServerMaxThreads(int maxThreads);
    int getServerPort();
    void setServerPort(int port);

    QString getCbrNameToBicResurce();
    void setCbrNameToBicResurce(const QString &cbrNameToBicResurce);

signals:
    void changedSettings();

private:
    Settings(const QString &iniFileFullName = INI_FILE_FULL_NAME);
    ~Settings();
    Settings(const Settings&) = delete;
    Settings(Settings&&) = delete;
    Settings &operator=(const Settings&) = delete;
    Settings &operator=(const Settings&&) = delete;

    QString m_iniFileFullName;
    QString m_dbName;
    QString m_dbServerName;
    QHostAddress m_dbServerAddress;
    QString m_dbUserLogin;
    QString m_dbUserPass;
    quint32 m_dbServerPort;
    QString m_cbrNameToBicResurce;

    int m_serverMaxQueued;
    int m_serverMaxThreads;
    int m_serverPort;

};

#endif // SETTINGS_H
