#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <intrin.h>

#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "renderer.h"
#include "vertexbuffer.h"
#include "ElementBuffer.h"
#include "shader.h"
#include "texture.h"
void drawTriangle(glm::mat4 serpico, unsigned int times, Shader& shader, Renderer& renderer, unsigned int& VAO, ElementBuffer& EBO);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//window settings
#define W_WIDTH  1000
#define W_HEIGHT 1000
//
#define pi 3.1415926535897932


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "ooaaooaaaooaahoo", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	{
		Shader shader("shader.vert", "shader.frag");

		float vertices[] = {
			-1.0f, -1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
			 0.0f,  1.0f, 0.0f,
		};
		float color[] = {
			 1.0f,  0.0f, 0.0f,
			 0.0f,  1.0f, 0.0f,
			 0.0f,  0.0f, 1.0f,
		};
		unsigned int indices[] = {
				0,1,2
		};

		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		VertexBuffer VBO(vertices, sizeof(vertices));

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3) * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		VertexBuffer colorVBO(color, sizeof(color));

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (3) * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(1);

		ElementBuffer EBO(indices, sizeof(indices) / sizeof(unsigned int));


		//unbind
		glBindVertexArray(0);
		VBO.Unbind();
		EBO.Unbind();

		Renderer renderer;
		//blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		while (!glfwWindowShouldClose(window)) {
			processInput(window);
			//gives a solid color to the display while clearing the stuff
			renderer.clear();

			//
			//Drawing details
			int limit = 2;
			glm::mat4 serpico{ 1.0f };
			//shader.use();
			//shader.SetMat4("TrMatrix", serpico);
			//renderer.draw(VAO, EBO, shader);
			drawTriangle(serpico,6, shader, renderer, VAO, EBO);
			//for (int i = 1; i <= limit; i++){
			//	static glm::vec3 p, q, r;
			//	serpico = glm::scale(serpico, glm::vec3(1.0f, 1.0f, 1.0f));
			//	{
			//		p = glm::vec3(-1.0f, -1.0f, 0.0f);
			//		p = glm::vec3(p.x * limit, p.y * limit, p.z * limit);
			//		shader.SetMat4("TrMatrix", glm::translate(serpico, p));
			//		shader.use();
			//		renderer.draw(VAO, EBO, shader);
			//	}
			//	{
			//		q = glm::vec3(1.0f, -1.0f, 0.0f);
			//		q = glm::vec3(q.x * limit, q.y * limit, q.z * limit);
			//		shader.SetMat4("TrMatrix", glm::translate(serpico, q));
			//		shader.use();
			//		renderer.draw(VAO, EBO, shader);
			//	}
			//	{
			//		r = glm::vec3(0.0f, 1.0f, 0.0f);
			//		r = glm::vec3(r.x * limit, r.y * limit, r.z * limit);
			//		shader.SetMat4("TrMatrix", glm::translate(serpico, r));
			//		shader.use();
			//		renderer.draw(VAO, EBO, shader);
			//	}
			//}
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glDeleteVertexArrays(1, &VAO);
	}
	glfwTerminate();
	return 0;
}

void drawTriangle(glm::mat4 serpico, unsigned int times, Shader& shader, Renderer& renderer, unsigned int& VAO, ElementBuffer& EBO) {
	if (times > 0) {
		glm::vec3 p, q, r;
		serpico = glm::scale(serpico, glm::vec3(0.5f, 0.5f, 1.0f));
		//shader.SetFloat("time", (float)glfwGetTime());

		p = glm::vec3(-1.0f, -1.0f, 0.0f);
		//if (times == 1) {
		//	shader.SetMat4("TrMatrix", glm::translate(serpico, p));
		//	shader.use();
		//	renderer.draw(VAO, EBO, shader);
		//}
		drawTriangle(glm::translate(serpico, p), times - 1, shader, renderer, VAO, EBO);

		q = glm::vec3(1.0f, -1.0f, 0.0f);
		//if (times == 1) {
		//	shader.SetMat4("TrMatrix", glm::translate(serpico, q));
		//	shader.use();
		//	renderer.draw(VAO, EBO, shader);
		//}
		drawTriangle(glm::translate(serpico, q), times - 1, shader, renderer, VAO, EBO);

		r = glm::vec3(0.0f, 1.0f, 0.0f);
		//if (times == 1) {
		//	shader.SetMat4("TrMatrix", glm::translate(serpico, r));
		//	shader.use();
		//	renderer.draw(VAO, EBO, shader);
		//}
		drawTriangle(glm::translate(serpico, r), times - 1, shader, renderer, VAO, EBO);

		shader.SetMat4("TrMatrix", glm::rotate(glm::translate(serpico, glm::vec3(0.0, -1.0, 0.0)),glm::radians(180.0f),glm::vec3(0.0,0.0,0.1)));
		shader.use();
		renderer.draw(VAO, EBO, shader);
	}
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//void lop(const Shader& sh, const Renderer& rd, int limit) {
//	static float p, q, r;
//	if (limit <= 0) return;
//	limit--;
//}