TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lglfw -lGLESv2

CONFIG += c++11

SOURCES += main.cpp \
    platform_asset_utils.cpp

unix:!macx: LIBS += -L$$OUT_PWD/../Common/ -lCommon

INCLUDEPATH += $$PWD/../Common
DEPENDPATH += $$PWD/../Common

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../Common/libCommon.a

unix:!macx: LIBS += -L$$OUT_PWD/../LibPng/ -lPng -lz

INCLUDEPATH += $$PWD/../LibPng
DEPENDPATH += $$PWD/../LibPng

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../LibPng/libPng.a

unix:!macx: LIBS += -L$$OUT_PWD/../Game/ -lGame

INCLUDEPATH += $$PWD/../Game
DEPENDPATH += $$PWD/../Game

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../Game/libGame.a

HEADERS += \
    platform_gl.h
