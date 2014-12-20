#-------------------------------------------------
#
# Project created by QtCreator 2014-11-04T20:23:20
#
#-------------------------------------------------

QT       -= core gui

TARGET = Png
TEMPLATE = lib

CONFIG += staticlib

emscripten{
    INCLUDEPATH += $$PWD/../zlib
    DEPENDPATH += $$PWD/../zlib
}

SOURCES += png.c \
                                  pngerror.c \
                                  pngget.c \
                                  pngmem.c \
                                  pngpread.c \
                                  pngread.c \
                                  pngrio.c \
                                  pngrtran.c \
                                  pngrutil.c \
                                  pngset.c \
                                  pngtrans.c \
                                  pngwio.c \
                                  pngwrite.c \
                                  pngwtran.c \
                                  pngwutil.c

HEADERS +=
