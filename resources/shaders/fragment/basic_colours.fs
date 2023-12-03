#version 300 es
precision mediump float;
out vec4 FragColor;
  
uniform vec4 ourColor; // we set this variable in the OpenGL code.

void main()
{
    FragColor = ourColor;
}   

// #version 300 es
// precision mediump float;

// in vec4 vertexColor;
// out vec4 fragColor;

// void main() {
//     // fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//     fragColor = vertexColor;
// }
