#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Logger.h"
#include <vector>
#include "Program.h"
#include "Texture.h"
#include "Timer.h"

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
	//glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE); // for uncapped fps

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

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3,   // second triangle
	};


	// create ARRAY
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// create BUFFER
	unsigned int VBO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind BUFFER with TARGET
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// copy DATA into BUFFER's memory using TARGET
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// set how OpenGL interprets data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	

	Texture texture1{ "../Resources/Textures/container.jpg", 0 };
	Texture texture2{ "../Resources/Textures/awesomeface.png", 1 };

	programs[0].use();
	glUniform1i(glGetUniformLocation(programs[0].ID, "ourTexture1"), 0);
	glUniform1i(glGetUniformLocation(programs[0].ID, "ourTexture2"), 1);

	glEnable(GL_DEPTH_TEST);
	



	main_loop(window, &VAO, programs);


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

void process(GLFWwindow* window, float& k, glm::mat4& trans)
{
	float angle{ 0.1f };
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		k += 0.01;
		trans = glm::rotate(trans, -angle, glm::vec3(1,0,0));
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		k -= 0.01;
		trans = glm::rotate(trans, angle, glm::vec3(1, 0, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		trans = glm::rotate(trans, angle, glm::vec3(0, 1, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		trans = glm::rotate(trans, -angle, glm::vec3(0, 1, 0));
	}


	k = k < 0 ? 0 : k;
	k = k > 1 ? 1 : k;
}





void main_loop(GLFWwindow* window, unsigned int* VAO, const std::vector<Program>& programs)
{
	// Drawing mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	float k{ 0.5 };
	glm::mat4 trans = glm::mat4(1.0f);
	//trans = glm::scale(trans, glm::vec3(2, 0.7, 1.0));


	


	while (!glfwWindowShouldClose(window))
	{
		Timer timer;
		processInput(window);

		
		process(window, k, trans);
		programs[0].set_uniform("k", k);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		programs[0].use();
		glBindVertexArray(VAO[0]);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		//glm test
		//glm::mat4 trans = glm::mat4(1.0f);
		//trans = glm::rotate(trans, angle, around);
		//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
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

		glm::mat4 view = glm::mat4(1.0f);
		// note that we're translating the scene in the reverse direction of where we want to move
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(105.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		programs[0].set_uniform("transform", trans);
		programs[0].set_uniform("view", view);
		programs[0].set_uniform("projection", projection);

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			programs[0].set_uniform("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//glFlush(); // for uncapped fps
		glfwSwapBuffers(window);
		glfwPollEvents();
		std::cout << 1000 / timer.get_passed_time() << '\n'; // measure fps
	}
}