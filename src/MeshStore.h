#include <string>
#include <map>
#include "Mesh.h"

class MeshStore
{
public:
    Mesh get(std::string name) const
    {
        return meshMap.at(name); // TODO Potential null
    }

private:
    // Square
    std::vector<Vertex> planeVertices = {
        {glm::vec3(1.0f, 1.0f, 0.0f)},   // top right
        {glm::vec3(1.0f, -1.0f, 0.0f)},  // bottom right
        {glm::vec3(-1.0f, -1.0f, 0.0f)}, // bottom left
        {glm::vec3(-1.0f, 1.0f, 0.0f)}   // top left
    };

    std::vector<unsigned int> planeIndices = {
        0, 1, 3,
        1, 2, 3};

    std::vector<Vertex> cubeVertices = {{glm::vec3(0.5f, 0.5f, 0.5f)},
                                        {glm::vec3(0.5f, 0.5f, -0.5f)},
                                        {glm::vec3(0.5f, -0.5f, 0.5f)},
                                        {glm::vec3(0.5f, -0.5f, -0.5f)},
                                        {glm::vec3(-0.5f, 0.5f, 0.5f)},
                                        {glm::vec3(-0.5f, 0.5f, -0.5f)},
                                        {glm::vec3(-0.5f, -0.5f, 0.5f)},
                                        {glm::vec3(-0.5f, -0.5f, -0.5f)}};

    std::vector<unsigned int> cubeIndices = {
        7, 3, 1,
        1, 5, 7,

        6, 2, 0,
        0, 4, 6,

        4, 5, 7,
        7, 6, 4,

        0, 1, 3,
        3, 2, 0,

        7, 1, 2,
        2, 6, 7,

        5, 1, 0,
        0, 4, 5};

    std::map<std::string, Mesh> meshMap = {
        {"Plane", Mesh(planeVertices, planeIndices)},
        {"Cube", Mesh(cubeVertices, cubeIndices)},
        {"Obstacle", Mesh(cubeVertices, cubeIndices)},
        {"Player", Mesh(cubeVertices, cubeIndices)}};
};