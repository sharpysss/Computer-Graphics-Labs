#include <common/camera.hpp>

Camera::Camera(const glm::vec3 Eye, const glm::vec3 Target)
{
    eye    = Eye;
    target = Target;
}

void Camera::calculateMatrices()
{
    // Calculate the view matrix
//    view = Maths::lookAt(eye, target, worldUp);
    
    direction.eulerToQuat(pitch, yaw, roll);
    view = direction.matrix() * Maths::translate(-eye);

    // Calculate the projection matrix
    projection = Maths::perspective(fov, aspect, near, far);
}

void Camera::calculateCameraVectors()
{
    front = glm::vec3(cos(yaw) * cos(pitch), sin(pitch), sin(yaw) * cos(pitch));
    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, worldUp));
    up    = glm::cross(right, front);
}
