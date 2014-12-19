#-------------------------------------------------
#
# Project created by QtCreator 2014-11-07T16:56:08
#
#-------------------------------------------------

QT       -= core gui

TARGET = Game
TEMPLATE = lib
CONFIG += staticlib

SOURCES += game.cpp

HEADERS += game.h

unix:!macx: LIBS += -L$$OUT_PWD/../Common/ -lCommon

INCLUDEPATH += $$PWD/../Common
DEPENDPATH += $$PWD/../Common

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../Common/libCommon.a

unix:!macx: LIBS += -L$$OUT_PWD/../LibPng/ -lPng

INCLUDEPATH += $$PWD/../LibPng
DEPENDPATH += $$PWD/../LibPng

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../LibPng/libPng.a
