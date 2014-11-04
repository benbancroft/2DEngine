TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt

ANDROID_PACKAGE_SOURCE_DIR = $$_PRO_FILE_PWD_

LIBS += -lGLESv2 -llog -landroid

SOURCES += \
    jni/Engine.cpp \
    jni/game.cpp \
    jni/platform_asset_utils.c \
    jni/platform_log.c \
    jni/renderer_wrapper.c

OTHER_FILES += \
    res/drawable-hdpi/ic_launcher.png \
    res/drawable-mdpi/ic_launcher.png \
    res/drawable-xhdpi/ic_launcher.png \
    src/uk/co/benbancroft/AndroidEngine/platform/PlatformFileUtils.java \
    src/uk/co/benbancroft/AndroidEngine/MainActivity.java \
    src/uk/co/benbancroft/AndroidEngine/RendererWrapper.java \
    AndroidManifest.xml

HEADERS += \
    jni/platform_gl.h

unix:!macx: LIBS += -L$$OUT_PWD/../Common/ -lCommon

INCLUDEPATH += $$PWD/../Common
DEPENDPATH += $$PWD/../Common

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../Common/libCommon.a

unix:!macx: LIBS += -L$$OUT_PWD/../LibPng/ -lPng

INCLUDEPATH += $$PWD/../LibPng
DEPENDPATH += $$PWD/../LibPng

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../LibPng/libPng.a
