//#include<glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//#include<random>
//#include<math.h>
//#include<thread>
//#include<chrono>
//
//#define M_PI 3.14159
//
//unsigned int VBO;
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//}
//
//float vertices[] = {
//	 0.5f,  0.5f, 0.0f,  // top right
//	 0.5f, -0.5f, 0.0f,  // bottom right
//	-0.5f, -0.5f, 0.0f,  // bottom left
//	-0.5f,  0.5f, 0.0f
//};
//
//unsigned int indices[] = {  
//	0, 1, 3,   // first triangle
//	1, 2, 3    // second triangle
//};
//
//const char* vertexShaderSrc = "#version 460 core \n"
//"layout (location = 0) in vec3 aPos; \n"
//"void main()"
//"{"
//"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
//"}\0";
//
//const char* fragmentShaderSrc = "#version 460 core\n"
//"out vec4 FragColor;"
//"void main(){"
//"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
//"}\0";
//
//void processInput(GLFWwindow* window) {
//	double xpos, ypos;
//	int height, width;
//	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
//		double xpos, ypos;
//		int width, height;
//
//		glfwGetCursorPos(window, &xpos, &ypos);
//		glfwGetWindowSize(window, &width, &height);
//
//		// Convert screen coordinates to normalized device coordinates
//		float normalizedX = (2.0f * xpos / width) - 1.0f;
//		float normalizedY = 1.0f - (2.0f * ypos / height);
//
//		std::cout << "Mouse clicked at: " << xpos << ", " << ypos << std::endl;
//		std::cout << "Normalized coords: " << normalizedX << ", " << normalizedY << std::endl;
//	}
//}
//
//int main() {
//	srand(static_cast<unsigned int>(time(0)));
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	GLFWwindow* window = glfwCreateWindow(800, 600, "Learn opengl", NULL, NULL);
//
//	if (window == NULL) {
//		std::cout << "Failed to create glfw window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//	glViewport(0, 0, 800, 600);
//
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	// setup vertices
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	// setup VAO
//	unsigned int VAO;
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//
//	// vertex shader
//	unsigned int vertexShader;
//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
//	glCompileShader(vertexShader);
//
//	int success;
//	char infoLog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		glad_glGetShaderInfoLog(vertexShader, 521, NULL, infoLog);
//		std::cout << "Error::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//
//
//	// fragment shader
//	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
//	glCompileShader(fragmentShader);
//
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		glad_glGetShaderInfoLog(fragmentShader, 521, NULL, infoLog);
//		std::cout << "Error::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//
//	// link shaders
//	unsigned int shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//	if (!success) {
//		glad_glGetShaderInfoLog(shaderProgram, 521, NULL, infoLog);
//		std::cout << "Error::Shader Linking Failed\n" << infoLog << std::endl;
//	}
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	glBindVertexArray(VAO);
//	glfwSwapInterval(4);
//
//	unsigned int EBO;
//	glGenBuffers(1, &EBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	while (!glfwWindowShouldClose(window)) {
//		processInput(window);
//		auto frameStart = std::chrono::high_resolution_clock::now();
//
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		glUseProgram(shaderProgram);
//		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//		auto frameEnd = std::chrono::high_resolution_clock::now();
//		auto frameDuration = std::chrono::duration_cast<std::chrono::microseconds>(frameEnd - frameStart);
//		const std::chrono::microseconds targetFrameTime(16667);
//
//		if (frameDuration < targetFrameTime) {
//			std::this_thread::sleep_for(targetFrameTime - frameDuration);
//		}
//	}
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteProgram(shaderProgram);
//	glfwTerminate();
//
//	return 0;
//}
