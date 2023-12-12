// TODO Process logic / collision / physics
#include "GameEvent.h"
#include "GameObject.h"
#include "GameState.h"
#include "MovementSystem.h"
#include <vector>

class EventProcessor {
public:
  EventProcessor(GameState *gameState) { this->gameState = gameState; }

  void handleEvents(std::vector<GameEvent> *gameEvents) {
    for (GameEvent gameEvent : *gameEvents) {
      if (gameEvent.getName() == "moveNorth") {
        GameObject *player = gameState->getGameObject("Player");
        movementSystem.moveNorth(player);
        handleCollision(player, gameState->getGameObjects());
      }

      if (gameEvent.getName() == "moveSouth") {
        GameObject *player = gameState->getGameObject("Player");
        movementSystem.moveSouth(player);
        handleCollision(player, gameState->getGameObjects());
      }

      if (gameEvent.getName() == "moveEast") {
        GameObject *player = gameState->getGameObject("Player");
        movementSystem.moveEast(player);
        handleCollision(player, gameState->getGameObjects());
      }

      if (gameEvent.getName() == "moveWest") {
        GameObject *player = gameState->getGameObject("Player");
        movementSystem.moveWest(player);
        handleCollision(player, gameState->getGameObjects());
      }

      if (gameEvent.getName() == "moveUp") {
        GameObject *player = gameState->getGameObject("Player");
        movementSystem.moveUp(player);
        handleCollision(player, gameState->getGameObjects());
      }

      if (gameEvent.getName() == "moveDown") {
        GameObject *player = gameState->getGameObject("Player");
        movementSystem.moveDown(player);
        handleCollision(player, gameState->getGameObjects());
      }

      if (gameEvent.getName() == "playerGravity") { // Probably not something we should have as an "event", and instead just a "tick" or something
        GameObject *player = gameState->getGameObject("Player");
        movementSystem.moveDown(player);
        handleCollision(player, gameState->getGameObjects());
      }
    }

    // TODO Empty list of events?
  }

private:
  GameState *gameState;

  MovementSystem movementSystem;

  // Check collision with all other collidable game objects
  void handleCollision(GameObject *object,
                       std::map<std::string, GameObject> gameObjects) {
    for (auto gameObject : gameObjects) {
      if (gameObject.second.isSolid) {
        if (checkCollision(*object, gameObject.second)) {
          object->position = object->previousPosition;
        }
      }
    }
  }

  // We assume for now that all objects' hitbox are square
  bool checkCollision(GameObject object1, GameObject object2) {
    bool collisionX = object1.position.x + object1.hitbox >=
                          object2.position.x - object2.hitbox &&
                      object2.position.x + object2.hitbox >=
                          object1.position.x - object1.hitbox;

    bool collisionY = object1.position.y + object1.hitbox >=
                          object2.position.y - object2.hitbox &&
                      object2.position.y + object2.hitbox >=
                          object1.position.y - object1.hitbox;

    bool collisionZ = object1.position.z + object1.hitbox >=
                          object2.position.z - object2.hitbox &&
                      object2.position.z + object2.hitbox >=
                          object1.position.z - object1.hitbox;

    // collision only if on both axes
    return collisionX && collisionY && collisionZ;
  }
};