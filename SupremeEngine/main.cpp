#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Logger.h"
#include <vector>
#include "Program.h"
#include "Texture.h"
#include "Timer.h"
#include "Camera.h"
#include "TestCube.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void main_loop(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);


int main()
{
	// Initialize the library
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);  // vsync
	//glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);  // uncapped FPS

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
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	// Drawing mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	main_loop(window);
	glfwTerminate();

	return 0;
}







void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);  // Set render area size
	print_log_message("Resized to " + std::to_string(width) + 'x' + std::to_string(height), 1);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

Camera camera;
void process(GLFWwindow* window, float& mixing_coeff, glm::mat4& trans, float deltaTime)
{
	float angle{ 1.0f };
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixing_coeff += 0.5 * deltaTime;
		trans = glm::rotate(trans, -angle * deltaTime, glm::vec3(1, 0, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixing_coeff -= 0.5 * deltaTime;
		trans = glm::rotate(trans, angle * deltaTime, glm::vec3(1, 0, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		trans = glm::rotate(trans, angle * deltaTime, glm::vec3(0, 1, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		trans = glm::rotate(trans, -angle * deltaTime, glm::vec3(0, 1, 0));
	}


	mixing_coeff = mixing_coeff < 0 ? 0 : mixing_coeff;
	mixing_coeff = mixing_coeff > 1 ? 1 : mixing_coeff;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.process_keyboard(Movement_direction::forward, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.process_keyboard(Movement_direction::backward, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.process_keyboard(Movement_direction::left, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.process_keyboard(Movement_direction::right, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.process_keyboard(Movement_direction::up, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera.process_keyboard(Movement_direction::down, deltaTime);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	camera.process_mouse_movement(xpos, ypos);
}



void main_loop(GLFWwindow* window)
{
	float mixing_coeff{ 0.5 };
	glm::mat4 trans = glm::mat4(1.0f);

	double deltaTime = 0.0f;  // Time between current frame and last frame
	Timer timer;
	TestCube cubes[] = {
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

	while (!glfwWindowShouldClose(window))
	{
		timer.reset();
		glfwPollEvents();
		processInput(window);
		process(window, mixing_coeff, trans, deltaTime);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glm::mat4 view = glm::mat4(1.0f);
		view = camera.get_view_matrix();
		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(camera.field_of_view), 800.0f / 600.0f, 0.1f, 100.0f);

		for (unsigned int i = 0; i < 10; i++)
		{
			cubes[i].program.set_uniform("transform", trans);
			cubes[i].program.set_uniform("view", view);
			cubes[i].program.set_uniform("projection", projection);
			cubes[i].program.set_uniform("mixing_coeff", mixing_coeff);

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubes[i].position);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			cubes[i].program.set_uniform("model", model);

			cubes[i].render();
		}

		std::cout << timer.get_fps() << '\r';  // measure fps
		deltaTime = timer.get_delta_time();

		glfwSwapBuffers(window);  // vsync
		//glFlush();  // uncapped fps
	}
}