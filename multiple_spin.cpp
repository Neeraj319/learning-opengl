//#include<glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//#include<random>
//#include<math.h>
//#include<thread>
//#include<chrono>
//#include"shader_s.h"
//
//#define M_PI 3.14159
//
//unsigned int VBO;
//unsigned int EBO;
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//}
//
//const float radius = 0.069;
//
//const int MAX_TRIANGLES = 196;
//const int MAX_COORDNATES = 9;
//const int MAX_VERTICES = 3;
//
//float vertices[MAX_TRIANGLES * MAX_COORDNATES];
//unsigned int indices[MAX_TRIANGLES * MAX_VERTICES];
//
//float startingH = -0.9, startingK = 0.9;
//float currentH = startingH, currentK = startingK;
//
//void generateEquilateralTriangle(float centerX, float centerY, float radius, int index) {
//	vertices[index++] = centerX + (radius * cos(210 * M_PI / 180.0));
//	vertices[index++] = centerY + (radius * sin(210 * M_PI / 180.0));
//	vertices[index++] = 0.0f;
//
//	vertices[index++] = centerX + (radius * cos(330 * M_PI / 180.0));
//	vertices[index++] = centerY + (radius * sin(330 * M_PI / 180.0));
//	vertices[index++] = 0.0f;
//
//	vertices[index++] = centerX;
//	vertices[index++] = centerY + radius;
//	vertices[index++] = 0.0f;
//}
//bool isTraingleDrawn = false;
//
//float getClockWiseAngle(float x, float y, float h, float k) {
//	float counterClockwiseAngle = atan2((y - k), (x - h));
//	return counterClockwiseAngle;
//}
//
//float getCounterClockwiseAngle(float x, float y, float h, float k) {
//	float angle = atan2((y - k), (x - h));
//
//	if (angle < 0) {
//		angle += 2 * M_PI;
//	}
//	return angle;
//}
//
//void spinTriangle() {
//	//float h = 0, k = 0;
//	float h = startingH;
//	float k = startingK;
//	float firstTheta, secondTheta, thirdTheta;
//	for (int i = 0; i < MAX_TRIANGLES * MAX_COORDNATES; i += 9) {
//		float angleDiff = 0.05;
//		if (k > 0) {
//			firstTheta = getClockWiseAngle(vertices[i + 0], vertices[i + 1], h, k);
//			secondTheta = getClockWiseAngle(vertices[i + 3], vertices[i + 4], h, k);
//			thirdTheta = getClockWiseAngle(vertices[i + 6], vertices[i + 7], h, k);
//
//			vertices[i + 0] = h + (radius * cos(firstTheta - angleDiff));
//			vertices[i + 1] = k + (radius * sin(firstTheta - angleDiff));
//
//			vertices[i + 3] = h + (radius * cos(secondTheta - angleDiff));
//			vertices[i + 4] = k + (radius * sin(secondTheta - angleDiff));
//
//			vertices[i + 6] = h + (radius * cos(thirdTheta - angleDiff));
//			vertices[i + 7] = k + (radius * sin(thirdTheta - angleDiff));
//		}
//		else {
//			firstTheta = getCounterClockwiseAngle(vertices[i + 0], vertices[i + 1], h, k);
//			secondTheta = getCounterClockwiseAngle(vertices[i + 3], vertices[i + 4], h, k);
//			thirdTheta = getCounterClockwiseAngle(vertices[i + 6], vertices[i + 7], h, k);
//
//			vertices[i + 0] = h + (radius * cos(firstTheta + angleDiff));
//			vertices[i + 1] = k + (radius * sin(firstTheta + angleDiff));
//
//			vertices[i + 3] = h + (radius * cos(secondTheta + angleDiff));
//			vertices[i + 4] = k + (radius * sin(secondTheta + angleDiff));
//
//			vertices[i + 6] = h + (radius * cos(thirdTheta + angleDiff));
//			vertices[i + 7] = k + (radius * sin(thirdTheta + angleDiff));
//		}
//		h = h + 2 * radius;
//		if (h > 1) {
//			h = startingH;
//			k = k - 2 * radius;
//		}
//	}
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
//
//}
//void drawTriangles() {
//
//	// Generate an equilateral triangle centered at the clicked position
//	int current = 0;
//	for (int i = 0; i < MAX_TRIANGLES; i++) {
//		indices[i * 3] = i * 3;
//		indices[i * 3 + 1] = i * 3 + 1;
//		indices[i * 3 + 2] = i * 3 + 2;
//	}
//	int index = 0;
//	for (int i = 0; i < MAX_TRIANGLES; i++) {
//		generateEquilateralTriangle(currentH, currentK, radius, index);
//		index += 9;
//		currentH = currentH + 2 * radius;
//		if (currentH > 1) {
//			currentH = startingH;
//			currentK = currentK - 2 * radius;
//		}
//	}
//
//	// Update the vertex buffer
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	isTraingleDrawn = true;
//}
//
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
//	Shader shader("fragmentShader.glsl", "vertexShader.glsl");
//
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	glBindVertexArray(VAO);
//	glfwSwapInterval(1);
//
//	glGenBuffers(1, &EBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	drawTriangles();
//
//	while (!glfwWindowShouldClose(window)) {
//		auto frameStart = std::chrono::high_resolution_clock::now();
//		//processInput(window);
//
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		shader.use();
//		glDrawElements(GL_TRIANGLES, MAX_TRIANGLES * MAX_VERTICES, GL_UNSIGNED_INT, 0);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//		if (isTraingleDrawn) {
//			spinTriangle();
//		}
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
//	glfwTerminate();
//
//	return 0;
//}
