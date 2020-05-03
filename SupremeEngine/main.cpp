#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include<iostream>
#include"Logger.h"
#include<vector>
#include"Program.h"
#include"Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void main_loop(GLFWwindow* window, unsigned int* VAO, const std::vector<Program>& programs);


int main()
{
	// Initialize the library
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Supreme Engine", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Register action on window resize
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);




	std::vector<Program> programs;
	programs.push_back(Program{ "../Shaders/vertex.glsl", "../Shaders/fragment.glsl" });


	// create DATA
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	float first_triangle[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3,   // second triangle
	};


	// create ARRAY
	unsigned int VAO[2];
	glGenVertexArrays(2, VAO);
	glBindVertexArray(VAO[0]);

	// create BUFFER
	unsigned int VBO[2], EBO;
	glGenBuffers(2, VBO);
	glGenBuffers(1, &EBO);

	// bind BUFFER with TARGET
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	// copy DATA into BUFFER's memory using TARGET
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// set how OpenGL interprets data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);




	Texture texture1{ "../Resources/Textures/container.jpg", 0 };
	Texture texture2{ "../Resources/Textures/awesomeface.png", 1 };

	programs[0].use();
	glUniform1i(glGetUniformLocation(programs[0].ID, "ourTexture1"), 0);
	glUniform1i(glGetUniformLocation(programs[0].ID, "ourTexture2"), 1);
	//programs[0].set_uniform("ourTexture2", std::vector<float>{1}); // doesn't work because of float

	



	main_loop(window, VAO, programs);


	glfwTerminate();



	return 0;
}







void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// Set render area size
	glViewport(0, 0, width, height);
	print_log_message("Resized to " + std::to_string(width) + 'x' + std::to_string(height), 1);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void process(GLFWwindow* window, float& k)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		k += 0.01;
	else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		k -= 0.01;

	if (k >= 1)
		k = 1;
	if (k <= 0)
		k = 0;
}

void main_loop(GLFWwindow* window, unsigned int* VAO, const std::vector<Program>& programs)
{
	// Drawing mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	float k{ 0.5 };
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		
		process(window, k);
		programs[0].set_uniform_1f("k", k);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		programs[0].use();
		glBindVertexArray(VAO[0]);
		//programs[0].set_uniform("xoffset", std::vector<float>{0.5});
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		//glm test
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(-1.0, 1.0, 1.0));
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::scale(trans, glm::vec3(1.7, 0.5, 1.0));
		/*unsigned int transformLoc = glGetUniformLocation(programs[0], "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));*/
		programs[0].set_uniform_matrix_4fv("transform", trans);



		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}