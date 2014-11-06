#-------------------------------------------------
#
# Project created by QtCreator 2014-11-04T14:26:22
#
#-------------------------------------------------

QT       -= core gui

TARGET = Common
TEMPLATE = lib
CONFIG += staticlib

HEADERS += \
    platform/platform_asset_utils.h \
    platform/platform_file_utils.h \
    platform/platform_gl.h \
    platform/platform_log.h \
    platform/platform_macros.h \
    asset.h \
    asset_utils.h \
    buffer.h \
    config.h \
    game.h \
    image_utils.h \
    macros.h \
    shader.h \
    texture.h

SOURCES += \
    platform/platform_file_utils.cpp \
    platform/platform_log.cpp \
    asset.cpp \
    asset_utils.cpp \
    buffer.cpp \
    game.cpp \
    image_utils.cpp \
    shader.cpp \
    texture.cpp

unix:!macx: LIBS += -L$$OUT_PWD/../LibPng/ -lPng

INCLUDEPATH += $$PWD/../LibPng
DEPENDPATH += $$PWD/../LibPng

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../LibPng/libPng.a

OTHER_FILES += \
    assets/textures/air_hockey_surface.png \
    assets/shaders/shader.fsh \
    assets/shaders/shader.vsh

#Assets

INSTALLS += textures shaders

textures.files += \
    assets/textures/air_hockey_surface.png
textures.path = /assets/textures

shaders.files += \
    assets/shaders/shader.fsh \
    assets/shaders/shader.vsh
shaders.path = /assets/shaders
