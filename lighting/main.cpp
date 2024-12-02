#include "renderer.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

constexpr int SCR_WIDTH = 1000;
constexpr int SCR_HEIGHT = 1000;

int main() {
	Camera camera(glm::vec3(2.0f, 0.0f, 5.0f));
	GLFWprogram glfwprogram(SCR_WIDTH, SCR_WIDTH, camera);
	GLFWwindow* window = glfwprogram.window;
	{
		glm::vec3 lightPos{ 1.0f, 0.0f, 0.0f };
		glm::vec3 lightColor{ 1.0,1.0,1.0 };

		Renderer renderer;
		renderer.importModel("../monky.obj");

		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(glfwprogram.window, true);
		ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
		ImGui::StyleColorsDark();

		Shader lightingShader("./shaders/shader.vert", "./shaders/shader.frag");
		Shader lightCubeShader("./shaders/lightShader.vert", "./shaders/lightShader.frag");

		float gridSquare[]={
			-1.0, 0.0, 0.0,		1.0, 0.0, 0.0,
		};
		VertexBuffer gridVBO(gridSquare,sizeof(gridSquare));
		VertexArray  gridVAO(3,1);
		gridVAO.attrPointer(0,3);

		float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,    0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,    0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,    1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,    1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,    1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,    0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,    0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,     1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,     0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,     1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,     1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,     0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,     1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,     0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,     1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,     1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,     1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,     0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,     0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,     0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,     1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,     1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,     1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,     0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,      0.0f, 1.0f
		};
		float textureCoords[] = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,

			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,

			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f,

			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f
		};
		VertexBuffer VBO(vertices, sizeof(vertices));
		// VertexBuffer textureVBO(textureCoords,sizeof(textureCoords));
		VertexArray ObjVAO(8, 3);

		VBO.bind();
		ObjVAO.attrPointer(0, 3);
		ObjVAO.attrPointer(1, 3);
		ObjVAO.attrPointer(2, 2);

		VBO.bind();
		VertexArray lightVAO(8, 1);
		lightVAO.attrPointer(0, 3);

		Textures textureManager;
		textureManager.newTexture("./img/container2.png", true);
		textureManager.newTexture("./img/container2_specular.png", true);
		// textureManager.newTexture("./img/matrix.jpg");
		textureManager.useAllTextures();
		// textureManager.newTexture("./img/awesomeface.png", true);

		// uncomment this call to draw in wireframe polygons.
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		while (!glfwWindowShouldClose(window)) {

			glfwprogram.setNewTime();
			glfwprogram.processInput();
			renderer.clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			
			glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			glm::mat4 view = camera.getViewMatrix();

			renderer.drawGrid(20,lightCubeShader,gridVAO,projection,view);


			// lightingShader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
			//
			// bind light to cam
			//
			if (glfwprogram.camIsLight) {
				lightPos = camera.getTarget();
			}
			lightingShader.setVec3("viewPos", lightPos);
			lightingShader.setVec3("light.position", lightPos);
			
			lightingShader.setFloat("light.constant",  1.0f);
        	lightingShader.setFloat("light.linear", 0.09);
        	lightingShader.setFloat("light.quadratic", 0.032);

			glm::vec3 diffuseColor = lightColor * glm::vec3(0.8f);
			glm::vec3 ambientColor = diffuseColor * glm::vec3(0.3f);
			lightingShader.setVec3("light.ambient", ambientColor);
			lightingShader.setVec3("light.diffuse", diffuseColor);
			lightingShader.setVec3("light.specular", lightColor);
			//glm::mat4 model1(1.0f);
			//lightPos = glm::rotate(model1, glm::radians(1.0f), glm::vec3(0.0, 1.0, 0.0)) * glm::vec4(lightPos, 1.0);

			// glm::quat lightQuat{ 1.0, 0.0, 0.002, 0.0  };
			// lightPos = glm::toMat4(lightQuat) * glm::vec4(lightPos, 1.0);
			// lightingShader.setVec3("lightPos", lightPos);
			lightingShader.setInt("material.diffuse",0);
			lightingShader.setInt("material.specular", 1);
			lightingShader.setFloat("material.shininess", 4.0f);

			lightingShader.setVec3("viewPos", camera.Position);

			lightingShader.setMat4("projection", projection);
			lightingShader.setMat4("view", view);
			glm::mat4 model = glm::mat4(1.0f);
			// lightingShader.setMat4("model", model);
			// renderer.draw(lightingShader, ObjVAO, 0, 36);

			glm::vec3 cubePositions[] = {
				glm::vec3( 0.0f,  0.0f,  0.0f),
				glm::vec3( 2.0f,  5.0f, -15.0f),
				glm::vec3(-1.5f, -2.2f, -2.5f),
				glm::vec3(-3.8f, -2.0f, -12.3f),
				glm::vec3( 2.4f, -0.4f, -3.5f),
				glm::vec3(-1.7f,  3.0f, -7.5f),
				glm::vec3( 1.3f, -2.0f, -2.5f),
				glm::vec3( 1.5f,  2.0f, -2.5f),
				glm::vec3( 1.5f,  0.2f, -1.5f),
				glm::vec3(-1.3f,  1.0f, -1.5f)
			};
			for(unsigned int i = 0; i < 10; i++){
				model = glm::mat4(1.0f);
				model = glm::translate(model, cubePositions[i]);
				float angle = 20.0f * i;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				lightingShader.setMat4("model", model);
				renderer.draw(lightingShader, ObjVAO, 0, 36);
			}

			lightCubeShader.setMat4("projection", projection);
			lightCubeShader.setMat4("view", view);
			model = glm::mat4(1.0f);
			model = glm::translate(model, lightPos);
			model = glm::scale(model, glm::vec3(0.2f));
			lightCubeShader.setVec4("color", glm::vec4(lightColor,1.0f));
			lightCubeShader.setMat4("model", model);

			// renderer.draw(lightCubeShader, lightVAO, 0, 36);

			{
				ImGui::SetNextWindowSize({ 400,500 });
				ImGui::SetNextWindowBgAlpha(0.3f);
				float imguiWidth = 400.0;
				ImGui::SetNextWindowPos({ glfwprogram.window_width - imguiWidth,0.0 });
				ImGui::Begin("fffffffff");
				ImGui::Text("shift : down");
				ImGui::Text("space : up");
				ImGui::Text("C \t: move light");
				ImGui::Text("V \t: exit camera");
				ImGui::ColorPicker3("lightColor", &lightColor[0]);
				ImGui::SliderFloat("lightPos.x", &lightPos.x, -10.0, 10.0);
				ImGui::SliderFloat("lightPos.y", &lightPos.y, -10.0, 10.0);
				ImGui::SliderFloat("lightPos.z", &lightPos.z, -10.0, 10.0);
				ImGui::SliderFloat("fov", &camera.Zoom, 1.0, 100.0);
				if (ImGui::Button("default fov")) {
					camera.Zoom = 45.0f;
				}
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::End();
			}
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			glfwprogram.endLoop();
		}
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwprogram.closeProgram();
	return 0;
}
