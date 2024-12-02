#pragma once

#include "camera.h"
#include "myUtils.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class GLFWprogram {
private:
    bool firstMouse = true;
    Camera &camera;
	bool mouseEnabled=true;

public:
    GLFWwindow *window;
    unsigned int window_width, window_height;
    float lastX, lastY;
    double currentX, currentY;
    float deltaTime = 0.0f, lastFrame = 0.0f;

    bool camIsLight = false;

    GLFWprogram(unsigned int width, unsigned int height, Camera &cam);
    ~GLFWprogram();
    void closeProgram();
    void setNewTime();
    void endLoop();
	void toggleCamera();
    void setCamera(Camera &cam);
    void processInput();
    void handleKeyboardInput();
    void handleMouseInput();
    void handleScroll(double xoffset, double yoffset);
};