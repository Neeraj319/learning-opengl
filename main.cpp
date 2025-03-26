#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include<random>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
float randomFloat()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	
	std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

	return dist(gen);

}

float vertices[9] = {
};


void processInput(GLFWwindow* window) {
	double xpos, ypos;
	int height, width;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
		glfwGetCursorPos(window, &xpos, &ypos);
		glfwGetWindowSize(window, &width, &height);
		double normalizedX = (-1.0f + 2.0f * (double)xpos) / width;
		double normlizedY = (1.0f - 2.0f * (double)(ypos)) / height;
		std::cout << "current x pos is " << xpos << " y pos is " << ypos << std::endl;
		std::cout << "normalized x pos is" << normalizedX << " y pos is " << normlizedY << std::endl;
	}
}

const char* vertexShaderSrc = "#version 460 core \n"
"layout (location = 0) in vec3 aPos; \n"
"void main()"
"{"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
"}\0";

const char* fragmentShaderSrc = "#version 460 core\n"
"out vec4 FragColor;"
"void main(){"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
"}\0";

int main() {
	srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < 9; i++) {
		vertices[i] = randomFloat();
	}
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Learn opengl", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create glfw window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// setup vertices
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// setup VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glad_glGetShaderInfoLog(vertexShader, 521, NULL, infoLog);
		std::cout << "Error::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	// fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glad_glGetShaderInfoLog(fragmentShader, 521, NULL, infoLog);
		std::cout << "Error::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// link shaders
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glad_glGetShaderInfoLog(shaderProgram, 521, NULL, infoLog);
		std::cout << "Error::Shader Linking Failed\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(VAO);
	glfwSwapInterval(4);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwTerminate();

	return 0;
}
