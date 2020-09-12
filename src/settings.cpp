#include "settings.h"

quint32 Settings::getDbPort()
{
    return m_dbServerPort;
}

void Settings::setDbPort(quint32 port)
{
    m_dbServerPort = port;
}

QString Settings::getDbName()
{
    return m_dbName;
}

void Settings::setDbName(const QString &dbName)
{
    m_dbName = dbName;
}

QString Settings::getDbServerName()
{
    return m_dbServerName;
}

void Settings::setDbServerName(const QString &dbServerName)
{
    m_dbServerName = dbServerName;
}

QHostAddress Settings::getDbServerAddress()
{
    return m_dbServerAddress;
}

void Settings::setDbServerAddress(const QHostAddress &dbServerAddress)
{
    m_dbServerAddress = dbServerAddress;
}

QString Settings::getDbUserLogin()
{
    return m_dbUserLogin;
}

void Settings::setDbUserLogin(const QString &dbUserLogin)
{
    m_dbUserLogin = dbUserLogin;
}

QString Settings::getDbUserPass()
{
    return m_dbUserPass;
}

void Settings::setDbUserPass(const QString &dbUserPass)
{
    m_dbUserPass = dbUserPass;
}

int Settings::getServerMaxQueued()
{
    return m_serverMaxQueued;
}

void Settings::setServerMaxQueued(int maxQueued)
{
    m_serverMaxQueued = maxQueued;
}

int Settings::getServerMaxThreads()
{
    return m_serverMaxThreads;
}

void Settings::setServerMaxThreads(int maxThreads)
{
    m_serverMaxThreads = maxThreads;
}

int Settings::getServerPort()
{
    return m_serverPort;
}

void Settings::setServerPort(int port)
{
    m_serverPort = port;
}

void Settings::loadSettings()
{
    m_dbUserLogin = "postgres";
    m_dbUserPass = "postgres";
    m_dbName = "FOT";
    m_dbServerName = "localhost";
    m_dbServerAddress = QHostAddress::LocalHost;
    m_dbServerPort = 5432;
    m_serverMaxQueued = 100;
    m_serverMaxThreads = 16;
    m_serverPort = 8000;
}

Settings::Settings(const QString &iniFileFullName) : m_iniFileFullName(iniFileFullName)
{
    loadSettings();
}

Settings::~Settings()
{

}
