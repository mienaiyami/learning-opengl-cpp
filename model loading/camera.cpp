#include "camera.h"

Camera::Camera(
    glm::vec3 position,
    glm::vec3 up,
    float yaw,
    float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
};
Camera::Camera(
    float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
};
glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
};
glm::vec3 Camera::getTarget() {
    return Position + Front;
}
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    glm::vec3 realFront = glm::normalize(glm::cross(WorldUp,Right));
    if (direction == FORWARD)
        Position += realFront * velocity;
    if (direction == BACKWARD)
        Position -= realFront * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
    //Position.y = 0.0f;
    if (direction == UP)
        Position += glm::vec3(0.0, 1.0, 0.0) * velocity;
    if (direction == DOWN)
        Position -= glm::vec3(0.0, 1.0, 0.0) * velocity;
}
void Camera::ProcessMouseScroll(float yoffset) {
    Zoom -= yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 100.0f)
        Zoom = 100.0f;
}
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;
    Yaw += xoffset;
    Pitch += yoffset;
    if (constrainPitch) {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }
    updateCameraVectors();
}
void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front   = glm::normalize(front);
    Right   = glm::normalize(glm::cross(Front, WorldUp));
    Up      = glm::normalize(glm::cross(Right, Front));
}