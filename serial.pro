#-------------------------------------------------
#
# Project created by QtCreator 2021-03-11T17:07:29
#
#-------------------------------------------------

QT       += core gui
QT       += core gui serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serial
TEMPLATE = app


SOURCES += main.cpp\
        serial.cpp \
    Can/canmatrix.cpp \
    Can/canrxthread.cpp \
    Can/cantxthread.cpp \
    Can/xlCANFunctions.cpp \
    Can/zlgCANFunctions.cpp \
    Can/CanComm.c

HEADERS  += serial.h \
    Can/CanComm.h \
    Can/canmatrix.h \
    Can/canrxthread.h \
    Can/cantxthread.h \
    Can/ControlCAN.h \
    Can/vxlapi.h \
    Can/xlCANFunctions.h \
    Can/zlgCANFunctions.h

FORMS    += serial.ui

win32: LIBS += -L$$PWD -lvxlapi -lControlCAN

RESOURCES += \
    SRC.qrc
