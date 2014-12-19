#include <stdlib.h>
#include <stdio.h>
#include <GL/glfw.h>
#include "game.h"

int init_gl();
void do_frame();
void shutdown_gl();

static Core::Engine* engine;

const int width = 480,
         height = 800;

int main()
{
    if (init_gl() == GL_TRUE) {
        engine->SurfaceCreated();
        engine->SurfaceChanged(width, height);

        while (true)
        {
            do_frame();
            glfwPollEvents();
        }

    }

    shutdown_gl();

    return 0;
}

int init_gl()
{

    if (glfwInit() != GL_TRUE) {
        printf("glfwInit() failed\n");
        return GL_FALSE;
    }

    if (glfwOpenWindow(width, height, 8, 8, 8, 8, 16, 0, GLFW_WINDOW) != GL_TRUE) {
        printf("glfwOpenWindow() failed\n");
        return GL_FALSE;
    }

    engine = InitialiseGame();

    return GL_TRUE;
}

void do_frame()
{
    engine->Render();
    glfwSwapBuffers();
}

void shutdown_gl()
{
    glfwTerminate();
}
