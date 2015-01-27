#-------------------------------------------------
#
# Project created by QtCreator 2014-11-04T14:26:22
#
#-------------------------------------------------

QT       -= core gui

TARGET = Common
TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

HEADERS += \
    platform/platform_asset_utils.h \
    platform/platform_file_utils.h \
    platform/platform_gl.h \
    platform/platform_log.h \
    platform/platform_macros.h \
    asset.h \
    asset_utils.h \
    config.h \
    image_utils.h \
    macros.h \
    shader.h \
    texture.h \
    engine.h \
    level.h \
    vector.h \
    entity.h \
    viewport.h \
    render.h \
    tiles/tilelayer.h \
    tiles/tilegenerator.h \
    tiles/tilesystem.h \
    depthrenderable.h

SOURCES += \
    platform/platform_file_utils.cpp \
    platform/platform_log.cpp \
    asset.cpp \
    asset_utils.cpp \
    image_utils.cpp \
    shader.cpp \
    texture.cpp \
    engine.cpp \
    level.cpp \
    vector.cpp \
    entity.cpp \
    viewport.cpp \
    render.cpp \
    tiles/tilelayer.cpp \
    tiles/tilegenerator.cpp \
    tiles/tilesystem.cpp \
    depthrenderable.cpp

INCLUDEPATH += $$PWD/../LibPng
DEPENDPATH += $$PWD/../LibPng

OTHER_FILES += \
    assets/textures/air_hockey_surface.png \
    assets/shaders/shader.fsh \
    assets/shaders/shader.vsh \
    assets/textures/tilesheet.png \
    assets/shaders/draw.fsh \
    assets/shaders/draw.vsh \
    assets/shaders/tile.fsh \
    assets/shaders/tile.vsh

#Assets

assets.path = $$OUT_PWD/../Desktop
emscripten:assets.path = $$OUT_PWD/../Desktop/assets
android:assets.path = /assets
assets.files = assets/*

INSTALLS += assets
