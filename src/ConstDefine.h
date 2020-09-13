#ifndef CONSTDEFINE_H
#define CONSTDEFINE_H

#include <QMap>
#include <algorithm>

#define INI_FILE_FULL_NAME "set.ini"

#define CREATE_CONTRACT_DB "CREATE TABLE contracts (id SERIAL, inn TEXT, bic TEXT, bankName TEXT, comment TEXT, startContract TEXT, activateContract TEXT, endContract TEXT, interest TEXT, moneyCod TEXT, moneyCount TEXT);"
#define CREATE_COMPANY_DB "CREATE TABLE company (inn TEXT, kpp TEXT, name TEXT);"
#define CREATE_OSTAT_DB "CREATE TABLE ostat ();"
#define CREATE_USER_DB "CREATE TABLE users (id SERIAL, login TEXT, surname TEXT, name TEXT, fathername TEXT, pass TEXT, position TEXT, unitname TEXT, role TEXT);"
#define CREATE_SESSION_DB "CREATE TABLE sessions (userid TEXT, uuid TEXT, time TEXT);"

static std::string simbolTable(const std::string &arg)
{
    QMap<std::string, std::string> simbols;
    simbols["%3C"] = "<";
    simbols["%20"] = " ";
    simbols["%3E"] = ">";
    simbols["%22"] = "\"";
    return simbols[arg];
}

static void prepareString(std::string &arg)
{
    size_t pos = arg.find('%');
    while (pos != std::string::npos)
    {
        arg.replace(pos, 3, simbolTable(arg.substr(pos, 3)));
        pos = arg.find('%');
    }
}


#define CREATE_BANKS_INDEX_DB ""
#define CREATE_CONTRACT_TYPE_DB ""

#endif // CONSTDEFINE_H
