#-------------------------------------------------
#
# Project created by QtCreator 2014-11-07T16:56:08
#
#-------------------------------------------------

QT       -= core gui

TARGET = Game
TEMPLATE = lib
CONFIG += staticlib

SOURCES += game.cpp \
    mainlevel.cpp

HEADERS += game.h \
    mainlevel.h

INCLUDEPATH += $$PWD/../Common
DEPENDPATH += $$PWD/../Common

INCLUDEPATH += $$PWD/../LibPng
DEPENDPATH += $$PWD/../LibPng
