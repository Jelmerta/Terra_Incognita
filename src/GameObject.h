#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>

#include <glad/egl.h>
#include <glad/gles2.h>
#include <glm/glm.hpp>

// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.

// What does one GameObject need? Define logic, a mesh, how to render, but also hitbox, position etc
// What is a Goblin? They might all have same mesh/color/hitbox/logic but they might have different positions, rotation, health, status effects, drops?
// On spawning though, the only variables might even be things like position/rotation
class GameObject
{
public:
    // object state
    std::string name;
    glm::vec2   position;
    glm::vec2   previousPosition; // We store the previous position such that collisions can be resolved by moving back to previous position (which, assuming collidables don't move, is a valid position without collision)
    float       scale;
    float       hitbox; // For now assumes hitbox is square
    glm::vec3   color;
    float       rotation; // in degrees
    bool        isSolid;
    float       distanceFromCenterOfModelToBottom; // A model might need to be moved up such that it appears above a plane. For now hardcoded in this silly variable
    // constructor(s)
    GameObject(std::string name, glm::vec2 position, float scale, float hitbox, glm::vec3 color, float rotation, bool isSolid, float distanceFromCenterOfModelToBottom);

    std::string getName() {
        return name;
    }
};

#endif