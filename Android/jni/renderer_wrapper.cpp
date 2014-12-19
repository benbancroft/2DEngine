#include "engine.h"
#include "game.h"
#include "macros.h"
#include <jni.h>
#include <cstddef>

using namespace Core;

static Engine* engine = NULL;

extern "C" {
    JNIEXPORT void JNICALL Java_uk_co_benbancroft_AndroidEngine_RendererWrapper_on_1surface_1created(
        JNIEnv * env, jclass cls) {
        UNUSED(env);
        UNUSED(cls);

        if (engine == NULL){

            engine = InitialiseGame();
            engine->SurfaceCreated();
        }
    }

    JNIEXPORT void JNICALL Java_uk_co_benbancroft_AndroidEngine_RendererWrapper_on_1surface_1changed(
        JNIEnv * env, jclass cls, jint width, jint height) {
        UNUSED(env);
        UNUSED(cls);
        engine->RecreateGLContext();
        engine->SurfaceChanged(width, height);
    }

    JNIEXPORT void JNICALL Java_uk_co_benbancroft_AndroidEngine_RendererWrapper_on_1draw_1frame(
        JNIEnv* env, jclass cls) {
        UNUSED(env);
        UNUSED(cls);
        engine->Render();
    }
}
