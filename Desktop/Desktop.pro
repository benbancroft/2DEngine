TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lglfw -lGLESv2

CONFIG += c++11

SOURCES += main.cpp \
    platform_asset_utils.cpp

INCLUDEPATH += $$PWD/../Common
DEPENDPATH += $$PWD/../Common

INCLUDEPATH += $$PWD/../LibPng
DEPENDPATH += $$PWD/../LibPng

INCLUDEPATH += $$PWD/../Game
DEPENDPATH += $$PWD/../Game

emscripten{
    TARGET = Desktop.html

    QMAKE_LFLAGS += -s USE_GLFW=3 --embed-file assets@/

    OBJECTS += $$OUT_PWD/../Game/libGame.bc \
        $$OUT_PWD/../Common/libCommon.bc \
        $$OUT_PWD/../LibPng/libPng.bc \
        $$OUT_PWD/../zlib/libzlib.bc
}else{
    Target = Desktop

    unix:!macx: LIBS += -L$$OUT_PWD/../Game/ -lGame
    unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../Game/libGame.a

    unix:!macx: LIBS += -L$$OUT_PWD/../Common/ -lCommon
    unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../Common/libCommon.a

    unix:!macx: LIBS += -L$$OUT_PWD/../LibPng/ -lPng -lz
    unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../LibPng/libPng.a

}

HEADERS += \
    platform_gl.h
