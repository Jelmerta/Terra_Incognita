#include "GameEvent.h"
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GameObject.h"
#include "GameState.h"
#include "InputHandler.h"
#include "RenderSystem.h"
#include "EventProcessor.h"

#include <vector>
#include <iostream>

GameObject planeObject("Plane", glm::vec2(0.0f, 0.0f), 1.0f, 1.0f,
                       glm::vec3(0.0f, 1.0f, 0.0f), 0, true);
GameObject playerObject("Player", glm::vec2(0.0f, 0.0f), 1.0f, 1.0f,
                        glm::vec3(1.0f, 0.0f, 0.0f), 0, true);
std::vector gameObjects = {planeObject, playerObject};
GameState gameState(gameObjects);

RenderSystem* renderSystem;
InputHandler* inputHandler;
EventProcessor eventProcessor(&gameState);

// Game loop
void render_frame(GLFWwindow *window) {
  std::vector<GameEvent> inputEvents = inputHandler->processInput(window);

std::cout << inputEvents.size() << std::endl;
  // TODO Process logic / collision / physics
//   std::vector<GameEvent> gameEvents
  eventProcessor.handleEvents(&inputEvents);

  renderSystem->render(gameState);

  // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
  glfwSwapBuffers(window);
}

int main(int argc, char **argv) {
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

  GLFWwindow *window =
      glfwCreateWindow(GameConstants::WINDOW_WIDTH,
                       GameConstants::WINDOW_HEIGHT, "Kloenk", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

#ifndef __EMSCRIPTEN__
  /* Load EGL */
  EGLDisplay display = glfwGetEGLDisplay();

  int egl_version = gladLoadEGL(display, glfwGetProcAddress);
  printf("EGL %d.%d\n", GLAD_VERSION_MAJOR(egl_version),
         GLAD_VERSION_MINOR(egl_version));
#endif

  /* Load GLES */
  std::cout << "-> using GLFW to load GLES2\n";
  int gles_version = gladLoadGLES2(glfwGetProcAddress);
  std::cout << "GLES " << GLAD_VERSION_MAJOR(gles_version) << "."
            << GLAD_VERSION_MINOR(gles_version) << std::endl;
  if (gles_version == 0) {
    std::cout << "Failed to initialize OpenGL context" << std::endl;
    return -1;
  }

  glEnable(GL_DEPTH_TEST);

  renderSystem = new RenderSystem;
  inputHandler = new InputHandler;

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop_arg((em_arg_callback_func)render_frame, window, 60,
                               1);
#else
  while (!glfwWindowShouldClose(window)) {
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