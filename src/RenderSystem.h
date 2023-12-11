#include "GameConstants.h"
#include "GameObject.h"
#include "GameState.h"
#include "Mesh.h"
#include "MeshStore.h"
#include "Shader.h"

class RenderSystem {
public:
  void render(GameState *gameState) const {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->use();

    performCameraTransformations(gameState->getTargetPosition());

    for (auto x : gameState->getGameObjects()) {
      render(x.second);
    }

    glBindVertexArray(0); // Reset bound array
  }

private:
  // For now, we assume the same shader is used everywhere
  Shader *shader = new Shader("resources/shaders/vertex/basic_positions.vs",
                              "resources/shaders/fragment/basic_colours.fs");
  MeshStore meshStore;
  void render(GameObject gameObject) const {
    Mesh mesh = meshStore.get(gameObject.getName());
    // Apply transformation to mesh?

    // // Move cube around based on input
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(gameObject.position.x,
                                            gameObject.position.y,
                                            gameObject.position.z));
    shader->setMat4("model", model);
    shader->setVec4("ourColor", glm::vec4(gameObject.color, 1));
    mesh.draw();
  }

  void performCameraTransformations(glm::vec3 cameraTarget) const {
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    glm::vec3 cameraPosition = glm::vec3(0.0f, 3.0f, 3.0f);
    glm::vec3 newCameraPosition = cameraTarget + cameraPosition;

    view = glm::lookAt(newCameraPosition, cameraTarget,
                       glm::vec3(0.0f, 1.0f, 0.0f));
    projection = glm::perspective(glm::radians(45.0f),
                                  (float)GameConstants::WINDOW_WIDTH /
                                      (float)GameConstants::WINDOW_HEIGHT,
                                  0.1f, 100.0f);
    // note: currently we set the projection matrix each frame, but since
    // the projection matrix rarely changes it's often best practice to set it
    // outside the main loop only once.
    // shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);
  }
};

// Reset buffers
// glBindBuffer(GL_ARRAY_BUFFER, 0);
// glBindVertexArray(0);
// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

// // glPolygonOffset()
// //     // If this is initialised through window dimension changes, is this
// needed?
// // glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

// Applying transformation to mesh?

// Cleanup code... Don't just delete this, make sure this gets cleaned up
// glDeleteVertexArrays(1, &VAO);
// glDeleteBuffers(1, &VBO);
// glDeleteProgram(shaderProgram);