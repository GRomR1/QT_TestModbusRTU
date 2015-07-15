QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
