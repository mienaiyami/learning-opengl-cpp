#include "GLFWInitiate.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
GLFWprogram::GLFWprogram(
    unsigned int width, unsigned int height, Camera &cam) : window_width(width), window_height(height), currentX(width / 2), currentY(height / 2), camera(cam) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(window_width, window_height, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "ERROR::GLFW : Failed to create GLFW window" << std::endl;
        glfwTerminate();
        std::exit(-1);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "ERROR::GLAD : Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        std::exit(-1);
    };
    if (mouseEnabled)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(window, this);
    glfwSetScrollCallback(window, [](GLFWwindow *window, double x, double y) {
        GLFWprogram *program = static_cast<GLFWprogram *>(glfwGetWindowUserPointer(window));
        program->handleScroll(x, y);
    });
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
};
GLFWprogram::~GLFWprogram() {
    glfwSetWindowShouldClose(window, true);
    glfwTerminate();
};
void GLFWprogram::setNewTime() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}
void GLFWprogram::closeProgram() {
    glfwTerminate();
};
void GLFWprogram::setCamera(Camera &cam) {
    camera = cam;
};
void GLFWprogram::toggleCamera() {
    mouseEnabled = !mouseEnabled;
    if (mouseEnabled) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetCursorPos(window, currentX, currentY);
    }
}
void GLFWprogram::processInput() {
    handleKeyboardInput();
    if (mouseEnabled)
        handleMouseInput();
    // handleScroll();
}
void GLFWprogram::handleKeyboardInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        camIsLight = !camIsLight;
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
        toggleCamera();
}
void GLFWprogram::handleMouseInput() {
    glfwGetCursorPos(window, &currentX, &currentY);
    if (firstMouse) {
        lastX = currentX;
        lastY = currentY;
        firstMouse = false;
    }
    float xoffset = currentX - lastX;
    float yoffset = lastY - currentY;
    lastX = currentX;
    lastY = currentY;
    camera.ProcessMouseMovement(xoffset, yoffset);
}
void GLFWprogram::handleScroll(double xoffset, double yoffset) {
    if (mouseEnabled)
        camera.ProcessMouseScroll(yoffset);
}
void GLFWprogram::endLoop() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}