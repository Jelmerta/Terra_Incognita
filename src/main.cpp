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

#include "EventProcessor.h"
#include "GameObject.h"
#include "GameState.h"
#include "InputHandler.h"
#include "RenderSystem.h"

#include <iostream>
#include <vector>

// Names need to be different in order for everything to be rendered
const GameObject planeObject("Plane", glm::vec3(0.0f, -0.5f, 0.0f), 1.0f,
                             0.50f, glm::vec3(0.0f, 1.0f, 0.0f), 0,
                             true); // For now like a cube
const GameObject playerObject("Player", glm::vec3(0.0f, 1.51f, 0.0f), 1.0f,
                              0.51f, glm::vec3(1.0f, 0.0f, 0.0f), 0, false);
const GameObject obstacleObject("Obstacle", glm::vec3(1.5f, 0.0f, 0.0f), 1.0f,
                                0.50f, glm::vec3(0.0f, 0.0f, 1.0f), 0, true);
const GameObject lowerPlane("lowerPlane", glm::vec3(0.0f, -3.0f, 0.0f), 1.0f, 0.50f,
                            glm::vec3(1.0f, 0.0f, 1.0f), 0, true);
std::vector gameObjects = {planeObject, playerObject, obstacleObject, lowerPlane};
GameState gameState(gameObjects);

const RenderSystem *renderSystem;
const InputHandler *inputHandler;
EventProcessor eventProcessor(&gameState);

// Game loop
void render_frame(GLFWwindow *window) {
  std::vector<GameEvent> inputEvents = inputHandler->processInput(window);
  inputEvents.push_back(GameEvent("playerGravity")); // Every frame, we just try to move down to act as gravity
  eventProcessor.handleEvents(&inputEvents);
  renderSystem->render(&gameState);
  glfwSwapBuffers(
      window); // Also polls IO events (keys pressed/released, mouse moved etc.)
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
  glfwWindowHint(GLFW_DEPTH_BITS, 24);

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
  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LEQUAL);
  glDepthRangef(0.0f, 1.0f);

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

  glfwTerminate();
  return 0;
}