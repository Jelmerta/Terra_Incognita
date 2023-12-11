#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "GameObject.h"
#include <exception>
#include <map>
#include <vector>

class GameState {
public:
  GameState(std::vector<GameObject> gameObjects) {
    for (GameObject gameObject : gameObjects) {
      this->gameObjects.insert({gameObject.getName(), gameObject});
    }
  }

  std::map<std::string, GameObject> getGameObjects() { return gameObjects; }

  GameObject *getGameObject(std::string name) { return &gameObjects.at(name); }

  glm::vec3 getTargetPosition() {
    for (auto x : getGameObjects()) {
      if (x.second.name == "Player") { // Somewhat hacky
        return x.second.position;
      }
    }
    throw new std::bad_exception; // Not sure what exception
  }

private:
  std::map<std::string, GameObject> gameObjects;
};

#endif