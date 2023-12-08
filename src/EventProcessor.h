// TODO Process logic / collision / physics
#include "GameEvent.h"
#include "GameObject.h"
#include "GameState.h"
#include "MovementSystem.h"
#include <vector>
#include <iostream>

class EventProcessor {
public:
  EventProcessor(GameState *gameState) { this->gameState = gameState; }

  void handleEvents(std::vector<GameEvent> *gameEvents) {
    for (GameEvent gameEvent : *gameEvents) {
        std::cout << gameEvent.getName() << std::endl;
      if (gameEvent.getName() == "moveNorth") {
        GameObject* gameObject = gameState->getGameObject("Player");
        movementSystem.moveNorth(gameObject);
        std::cout << gameObject->position.y << std::endl;
      }

      if (gameEvent.getName() == "moveSouth") {
        GameObject* gameObject = gameState->getGameObject("Player");
        movementSystem.moveSouth(gameObject);
      }

      if (gameEvent.getName() == "moveEast") {
        GameObject* gameObject = gameState->getGameObject("Player");
        movementSystem.moveEast(gameObject);
      }

      if (gameEvent.getName() == "moveWest") {
        GameObject* gameObject = gameState->getGameObject("Player");
        movementSystem.moveWest(gameObject);
      }
    }

    // TODO Empty events?
  }

private:
  GameState *gameState;

  MovementSystem movementSystem;
};