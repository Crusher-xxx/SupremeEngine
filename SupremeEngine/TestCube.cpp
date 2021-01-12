#include "TestCube.h"

// Executes from
std::string relative_path{  "../" };  // from Visual Studio
//std::string relative_path{ "../../" };  // from exe

TestCube::TestCube(glm::vec3 position) : 
	GameObject(position),
	program{ relative_path + "Shaders/vertex.glsl", relative_path + "Shaders/fragment.glsl" },
	texture1{ relative_path + "Resources/Textures/container.jpg", 0 },
	texture2{ relative_path + "Resources/Textures/awesomeface.png", 1 }
{
	// create ARRAY
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// create BUFFER
	glGenBuffers(1, &VBO);
	// bind BUFFER with TARGET
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// copy DATA into BUFFER's memory using TARGET
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);  // ???????????????? &vertices
	// set how OpenGL interprets data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);  // Positional coordinates
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));  // Texture coordinates
	glEnableVertexAttribArray(1);

}

TestCube::~TestCube()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void TestCube::render()
{
	program.use();
	program.set_uniform("crate_texture", 0);
	program.set_uniform("face_texture", 1);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}