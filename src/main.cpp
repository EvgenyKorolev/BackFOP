#include <QCoreApplication>
#include <QTextCodec>

#include "httpserver.h"
#include "settings.h"
#include "dbowner.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    Settings::getInstance();
    DbOwner::getInstance();
    qDebug() << DbOwner::getInstance().isValid();
    HttpServer server;
    return a.exec();
}
