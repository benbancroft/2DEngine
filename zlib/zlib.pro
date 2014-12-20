#-------------------------------------------------
#
# Project created by QtCreator 2014-12-20T00:08:38
#
#-------------------------------------------------

QT       -= core gui

TARGET = zlib
TEMPLATE = lib
CONFIG += staticlib

DEPENDSPATH += $$system(pwd)

SOURCES += adler32.c \
    crc32.c \
    deflate.c \
    infback.c \
    inffast.c \
    inflate.c \
    inftrees.c \
    trees.c \
    zutil.c

HEADERS += adler32.h \
    zlib.h \
    crc32.h \
    deflate.h \
    infback.h \
    inffast.h \
    inflate.h \
    inftrees.h \
    trees.h \
    zutil.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
