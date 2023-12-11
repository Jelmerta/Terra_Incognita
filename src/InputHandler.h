#include "GameEvent.h"
#include <GLFW/glfw3.h>
#include <vector>
class InputHandler {
public:
  std::vector<GameEvent> processInput(GLFWwindow *window) const {
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }

    std::vector<GameEvent> inputEvents = {};
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
      inputEvents.push_back(GameEvent("moveNorth"));
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
      inputEvents.push_back(GameEvent("moveSouth"));
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
      inputEvents.push_back(GameEvent("moveEast"));
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
      inputEvents.push_back(GameEvent("moveWest"));
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
      inputEvents.push_back(GameEvent("moveUp"));
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
      inputEvents.push_back(GameEvent("moveDown"));
    }

    return inputEvents;
  }
};

// Handles all events. Can have multiple presses in a frame
// // void key_callback(GLFWwindow *window, int key, int scancode, int action,
// int mode)
// {
//     if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, GL_TRUE);
// }

// glfwSetKeyCallback(window, key_callback);

// glfwPollEvents();
