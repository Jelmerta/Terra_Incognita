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
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <filesystem>

#include "Character.cpp"

void processInput(GLFWwindow *window);

const GLuint WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
unsigned int VAO_PLANE;
unsigned int VAO_CUBE;
// unsigned int shaderProgram;
Shader *ourShader;

Character character;

// Square
float vertices_plane[] = {
    1.0f, 1.0f, 0.0f,   // top right
    1.0f, -1.0f, 0.0f,  // bottom right
    -1.0f, -1.0f, 0.0f, // bottom left
    -1.0f, 1.0f, 0.0f   // top left
};

unsigned int indices_plane[] = {
    0, 1, 3,
    1, 2, 3};

float cube[] = {
    0.5f, 0.5f, 0.5f,   // + + +
    0.5f, 0.5f, -0.5f,  // + + -
    0.5f, -0.5f, 0.5f,  // + - +
    0.5f, -0.5f, -0.5f, // + - -
    -0.5f, 0.5f, 0.5f,  // - + +
    -0.5f, 0.5f, -0.5f, // - + -
    -0.5f, -0.5f, 0.5f, // - - +
    -0.5f, -0.5f, -0.5f // - - -
};

unsigned int cube_indices[] = {
    7, 3, 1,
    1, 5, 7,

    6, 2, 0,
    0, 4, 6,

    4, 5, 7,
    7, 6, 4,

    0, 1, 3,
    3, 2, 0,

    7, 1, 2,
    2, 6, 7,

    5, 1, 0,
    0, 4, 5};

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        character.moveNorth();
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        character.moveSouth();
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        character.moveEast();
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        character.moveWest();
    }
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

    // create transformations
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::translate(glm::rotate(view, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(0.0f, -3.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
    // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    ourShader->setMat4("model", model);
    ourShader->setMat4("view", view);
    ourShader->setMat4("projection", projection);

    ourShader->setVec4("ourColor", glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));
    glBindVertexArray(VAO_PLANE);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Move cube around based on input
    model = glm::translate(glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(character.getLongitude(), 0.0f, character.getLatitude()));
    ourShader->setMat4("model", model);

    ourShader->setVec4("ourColor", glm::vec4(0.2f, 0.8f, 0.2f, 1.0f));
    glBindVertexArray(VAO_CUBE);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0); // Reset bound array

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

    // PLANE CODE
    // Initialisation code
    unsigned int VBO_PLANE;
    glGenBuffers(1, &VBO_PLANE);

    unsigned int EBO_PLANE;
    glGenBuffers(1, &EBO_PLANE);

    glGenVertexArrays(1, &VAO_PLANE);

    // 1. bind Vertex Array Object
    glBindVertexArray(VAO_PLANE);

    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO_PLANE);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_plane), vertices_plane, GL_STATIC_DRAW);

    // 3. copy our index array in a element buffer for OpenGL to use (so we reuse the same vertices instead of duplicating)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_PLANE);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_plane), indices_plane, GL_STATIC_DRAW);

    // 4. Set Vertex Attribute pointers

    // Do we need to get position dynamically, because of GLES? Not defined in shader
    // GLint positionAttribute = glGetAttribLocation(shaderProgram, "position");
    // glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // glEnableVertexAttribArray(positionAttribute);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // CUBE CODE
    // Initialisation code
    unsigned int VBO_CUBE;
    glGenVertexArrays(1, &VAO_CUBE);

    glGenBuffers(1, &VBO_CUBE);

    unsigned int EBO_CUBE;
    glGenBuffers(1, &EBO_CUBE);

    // 1. bind Vertex Array Object
    glBindVertexArray(VAO_CUBE);

    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO_CUBE);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

    // 3. copy our index array in a element buffer for OpenGL to use (so we reuse the same vertices instead of duplicating)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_CUBE);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    // 4. Set Vertex Attribute pointers

    // Do we need to get position dynamically, because of GLES? Not defined in shader
    // GLint positionAttribute = glGetAttribLocation(shaderProgram, "position");
    // glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // glEnableVertexAttribArray(positionAttribute);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Reset buffers
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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