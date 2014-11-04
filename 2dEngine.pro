TEMPLATE = subdirs

SUBDIRS += \
    Android \
    Common \
    LibPng

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/Common/release/ -lCommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/Common/debug/ -lCommon
else:unix: LIBS += -L$$OUT_PWD/Common/ -lCommon

INCLUDEPATH += $$PWD/Common
DEPENDPATH += $$PWD/Common
