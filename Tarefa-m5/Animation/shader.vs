#version 330 core

layout (location = 0) in vec3 aPos; // Um vetor para as coordenadas
layout (location = 1) in vec3 aColor; // Um vetor para as cores
layout (location = 2) in vec2 aTexCoord; // Um vetor para as textura

out vec3 ourColor; // Saída da cor para o fragment shader
out vec2 TexCoord; // Saída da testura para o fragment shader

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
    ourColor = aPos; // Manda a info de cor que está no vertice para o fragment shader
    TexCoord = vec2(aTexCoord.x, aTexCoord.y); // Manda a info da textura que está no VAO(2) para o fragment shader
}
