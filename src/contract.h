#ifndef CONTRACT_H
#define CONTRACT_H

#include <QString>

struct Contract
{
    QString inn;
    QString bic;
    QString bankName;
    QString comment;
    QString startContract;
    QString activateContract;
    QString endContract;
    QString interest;
    QString moneyCod;
    QString moneyCount;
};

#endif // CONTRACT_H
