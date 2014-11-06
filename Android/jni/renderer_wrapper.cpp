#include "game.h"
#include "macros.h"
#include <jni.h>

extern "C" {
    JNIEXPORT void JNICALL Java_uk_co_benbancroft_AndroidEngine_RendererWrapper_on_1surface_1created(
        JNIEnv * env, jclass cls) {
        UNUSED(env);
        UNUSED(cls);
        on_surface_created();
    }

    JNIEXPORT void JNICALL Java_uk_co_benbancroft_AndroidEngine_RendererWrapper_on_1surface_1changed(
        JNIEnv * env, jclass cls, jint width, jint height) {
        UNUSED(env);
        UNUSED(cls);
        on_surface_changed();
    }

    JNIEXPORT void JNICALL Java_uk_co_benbancroft_AndroidEngine_RendererWrapper_on_1draw_1frame(
        JNIEnv* env, jclass cls) {
        UNUSED(env);
        UNUSED(cls);
        on_draw_frame();
    }
}
