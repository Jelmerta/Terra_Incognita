#include "GameObject.h"
class MovementSystem {
public:
  // North is defined as negative Z (Right hand rule)
  void moveNorth(GameObject* gameObject) const {
    gameObject->previousPosition = gameObject->position;
    gameObject->position.z -= movementSpeed;
  }

  // South is defined as positive Z (Right hand rule)
  void moveSouth(GameObject* gameObject) const {
    gameObject->previousPosition = gameObject->position;
    gameObject->position.z += movementSpeed;
  }

  void moveEast(GameObject* gameObject) const {
    gameObject->previousPosition = gameObject->position;
    gameObject->position.x += movementSpeed;
  }

  void moveWest(GameObject* gameObject) const {
    gameObject->previousPosition = gameObject->position;
    gameObject->position.x -= movementSpeed;
  }

  void moveUp(GameObject* gameObject) const {
    gameObject->previousPosition = gameObject->position;
    gameObject->position.y += movementSpeed;
  }

  void moveDown(GameObject* gameObject) const {
    gameObject->previousPosition = gameObject->position;
    gameObject->position.y -= movementSpeed;
  }

private:
  const float movementSpeed = 0.01f;
};