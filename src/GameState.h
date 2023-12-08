#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "GameObject.h"
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

  GameObject* getGameObject(std::string name) { return &gameObjects.at(name); }

private:
  std::map<std::string, GameObject> gameObjects;
};

#endif