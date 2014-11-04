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
    asset_utils.h \
    buffer.h \
    config.h \
    game.h \
    image.h \
    macros.h \
    shader.h \
    texture.h \
    platform/platform_asset_utils.h \
    platform/platform_file_utils.h \
    platform/platform_log.h \
    platform/platform_macros.h \
    platform/platform_gl.h

SOURCES += \
    asset_utils.c \
    buffer.c \
    game.c \
    image.c \
    shader.c \
    texture.c \
    platform/platform_file_utils.c \
    platform/platform_log.c

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
