#ifndef MESH_H
#define MESH_H

#include <glad/egl.h>
#include <glad/gles2.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

#include <vector>

#include <iostream>

struct Vertex {
    // position
    glm::vec3 Position;
};

class Mesh {
public:
    // mesh Data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO;

    // constructor
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
    {
        this->vertices = vertices;
        this->indices = indices;

        // now that we have all the required data, set the vertex buffers and its attribute pointers.
        setupMesh();
    }

    // render the mesh
    void draw() 
    {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

private:
    // render data 
    unsigned int VBO, EBO;

    // initializes all the buffer objects/arrays
    void setupMesh()
    {
        // create buffers/arrays
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        // load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // A great thing about structs is that their memory layout is sequential for all its items.
        // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
        // again translates to 3/2 floats which translates to a byte array.
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // set the vertex attribute pointers
        // vertex Positions
        glEnableVertexAttribArray(0);	
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glBindVertexArray(0);
    }
};
#endif



    // // CUBE CODE
    // // Initialisation code
    // unsigned int VBO_CUBE;
    // glGenVertexArrays(1, &VAO_CUBE);

    // glGenBuffers(1, &VBO_CUBE);

    // unsigned int EBO_CUBE;
    // glGenBuffers(1, &EBO_CUBE);

    // // 1. bind Vertex Array Object
    // glBindVertexArray(VAO_CUBE);

    // // 2. copy our vertices array in a buffer for OpenGL to use
    // glBindBuffer(GL_ARRAY_BUFFER, VBO_CUBE);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

    // // 3. copy our index array in a element buffer for OpenGL to use (so we reuse the same vertices instead of duplicating)
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_CUBE);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    // // 4. Set Vertex Attribute pointers

    // // Do we need to get position dynamically, because of GLES? Not defined in shader
    // // GLint positionAttribute = glGetAttribLocation(shaderProgram, "position");
    // // glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // // glEnableVertexAttribArray(positionAttribute);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // glEnableVertexAttribArray(0);

    // GameObject secondCube(glm::vec2(0.5, 0.5), 0.3, 0.3, glm::vec3(1.0f, 0.0f, 0.0f), 0, true);
    // secondCube.render();





// PLANE CODE
    // Initialisation code
    // unsigned int VBO_PLANE;
    // glGenBuffers(1, &VBO_PLANE);

    // unsigned int EBO_PLANE;
    // glGenBuffers(1, &EBO_PLANE);

    // glGenVertexArrays(1, &VAO_PLANE);

    // // 1. bind Vertex Array Object
    // glBindVertexArray(VAO_PLANE);

    // // 2. copy our vertices array in a buffer for OpenGL to use
    // glBindBuffer(GL_ARRAY_BUFFER, VBO_PLANE);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_plane), vertices_plane, GL_STATIC_DRAW);

    // // 3. copy our index array in a element buffer for OpenGL to use (so we reuse the same vertices instead of duplicating)
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_PLANE);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_plane), indices_plane, GL_STATIC_DRAW);

    // // 4. Set Vertex Attribute pointers

    // // Do we need to get position dynamically, because of GLES? Not defined in shader
    // // GLint positionAttribute = glGetAttribLocation(shaderProgram, "position");
    // // glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // // glEnableVertexAttribArray(positionAttribute);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // glEnableVertexAttribArray(0);


    // Rendering:

        // ourShader->setVec4("ourColor", glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));
    // glBindVertexArray(VAO_PLANE);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



    // ourShader->setVec4("ourColor", glm::vec4(0.2f, 0.8f, 0.2f, 1.0f));
    // glBindVertexArray(VAO_CUBE);
    // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);




    