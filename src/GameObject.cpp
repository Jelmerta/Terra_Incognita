#include "GameObject.h"
#include <string>

GameObject::GameObject(std::string name, glm::vec2 position, float scale, float hitbox, glm::vec3 color, float rotation, bool isSolid, float distanceFromCenterOfModelToBottom)
    : name(name), position(position), scale(scale), hitbox(hitbox), color(color), rotation(rotation), isSolid(isSolid), distanceFromCenterOfModelToBottom(distanceFromCenterOfModelToBottom) { }