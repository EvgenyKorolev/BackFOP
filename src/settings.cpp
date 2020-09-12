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

QString Settings::getCbrNameToBicResurce()
{
    return m_cbrNameToBicResurce;
}

void Settings::setCbrNameToBicResurce(const QString &cbrNameToBicResurce)
{
    m_cbrNameToBicResurce = cbrNameToBicResurce;
}

void Settings::loadSettings()
{
    m_dbUserLogin = "rosatom";
    m_dbUserPass = "rosatomfop";
    m_dbName = "rosatom";
    m_dbServerName = "rosatom-db.c5w73kvgbckq.eu-central-1.rds.amazonaws.com";
    m_dbServerAddress = QHostAddress::LocalHost;
    m_dbServerPort = 5432;
    m_serverMaxQueued = 100;
    m_serverMaxThreads = 16;
    m_serverPort = 8000;
    m_cbrNameToBicResurce = "www.cbr.ru/scripts/XML_bic.asp";
}

Settings::Settings(const QString &iniFileFullName) : m_iniFileFullName(iniFileFullName)
{
    loadSettings();
}

Settings::~Settings()
{

}
