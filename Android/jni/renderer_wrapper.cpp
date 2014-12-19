#include "engine.h"
#include "game.h"
#include "macros.h"
#include <jni.h>
#include <cstddef>
#include <time.h>

using namespace Core;

static Engine* engine = NULL;

static double startTime = 0;

static double now_ms() {

    struct timespec res;
    clock_gettime(CLOCK_MONOTONIC, &res);
    return 1000.0 * res.tv_sec + (double) res.tv_nsec / 1e6;

}

extern "C" {
    JNIEXPORT void JNICALL Java_uk_co_benbancroft_AndroidEngine_RendererWrapper_on_1surface_1created(
        JNIEnv * env, jclass cls) {
        UNUSED(env);
        UNUSED(cls);

        if (engine == NULL){

            engine = InitialiseGame();
            engine->SurfaceCreated();
            startTime = now_ms();
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
        engine->Animate(now_ms()-startTime);
    }
}
