// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Processamento Gráfico
// Módulo 4
// Tarefa: Resposta ao Desafio M4
// Data: 22/06/2024
// Professor: Fernando Marson
// Aluno: Lucas Lazzaretti Weber
// Registro Acadêmico: 1930506

// --- Compilar com ---
// g++ texture.cpp -o texture ../../src/glad.c -I include -I../../include -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib64 -lGLEW -lGL -lX11 -lglfw -lrt -lm -ldl

// --- Executar com ---
// ./texture


#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 

#include <iostream>
#include <cmath>

#include "../../Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

#include <vector>
#include <cstdlib>
#include <ctime>  

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}



int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "Tarefa-M4", NULL, NULL);
    if (window == NULL) {
        cout << "###Erro: Falha na criação da janela GLFW !" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); 
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "###Erro: Falha na inicialização do GLAD !" << endl;
        return -1;
    }
    
    // Define Hard Coded 1 Shader para cada textura utilizada na tarefa
	
	Shader meusShaders[4] = {
    Shader("./shader.vs", "./shader.fs"),
    Shader("./shader.vs", "./shader.fs"),
    Shader("./shader.vs", "./shader.fs"),
    Shader("./shader.vs", "./shader.fs")
};

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // top right
         1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // bottom left
        -1.0f,  1.0f, 0.0f,	  1.0f, 1.0f, 0.0f,   0.0f, 0.0f  // top left
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // Criacao e carregamento das texturas
    // -------------------------
    unsigned int textureBg, textureTree, textureBirdOne, textureBirdTwo;
    
    unsigned int textures[] = {textureBg, textureTree, textureBirdOne, textureBirdTwo};
    
    std::vector<std::string> images = {"../img/bg.png", "../img/tree.png", "../img/bird-1.png", "../img/bird-2.png"};
    
    
    for (int i = 0; i < images.size(); i++) {
		glGenTextures(1, &textures[i]);
		glBindTexture(GL_TEXTURE_2D, textures[i]); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		int width, height, nrChannels;
		unsigned char *data = stbi_load(images[i].c_str(), &width, &height, &nrChannels, 0);
		
		if (data) {
			
			(nrChannels == 3)
				? glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data)
				: glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "Failed to load texture" << std::endl;
		}
		
		stbi_image_free(data);
	}
    

    // Loop de renderização
    while(!glfwWindowShouldClose(window)) { 
        processInput(window);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); 

        // bind Texture Background
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glm::mat4 transformBg = glm::mat4(1.0f);
        meusShaders[0].use();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        unsigned int transformLocBg = glGetUniformLocation(meusShaders[0].ID, "transform");
        glUniformMatrix4fv(transformLocBg, 1, GL_FALSE, glm::value_ptr(transformBg));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                
        // bind Texture Tree
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        glm::mat4 transformTree = glm::mat4(1.0f);
        transformTree = glm::scale(transformTree, glm::vec3(0.3, 0.3, 0.2));
        transformTree = glm::translate(transformTree, glm::vec3(-1.5f, -1.5f, 0.0f));
        meusShaders[1].use();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        unsigned int transformLocTree = glGetUniformLocation(meusShaders[1].ID, "transform");
        glUniformMatrix4fv(transformLocTree, 1, GL_FALSE, glm::value_ptr(transformTree));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		// bind Texture Bird One
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glm::mat4 transformBirdOne = glm::mat4(1.0f);
		transformBirdOne = glm::scale(transformBirdOne, glm::vec3(0.1, 0.1, 0.2));
		transformBirdOne = glm::translate(transformBirdOne, glm::vec3(-1.0f, 1.0f, 0.0f));
		meusShaders[2].use();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		unsigned int transformLocBirdOne = glGetUniformLocation(meusShaders[2].ID, "transform");
		glUniformMatrix4fv(transformLocBirdOne, 1, GL_FALSE, glm::value_ptr(transformBirdOne));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		// bind Texture Bird Two
		glBindTexture(GL_TEXTURE_2D, textures[3]);
		glm::mat4 transformBirdTwo = glm::mat4(1.0f);
		transformBirdTwo = glm::scale(transformBirdTwo, glm::vec3(0.1, 0.1, 0.2));
		transformBirdTwo = glm::translate(transformBirdTwo, glm::vec3(-3.5f, -3.5f, 0.0f));
		meusShaders[3].use();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		unsigned int transformLocBirdTwo = glGetUniformLocation(meusShaders[2].ID, "transform");
		glUniformMatrix4fv(transformLocBirdTwo, 1, GL_FALSE, glm::value_ptr(transformBirdTwo));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
       
        // Bind VAO
        glBindVertexArray(VAO);

        glfwSwapBuffers(window); 
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
