#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <glad/egl.h>
#include <glad/gles2.h>

#define GLFW_INCLUDE_NONE 1
#include <GLFW/glfw3.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#else
#define GLFW_EXPOSE_NATIVE_EGL 1
#include <GLFW/glfw3native.h>
#endif

#include "shader_m.h"

#include <glm/glm.hpp>

#include <filesystem>


void processInput(GLFWwindow *window);

const GLuint WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
unsigned int VAO;
unsigned int EBO;
// unsigned int shaderProgram;
Shader* ourShader;

// Square
float vertices[] = {
    0.5f, 0.5f, 0.0f,   // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f   // top left
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3};

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Game loop
void render_frame(GLFWwindow *window)
{
    // Handle input
    processInput(window);
    glfwPollEvents();

    // Render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    ourShader->use();
    // glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0); // Not really sure why used in tutorial, should look up. Already set outside of loop

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
}

int main(int argc, char **argv)
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    // When window size is changed, make sure that OpenGL is adjusted accordingly
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Kloenk", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

#ifndef __EMSCRIPTEN__
    /* Load EGL */
    EGLDisplay display = glfwGetEGLDisplay();

    int egl_version = gladLoadEGL(display, glfwGetProcAddress);
    printf("EGL %d.%d\n", GLAD_VERSION_MAJOR(egl_version), GLAD_VERSION_MINOR(egl_version));
#endif

    /* Load GLES */
    std::cout << "-> using GLFW to load GLES2\n";
    int gles_version = gladLoadGLES2(glfwGetProcAddress);
    std::cout << "GLES " << GLAD_VERSION_MAJOR(gles_version) << "." << GLAD_VERSION_MINOR(gles_version) << std::endl;
    if (gles_version == 0)
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    ourShader = new Shader("resources/shaders/vertex/basic_positions.vs", "resources/shaders/fragment/basic_colours.fs");

    // Initialisation code
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &EBO);

    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);

    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 3. copy our index array in a element buffer for OpenGL to use (so we reuse the same vertices instead of duplicating)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 4. Set Vertex Attribute pointers

    // Do we need to get position dynamically, because of GLES? Not defined in shader
    // GLint positionAttribute = glGetAttribLocation(shaderProgram, "position");
    // glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // glEnableVertexAttribArray(positionAttribute);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    ourShader->use();
    // ---------------

    // glPolygonOffset()
    //     // If this is initialised through window dimension changes, is this needed?
    // glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg((em_arg_callback_func)render_frame, window, 60, 1);
#else
    while (!glfwWindowShouldClose(window))
    {
        render_frame(window);
    }
#endif

// Cleanup code... Don't just delete this, make sure this gets cleaned up
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    // glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}