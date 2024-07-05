
//Compilar com: g++ M5.cpp -o tarefa-m5 src/glad.c -I include -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib64 -lGLEW -lGL -lX11 -lglfw -lrt -lm -ldl
// g++ M5.cpp -o tarefa-m5 ../src/glad.c ./gl_utils.cpp ./stb_image.cpp -I include -I../include -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib64 -lGLEW -lGL -lX11 -lglfw -lrt -lm -ldl
// Rodar com: ./tarefa-m5


#include "stb_image.h"
#include "gl_utils.h"
#include <glad/glad.h> // GLAD
#include <GLFW/glfw3.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define GL_LOG_FILE "gl.log"
#include <iostream>
#include "../Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

int g_gl_width = 480;
int g_gl_height = 480;

float fw = 0.25f;
float fh = 0.25f;
float offsetx = 0, offsety = 0;
int frameAtual = 3;
int acao = 3;
float previous = glfwGetTime();
int sign = 1;
int FPS = 6;
double current_seconds;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    // double current_seconds = glfwGetTime();
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
    std::cout << current_seconds << std::endl;

        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_W))
		{
			offsety = 0.0f;
			if ((current_seconds - previous) > (1/(float)FPS)){
				previous = current_seconds;
				frameAtual = (frameAtual + 1) % 4;
				offsetx = fw * (float)frameAtual;
                std::cout << "Esta entrando dentro da condicao" << std::endl;
			}

		}
		else if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_S))
		{
			offsety = 0.75f;
			if ((current_seconds - previous) > (1/(float)FPS)){
				previous = current_seconds;
				frameAtual = (frameAtual + 1) % 4;
				offsetx = fw * (float)frameAtual;
			}
		}
		else if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D))
		{
			offsety = 0.25f;
			if ((current_seconds - previous) > (1/(float)FPS)){
				previous = current_seconds;
				frameAtual = (frameAtual + 1) % 4;
				offsetx = fw * (float)frameAtual;
			}
		}
		else if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A))
		{
			offsety = 0.50f;
			if ((current_seconds - previous) > (1/(float)FPS)){
				previous = current_seconds;
				frameAtual = (frameAtual + 1) % 4;
				offsetx = fw * (float)frameAtual;
			}
		}
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "M5-Controle e Animação de Sprites", NULL, NULL);

    if (window == NULL) {
        cout << "###Erro: Falha na criação da janela GLFW !" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // Informa para o GLFW fazer com a janela criada seja o contexto principal na thread atual.

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Define a função a ser chamada se a janela principal mudar de tamanho

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "###Erro: Falha na inicialização do GLAD !" << endl;
        return -1;
    }



    //Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
    Shader shaderBg("./vertex_shader.glsl", "./fragment_shader.glsl"); // Shader para o fundo
    Shader shaderSully("./sprites_vs.glsl", "./sprites_fs.glsl"); // Shader para o personagem

    // VERTICES E VAO PARA O BACKGROUND:
    float verticesBg[] = {
         // positions          // texture coords (variam de 0.0 à 1.0 -- não podem ser negativas !)
        // Seguindo orientação anti-horário para facilitar a adição do eixo Z futuramente
        // Mudança na orientação dos eixo T para evitar de carregar as texturas de cabeça para baixo
        // X     Y     Z      S(X)  T(Y)
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, // sup./dir.
         1.0f, -1.0f, 0.0f,   1.0f, 1.0f, // inf./dir.
        -1.0f, -1.0f, 0.0f,   0.0f, 1.0f, // inf./esq.
        -1.0f,  1.0f, 0.0f,   0.0f, 0.0f  // sup./esq.
    };

    unsigned int indexBg[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO_FUN, VAO_FUN, EBO_FUN;
    glGenVertexArrays(1, &VAO_FUN);
    glGenBuffers(1, &VBO_FUN);
    glGenBuffers(1, &EBO_FUN);
    glBindVertexArray(VAO_FUN);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_FUN);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBg), verticesBg, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_FUN);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexBg), indexBg, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // VERTICES E VAO PARA O SULLY

    float verticesSully[] = {
         // positions          // texture coords (variam de 0.0 à 1.0 -- não podem ser negativas !)
        // Seguindo orientação anti-horário para facilitar a adição do eixo Z futuramente
        // Mudança na orientação dos eixo T para evitar de carregar as texturas de cabeça para baixo
        // X     Y     Z      S(X)  T(Y)
         0.25f, 0.25f, 0.0f, 0.25f, 0.25f, // top right
		 0.25f, -0.25f, 0.0f, 0.25f, 0.0f, // bottom right
		 -0.25f, -0.25f, 0.0f, 0.0f, 0.0f, // bottom left
		 -0.25f, 0.25f, 0.0f, 0.0f, 0.25f,
    };

    unsigned int indexSully[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO_PER, VAO_PER, EBO_PER;
    glGenVertexArrays(1, &VAO_PER);
    glGenBuffers(1, &VBO_PER);
    glGenBuffers(1, &EBO_PER);
    glBindVertexArray(VAO_PER);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_PER);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSully), verticesSully, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_PER);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexSully), indexSully, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // load and create a texture
    // -------------------------
    const int MAX_TEXTURES = 2;
    string texturaNome[MAX_TEXTURES] = {
        "sky.png",
        "sully.png",
    };

    unsigned int texture[MAX_TEXTURES];
    for (int i=0; i<MAX_TEXTURES; i++) {
        glGenTextures(1, &texture[i]);
        glBindTexture(GL_TEXTURE_2D, texture[i]); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method) // P/ Eixo S (X)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        int width, height, nrChannels;
        unsigned char *data = stbi_load(texturaNome[i].c_str(), &width, &height, &nrChannels, 0); //
        if (data) {
            cout << "pathNome =" << texturaNome[i] << " | "; // Debug
            cout << "nrChannels =" << nrChannels << " | "; // Debug
            cout << "width =" << width << " | "; // Debug
            cout << "height =" << height << endl; // Debug
            (nrChannels == 3) ?
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data) :
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture: " << texturaNome[i] << std::endl;
        }
        stbi_image_free(data);
    }



	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    while(!glfwWindowShouldClose(window)) {
        glm::mat4 projection = glm::ortho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
        // Comandos de renderização:
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT); // Aplica as cores acima ao buffer de cor -- poderia aplicar as cores acima a outros buffers (GL_DEPTH_BUFFER_BIT OU GL_STENCIL_BUFFER_BIT)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Usa GL_DEPTH_BUFFER_BIT para apagar o buffer das texturas

        // Desenha o fundo:
        glBindVertexArray(VAO_FUN);
        glBindTexture(GL_TEXTURE_2D, texture[0]); // Ativa a textura do fundo
        glm::mat4 transform0 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        shaderBg.use();
        unsigned int transformLoc0 = glGetUniformLocation(shaderBg.ID, "transform");
        glUniformMatrix4fv(transformLoc0, 1, GL_FALSE, glm::value_ptr(transform0));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Desenha o personagem:
        glBindVertexArray(VAO_PER);
        glBindTexture(GL_TEXTURE_2D, texture[1]); // Ativa a textura do fundo
        shaderSully.use();
        glm::mat4 transform1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        transform1 = glm::scale(transform1, glm::vec3(0.3, 0.3, 0.0)); //
        transform1 = glm::translate(transform1, glm::vec3(0.5f, 0.5f, 0.0f));
        unsigned int transformLoc1 = glGetUniformLocation(shaderSully.ID, "transform");
        glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(transform1));


        glUniform1i(glGetUniformLocation(shaderSully.ID, "sprite"), 0); //
        unsigned int offX = glGetUniformLocation(shaderSully.ID, "offX");
        //void glUniform1f(GLint location,	GLfloat v0);
        //glUniform1f(transformAlfa0, 1.0);
        glUniform1f(offX, offsetx);


        unsigned int offY = glGetUniformLocation(shaderSully.ID, "offY");
        glUniform1f(offY, offsety);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window); // Troca os buffers de cor -- evitar o flickering

        processInput(window);

        glfwPollEvents(); // Checa se algum evento foi disparado -- limpa os eventos já ocorridos e processados ?


    }

    glfwTerminate(); // Deleta todos os recursos que o GLFW alocou
    return 0;
}
