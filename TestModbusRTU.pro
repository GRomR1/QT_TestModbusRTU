QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(libmodbus-3.0.6/libmodbus.pri)

TARGET = CraneEmulator
TEMPLATE = app

SOURCES += main.cpp \
    PortSelector.cpp \
    PortListener.cpp \
    MainWindow.cpp \

HEADERS  += \
    PortSelector.h \
    PortListener.h \
    MainWindow.h \
    ../Defines.h \

FORMS    += \
    PortSelector.ui \
    MainWindow.ui \
