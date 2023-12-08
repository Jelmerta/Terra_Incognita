#include "GameObject.h"
class MovementSystem {
public:
  void moveNorth(GameObject* gameObject) const {
    gameObject->previousPosition = gameObject->position;
    gameObject->position.y += movementSpeed;
  }

  void moveSouth(GameObject* gameObject) const {
    gameObject->previousPosition = gameObject->position;
    gameObject->position.y -= movementSpeed;
  }

  void moveEast(GameObject* gameObject) const {
    gameObject->previousPosition = gameObject->position;
    gameObject->position.x += movementSpeed;
  }

  void moveWest(GameObject* gameObject) const {
    gameObject->previousPosition = gameObject->position;
    gameObject->position.x -= movementSpeed;
  }

private:
  const float movementSpeed = 0.01f;
};