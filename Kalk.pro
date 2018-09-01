#-------------------------------------------------
#
# Project created by QtCreator 2018-08-31T13:31:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kalk
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
    Controller/binController.cpp \
    Model/binModel.cpp \
    Model/binary/binary.cpp \
    Model/binary/float16.cpp \
    Model/binary/floatP.cpp \
    Model/binary/integer.cpp \
    Model/binary/sigMag.cpp \
    Model/binary/twosComp.cpp \
    View/Custom/QCustomBtn.cpp \
    View/MainWindow.cpp

HEADERS  += \
    Controller/binController.h \
    Model/binModel.h \
    Model/binary/binary.h \
    Model/binary/float16.h \
    Model/binary/floatP.h \
    Model/binary/integer.h \
    Model/binary/opEx.h \
    Model/binary/sigMag.h \
    Model/binary/twosComp.h \
    View/Custom/QCustomBtn.h \
    View/MainWindow.h
