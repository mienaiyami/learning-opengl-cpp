#include "shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

//window settings
#define W_WIDTH 1000
#define W_HEIGHT 1000
#define TIMES 1

constexpr double pi = 3.141592653589793238462643383279502884L;

float sind(int i) {
    return sinf(i * pi / 180*TIMES);
}
float cosd(int i) {
    return cosf(i * pi / 180*TIMES);
}

int main() {
    //BEGINNING OF MAIN()=======================================================================
    glfwInit(); //initialize
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "ooaaooaaaooaahoo", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shaderMain("./shaders/shader.vert", "./shaders/shader.frag");
    float vertices[361*3*TIMES] = {0.0f, 0.0f, 0.0f};
    for (int degree = 0; degree < 360*TIMES; degree++) {
        vertices[3 * degree + 3] = cosd(degree);
        vertices[3 * degree + 4] = sind(degree);
        vertices[3 * degree + 5] = 0.0f;
        // std::cout << "vertices["<<degree<<"] : \t" << vertices[3 * degree + 3]<<" "
        //                               << vertices[3 * degree + 4]<<" "
        //                               << vertices[3 * degree + 5] << std::endl;
        // std::cout << "vertices i : " << degree << std::endl;
    }
    unsigned int indices[(360 * 3*TIMES)]={0};
    for (int degree = 0; degree < 360*TIMES; degree++) {
        indices[3 * degree] = 0;
        indices[3 * degree + 1] = degree + 1;
        indices[3 * degree + 2] = degree + 2;
        // std::cout << "indices i : " << degree<< "\n\t"<<indices[3 * degree]<<" "<<
        //                                              indices[3 * degree + 1]<< " "<<
        //                                              indices[3 * degree + 2] << std::endl;
    }
    indices[(360 * 3*TIMES) -1] = 1;
    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float) , (void *)0);
    glEnableVertexAttribArray(0);

    //unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        //gives a solid color to the display while clearing the stuff
        glClearColor(0.1f, 0.125f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Draw triangle
        shaderMain.use();
        const float time = glfwGetTime();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
    //END OF MAIN()=============================================================================
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}