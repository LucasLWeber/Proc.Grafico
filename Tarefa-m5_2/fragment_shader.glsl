#version 330 core
out vec4 FragColor;
in vec2 TexCoord; // Recebe a textura do vertex shader
// texture samplers
uniform sampler2D texture1;
//uniform sampler2D texture2;
void main()
{
    //FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2) ; // Interpola linearmente entre as 2 texturas (80% a 1ª (container2) e 20% a 2ª (awesomeface))
    FragColor = texture(texture1, TexCoord); // Aqui em vez de mandar a cor, manda a textura
}
