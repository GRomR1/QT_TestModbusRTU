INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS                +=   $$PWD/src/modbus-private.h \
                            $$PWD/src/modbus-rtu-private.h \
                            $$PWD/src/modbus-rtu.h \
#                            $$PWD/src/modbus-tcp-private.h \
                            $$PWD/src/modbus-tcp.h \
                            $$PWD/src/modbus-version.h \
                            $$PWD/src/modbus.h

SOURCES                +=   $$PWD/src/modbus.c \
                            $$PWD/src/modbus-data.c \
                            $$PWD/src/modbus-rtu.c \
#                            $$PWD/src/modbus-tcp.c
