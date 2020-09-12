QT -= gui
QT += network sql xml

CONFIG += c++17 console
CONFIG -= app_bundle

TARGET = post
TEMPLATE = app
MOC_DIR = moc
OBJECTS_DIR = obj
UI_DIR = ui
RCC_DIR = rcc
DESTDIR = out

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += \
    /usr/include/Poco/        \
    /usr/include/Poco/Net

LIBS += \
    /usr/lib64/libPocoNet.so   \
    /usr/lib64/libPocoFoundation.so

SOURCES += \
    src/dbowner.cpp \
    src/httprequesthandlerfactory.cpp \
    src/httpserver.cpp \
    src/main.cpp \
    src/requestbiccode.cpp \
    src/requesterror.cpp \
    src/requestgetcontract.cpp \
    src/requestping.cpp \
    src/requestsetcontract.cpp \
    src/settings.cpp \
    src/xmldatahandler.cpp

TRANSLATIONS += \
    hackathonback_ru_RU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/ConstDefine.h \
    src/contract.h \
    src/dbowner.h \
    src/httprequesthandlerfactory.h \
    src/httpserver.h \
    src/requestbiccode.h \
    src/requesterror.h \
    src/requestgetcontract.h \
    src/requestping.h \
    src/requestsetcontract.h \
    src/settings.h \
    src/xmldatahandler.h
