#ifndef CONSTDEFINE_H
#define CONSTDEFINE_H

#define INI_FILE_FULL_NAME "set.ini"

#define CREATE_CONTRACT_DB "CREATE TABLE contracts (id SERIAL, inn TEXT, bic TEXT, bankName TEXT, comment TEXT, startContract TEXT, activateContract TEXT, endContract TEXT, interest TEXT, moneyCod TEXT, moneyCount TEXT);"
#define CREATE_COMPANY_DB "CREATE TABLE company (inn TEXT, kpp TEXT, name TEXT);"
#define CREATE_OSTAT_DB "CREATE TABLE ostat ();"
#define CREATE_USER_DB "CREATE TABLE dbusers (id SERIAL, login TEXT, surname TEXT, name TEXT, fathername TEXT, pass TEXT, position TEXT, unitname TEXT, role TEXT);"
#define CREATE_SESSION_DB "CREATE TABLE sessions (userid TEXT, uuid TEXT, time TEXT);"



#define CREATE_BANKS_INDEX_DB ""
#define CREATE_CONTRACT_TYPE_DB ""

#endif // CONSTDEFINE_H
