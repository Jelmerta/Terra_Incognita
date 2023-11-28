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

void processInput(GLFWwindow *window);

const GLuint WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
unsigned int VAO;
unsigned int shaderProgram;

const char *vertexShaderSource = "#version 300 es\n"
                                  "layout (location=0) in vec3 position;\n"
                                 "void main()\n"
                                 "{\n"
                                 "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
                                 "}\0\n";

const char *fragmentShaderSource = "#version 300 es\n"
                                   //    "#ifdef GL_ES\n"
                                   "precision mediump float;\n"
                                   //    "#endif\n"
                                   "out vec4 fragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\0";

const float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f};

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
    std::cout << "Start of game loop" << std::endl; // Debug logging
    // Handle input
    processInput(window);
    glfwPollEvents();

    // Render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

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

    // ---------------
    // Vertex Shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // error log for compilation
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    // Fragment Shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // error log for compilation
    int successFrag;
    char infoLogFrag[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFrag);
    if (!successFrag)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLogFrag);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLogFrag << std::endl;
    }

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR: Shader linking failed\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Initialisation code
    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);

    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 3. Set Vertex Attribute pointers

    // Do we need to get position dynamically, because of GLES? Not defined in shader
    // GLint positionAttribute = glGetAttribLocation(shaderProgram, "position");
    // glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // glEnableVertexAttribArray(positionAttribute);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // ---------------

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

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}