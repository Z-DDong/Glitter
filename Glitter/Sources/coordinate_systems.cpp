#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "coordinate_systems.h"
#include <iostream>
#include "func.h"
#include <shader_s.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void coordinate_systems::initOpenGL()
{
	//initiate the glfw
	glfwInit();
	//set the version of the openGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//set the openGL profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//set the openGL not resizable
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//create the window
	window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	//if the window is null,then print the error
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	//set the current context
	glfwMakeContextCurrent(window);
	//set the callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//initiate the glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	//set the viewport
	glViewport(0, 0, 800, 600);
}

void coordinate_systems::setVertexData()
{
	//create a cube vertex data array 
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	//create the VAO, VBO, EBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);	
	glBindVertexArray(VAO);


	//bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//set the VBO's data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//bind the EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	////set the EBO's data
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//set the vertex attribute	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//set the vertex color
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	//set the vertex texture
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//unbind the VAO
	glBindVertexArray(0);
	//unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbind the EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
	//unbind the program
	glUseProgram(0);

}

void coordinate_systems::initShader()
{
	//init the shader with SmpleVertexShader.vert and SampleFragmentShader.frag
	Shader myshader("..\\Glitter\\Shaders\\coordinate.vs", "..\\Glitter\\Shaders\\coordinate.fs");
	//use the shader
	myshader.use();
	//set the shaderID
	shaderID = myshader.ID;
}

void coordinate_systems::loadTexture()
{	
	//set the texture1
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//set the texture1's wrap and filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
	//load the texture1's image
	int width, height, nrChannels;
	unsigned char* data = stbi_load("..\\Glitter\\Img\\container.jpg", &width, &height, &nrChannels, 0);
	//if the data is not null,then set the texture1's image
	if (data) {
		//set the texture1's image
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,data);
		//generate the mipmap
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	//else print the error
	else {
		std::cout << "Failed to load texture1" << std::endl;
	}
	//free the data
	stbi_image_free(data);
}

void coordinate_systems::run()
{
	//initial OpenGL 
	initOpenGL();
	//set the vertex data
	setVertexData();
	//init the shader
	initShader();
	//load the texture
	loadTexture();
	
	//render loop
	while (!glfwWindowShouldClose(window)) {
		//process the input
		processInput(window);
		//open the depth test
		glEnable(GL_DEPTH_TEST);
		//clear the color buffer and the depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
		// 
		//set the background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//clear the color buffer and the depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		////create the transform matrix
		//glm::mat4 transform = glm::mat4(1.0f);
		////set the transform matrix
		//transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		//transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f,0.0f,1.0f));
		////get the transform matrix's location
		//unsigned int transformLoc = glGetUniformLocation(shaderID, "transform");
		////set the transform matrix
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		//create model matrix
		glm::mat4 model = glm::mat4(1.0f);
		//set the model matrix 		
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f,0.0f,0.0f));
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		//create view matrix
		glm::mat4 view = glm::mat4(1.0f);
		//set the view matrix
		view = glm::translate(view, glm::vec3(0.0f,0.0f,-3.0f));
		//create projection matrix
		glm::mat4 projection = glm::mat4(1.0f);
		//set the projection matrix
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


		//get the model matrix's location
		unsigned int modelLoc = glGetUniformLocation(shaderID, "model");
		//set the model matrix
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//get the view matrix's location
		unsigned int viewLoc = glGetUniformLocation(shaderID, "view");
		//set the view matrix
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		//get the projection matrix's location
		unsigned int projectionLoc = glGetUniformLocation(shaderID, "projection");
		//set the projection matrix
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		//bind the texture
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);

		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		//create 10 time the cube
		for (unsigned int i = 0; i < 10; i++)
		{
			//create the model matrix
			glm::mat4 model = glm::mat4(1.0f);
			//translate the model matrix
			model = glm::translate(model, cubePositions[i]);
			//rotate the model matrix
			float angle = 20.0f * i;
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle+10), glm::vec3(0.5f, 1.0f, 0.0f));
			//set the model matrix
			unsigned int modelLoc = glGetUniformLocation(shaderID, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			//draw the cube
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//use the shader
		glUseProgram(shaderID);				

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//swap the buffer
		glfwSwapBuffers(window);
		//poll the event
		glfwPollEvents();
	}
}


