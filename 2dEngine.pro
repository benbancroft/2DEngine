TEMPLATE = subdirs

android {
SUBDIRS += Android
}

win32|linux:!android{
SUBDIRS += Desktop
}

SUBDIRS += \
    Common \
    LibPng \
    Game
