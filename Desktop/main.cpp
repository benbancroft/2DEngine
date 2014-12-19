#include <stdlib.h>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include "game.h"

int init_gl();
void do_frame();
void shutdown_gl();

static Core::Engine* engine;
static GLFWwindow* window = NULL;

double lastTime = 0;

const int width = 480,
         height = 800;

int main()
{
    if (init_gl()) {
        engine->SurfaceCreated();
        engine->SurfaceChanged(width, height);

        #ifdef __EMSCRIPTEN__
            emscripten_set_main_loop(do_frame, 60, 1);
        #else
            while (!glfwWindowShouldClose(window)) {
                do_frame();
                glfwPollEvents();

                // Delay to keep frame rate constant
                /*double currentTime = glfwGetTime()*1000;
                Sleep(60-(lastTime-currentTime));
                lastTime = glfwGetTime()*1000;*/
            }
        #endif

    }

    shutdown_gl();

    return 0;
}

int init_gl()
{

    if (!glfwInit()) {
        printf("glfwInit() failed\n");
        return false;
    }

    window = glfwCreateWindow(width, height, "2dEngine", NULL, NULL);
    if (!window) {
        printf("glfwOpenWindow() failed\n");
        return false;
    }

    glfwMakeContextCurrent(window);

    engine = InitialiseGame();

    return true;
}

void do_frame()
{
    engine->Animate(glfwGetTime()*1000);
    glfwSwapBuffers(window);
}

void shutdown_gl()
{
    glfwTerminate();
}
