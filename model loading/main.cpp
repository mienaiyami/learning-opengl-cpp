#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "renderer.h"

constexpr int SCR_WIDTH = 1000;
constexpr int SCR_HEIGHT = 1000;

int main() {
    Camera camera(glm::vec3(2.0f, 0.0f, 5.0f));
    GLFWprogram glfwprogram(SCR_WIDTH, SCR_WIDTH, camera);
    GLFWwindow *window = glfwprogram.window;
    {
        glm::vec3 lightPos{1.0f, 0.0f, 0.0f};
        glm::vec3 lightColor{1.0, 1.0, 1.0};

        Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(glfwprogram.window, true);
        ImGui_ImplOpenGL3_Init((char *)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
        ImGui::StyleColorsDark();

        Shader lightingShader("./shaders/shader.vert", "./shaders/shader.frag");
        Shader lightCubeShader("./shaders/lightShader.vert", "./shaders/lightShader.frag");

    	stbi_set_flip_vertically_on_load(true);
        Model model1("../test model/backpack.obj");

        float gridSquare[] = {
            -1.0, 0.0, 0.0, 	1.0, 0.0, 0.0,
        };
        VertexBuffer gridVBO(gridSquare, sizeof(gridSquare));
        VertexArray gridVAO(3, 1);
        gridVAO.attrPointer(0, 3, (void *)0);

        // uncomment this call to draw in wireframe polygons.
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        while (!glfwWindowShouldClose(window)) {

            glfwprogram.setNewTime();
            glfwprogram.processInput();
            renderer.clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
            glm::mat4 view = camera.getViewMatrix();

            renderer.drawGrid(20, lightCubeShader, gridVAO, projection, view);
			
			if (glfwprogram.camIsLight) {
				lightPos = camera.getTarget();
			}
			lightingShader.setVec3("viewPos", camera.Position);
			lightingShader.setVec3("light.position", lightPos);
			

			glm::vec3 diffuseColor = lightColor * glm::vec3(0.8f);
			glm::vec3 ambientColor = diffuseColor * glm::vec3(0.5f);
			lightingShader.setFloat("light.constant",  1.0f);
        	lightingShader.setFloat("light.linear", 0.09);
        	lightingShader.setFloat("light.quadratic", 0.032);
			lightingShader.setVec3("light.ambient", ambientColor);
			lightingShader.setVec3("light.diffuse", diffuseColor);
			lightingShader.setVec3("light.specular", lightColor);

            lightingShader.setMat4("projection", projection);
            lightingShader.setMat4("view", view);
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        	lightingShader.setMat4("model", model);
            model1.Draw(lightingShader);

            {
                ImGui::SetNextWindowSize({400, 500});
                ImGui::SetNextWindowBgAlpha(0.3f);
                float imguiWidth = 400.0;
                ImGui::SetNextWindowPos({glfwprogram.window_width - imguiWidth, 0.0});
                ImGui::Begin("fffffffff");
                ImGui::Text("shift : down");
                ImGui::Text("space : up");
                ImGui::Text("C \t: move light");
                ImGui::Text("V \t: exit camera");
                ImGui::SliderFloat("fov", &camera.Zoom, 1.0, 100.0);
                if (ImGui::Button("default fov")) {
                    camera.Zoom = 45.0f;
                }
                if (ImGui::Button("lines")) {
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                }
                if (ImGui::Button("triangle")) {
					glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
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
