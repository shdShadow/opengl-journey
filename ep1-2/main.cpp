#include <iostream>
#include "Libraries/include/glad/glad.h"
#include <math.h>
#include "GLFW/glfw3.h"
//SO, opengl is kinda lame, and doesnt give us a Vertex Shader nor a Fragment Shader
//We need to write one of our own, and by writing i mean copying it
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main (int argc, char *argv[]) {
		glfwInit();
	//Specify glwf verion
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	//The coordinate system is normalized. This means:
	//Leftmost part of the window is -1 for x
	//Rightmost part of the window is +1 for x
	//Uppermost part of the window is +1 for y
	//Lowermost part of the window if -1 for y
	//Every 3 commas is a single coordinate
	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.05f * float(sqrt(3)) * 2 / 3, 0.0f
	};
	//creating the window
	GLFWwindow* window = glfwCreateWindow(800, 800, "my realm", NULL, NULL);
	if (window == NULL){
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//We have created the window but glfw is kinda stoopid
	//so we need to tell him that we would also like to use it
	glfwMakeContextCurrent(window);
	gladLoadGL();
	//Computer graphics says that there are two buffers, the front and the back
	//The front buffer contains the pixel that are currently rendered on the screnn
	//The back buffer contains the pixels that are going to be rendered
	//Setting the color with the command below, means overwriting the back buffer
	//in order to display it, we need to swap buffers
	glViewport(0, 0, 800, 800);
	//Opengl shaders are only accessible by reference so we create reference integers
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//Opengl is stoopider than i thought
	//and the gpu cant make this sht up, so the shader in this point is unsable
	//in order to help our poor 3050, we need to compile it right now into machine code
	glCompileShader(vertexShader);
	
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//In order to use both shaders, we need to wrap them up in something that is called
	//SHADER PROGRAM
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);
	//TIDY STUFF
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLuint VAO,VBO; //it is tecnically an array, but for now we have only one object
	//order is importantg
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//Unbind 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	glClearColor(0.07f,0.13f,0.17f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
	while(!glfwWindowShouldClose(window)){
		glClearColor(0.07f,0.13f,0.17f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//WE CAN DRAW, YIPPI
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//Delete all the object we have used
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	//After we finish using our window, we need to destroy it
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
