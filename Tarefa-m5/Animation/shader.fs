#version 330 core
out vec4 FragColor;

in vec3 ourColor; // Recebe a cor do vertex shader
in vec2 TexCoord; // Recebe a textura do vertex shader

// texture sampler
uniform sampler2D texture1;
void main()
{
    FragColor = texture(texture1, TexCoord); // Aqui em vez de mandar a cor, manda a textura
}
