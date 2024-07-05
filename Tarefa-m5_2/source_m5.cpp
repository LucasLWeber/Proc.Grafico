
// Para compilar -> Estar no diretorio do arquivo exemplo_06.cpp
// g++ source_m5.cpp -o m5 ../src/glad.c ./gl_utils.cpp ./stb_image.cpp -I include -I../include -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib64 -lGLEW -lGL -lX11 -lglfw -lrt -lm -ldl

// Para executar
// ./m5



//#define STB_IMAGE_IMPLEMENTATION
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
GLFWwindow *g_window = NULL;

int main()
{
	restart_gl_log();
	start_gl();

	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS);	// depth-testing interprets a smaller value as "closer"

	Shader bgShader = Shader("./shader.vs", "./shader.fs");

	float bgVertices[] = {
        // positions          // colors           // texture coords
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // top right
         1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // bottom left
        -1.0f,  1.0f, 0.0f,	  1.0f, 1.0f, 0.0f,   0.0f, 0.0f  // top left
    };

	unsigned int bgIndex[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

	unsigned int VBO_FUN, VAO_FUN, EBO_FUN;
    glGenVertexArrays(1, &VAO_FUN);
    glGenBuffers(1, &VBO_FUN);
    glGenBuffers(1, &EBO_FUN);

    glBindVertexArray(VAO_FUN);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_FUN);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bgVertices), bgVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_FUN);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bgIndex), bgIndex, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

	string textureBgPath = "sky.png";

    unsigned int textureBg;
        // texture 1:
        glGenTextures(1, &textureBg);
        glBindTexture(GL_TEXTURE_2D, textureBg); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method) // P/ Eixo S (X)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int widthBg, heightBg, nrChannelsBg;
        unsigned char *dataBg = stbi_load(textureBgPath.c_str(), &widthBg, &heightBg, &nrChannelsBg, 0); //
        if (dataBg) {
            cout << "pathNome =" << textureBgPath << " | "; // Debug
            cout << "nrChannels =" << nrChannelsBg << " | "; // Debug
            cout << "width =" << widthBg << " | "; // Debug
            cout << "height =" << heightBg << endl; // Debug
            (nrChannelsBg == 3) ?
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthBg, heightBg, 0, GL_RGB, GL_UNSIGNED_BYTE, dataBg) :
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthBg, heightBg, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataBg);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture: " << textureBgPath << std::endl;
        }
        stbi_image_free(dataBg);


	float vertices[] = {

		// MAPEAMENTO PARA SULLY
		 0.5f, 0.5f, 0.25f, 0.25f, // top right
		 0.5f, -0.5f, 0.25f, 0.0f, // bottom right
		 -0.5f, -0.5f, 0.0f, 0.0f, // bottom left
		 -0.5f, 0.5f, 0.0f, 0.25f, // top left
	};
	unsigned int indices[] = {
		2, 1, 0, // first triangle
		0, 3, 2  // second triangle
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
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// load and create a texture



	int width, height, nrChannels;
	char vertex_shader[1024 * 256];
	char fragment_shader[1024 * 256];
	parse_file_into_str("_sprites_vs.glsl", vertex_shader, 1024 * 256);
	parse_file_into_str("_sprites_fs.glsl", fragment_shader, 1024 * 256);

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	const GLchar *p = (const GLchar *)vertex_shader;
	glShaderSource(vs, 1, &p, NULL);
	glCompileShader(vs);

	int params = -1;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params)
	{
		fprintf(stderr, "AAAAA ERROR: GL shader index %i did not compile\n", vs);
		print_shader_info_log(vs);
		return 1; // or exit or something
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	p = (const GLchar *)fragment_shader;
	glShaderSource(fs, 1, &p, NULL);
	glCompileShader(fs);

	glGetShaderiv(fs, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params)
	{
		fprintf(stderr, "BBBBBB ERROR: GL shader index %i did not compile\n", fs);
		print_shader_info_log(fs);
		return 1; // or exit or something
	}

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	glGetProgramiv(shader_programme, GL_LINK_STATUS, &params);
	if (GL_TRUE != params)
	{
		fprintf(stderr, "CCCCCC ERROR: could not link shader programme GL index %i\n", shader_programme);
		return false;
	}

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	 unsigned char *data = stbi_load("sully.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	float fw = 0.25f;
	float fh = 0.25f;
	float offsetx = 0, offsety = 0;
	int frameAtual = 3;
	int acao = 3;
	float previous = glfwGetTime();
	int sign = 1;
	int FPS = 6;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	while (!glfwWindowShouldClose(g_window))
	{
		glm::mat4 projection = glm::ortho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
		_update_fps_counter(g_window);
		double current_seconds = glfwGetTime();

		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, g_gl_width, g_gl_height);

		// bind Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(shader_programme, "sprite"), 0);

		glUseProgram(shader_programme);
		glEnable(GL_BLEND);
		glUniform1f(glGetUniformLocation(shader_programme, "offsetx"), offsetx);
		glUniform1f(glGetUniformLocation(shader_programme, "offsety"), offsety);

		if (GLFW_PRESS == glfwGetKey(g_window, GLFW_KEY_W))
		{
			offsety = 0.0f;
			if ((current_seconds - previous) > (1/(float)FPS)){
				previous = current_seconds;
				frameAtual = (frameAtual + 1) % 4;
				offsetx = fw * (float)frameAtual;
			}

		}
		else if(GLFW_PRESS == glfwGetKey(g_window, GLFW_KEY_S))
		{
			offsety = 0.75f;
			if ((current_seconds - previous) > (1/(float)FPS)){
				previous = current_seconds;
				frameAtual = (frameAtual + 1) % 4;
				offsetx = fw * (float)frameAtual;
			}
		}
		else if(GLFW_PRESS == glfwGetKey(g_window, GLFW_KEY_D))
		{
			offsety = 0.25f;
			if ((current_seconds - previous) > (1/(float)FPS)){
				previous = current_seconds;
				frameAtual = (frameAtual + 1) % 4;
				offsetx = fw * (float)frameAtual;
			}
		}
		else if(GLFW_PRESS == glfwGetKey(g_window, GLFW_KEY_A))
		{
			offsety = 0.50f;
			if ((current_seconds - previous) > (1/(float)FPS)){
				previous = current_seconds;
				frameAtual = (frameAtual + 1) % 4;
				offsetx = fw * (float)frameAtual;
			}
		}

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);




		glfwPollEvents();
		glfwSwapBuffers(g_window);



	}

	// close GL context and any other GLFW resources
	glfwTerminate();
	return 0;
}
