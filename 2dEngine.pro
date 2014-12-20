TEMPLATE = subdirs
CONFIG -= qt

android {
SUBDIRS += Android
}

win32|linux|emscripten:!android{
SUBDIRS += Desktop
}

SUBDIRS += \
    Common \
    LibPng \
    Game

emscripten{
SUBDIRS += zlib
}
