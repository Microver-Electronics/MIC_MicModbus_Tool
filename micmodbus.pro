TARGET = micmodbus
TEMPLATE = app
VERSION = 0.1.0

QT += gui widgets serialport

SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/BatchProcessor.cpp \
    3rdparty/libmodbus/src/modbus.c \
    3rdparty/libmodbus/src/modbus-data.c \
    3rdparty/libmodbus/src/modbus-rtu.c \
    3rdparty/libmodbus/src/modbus-tcp.c \
    src/rtusettingswidget.cpp \
    src/serialsettingswidget.cpp \
    src/tcpipsettingswidget.cpp \
    src/ipaddressctrl.cpp \
    src/iplineedit.cpp

HEADERS += src/mainwindow.h \
    src/BatchProcessor.h \
    3rdparty/libmodbus/src/modbus.h \
    src/serialsettingswidget.h \
    src/imodbus.h \
    src/tcpipsettingswidget.h \
    src/ipaddressctrl.h \
    src/iplineedit.h

INCLUDEPATH += 3rdparty/libmodbus \
               3rdparty/libmodbus/src \
               src

FORMS += forms/mainwindow.ui \
    forms/about.ui	\
    forms/BatchProcessor.ui \
    forms/serialsettingswidget.ui \
    forms/tcpipsettingswidget.ui \
    forms/ipaddressctrl.ui

RESOURCES += \
    data/micmodbus.qrc

RC_FILE += micmodbus.rc

include(deployment.pri)
