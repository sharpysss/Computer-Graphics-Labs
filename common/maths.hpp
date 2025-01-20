#pragma once

#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/io.hpp>

// Maths class
class Maths
{
public:
    
    // Transformation matrices
    static float     radians(float angle);
    static glm::mat4 scale(const glm::vec3 &v);
    static glm::mat4 translate(const glm::vec3 &v);
    static glm::mat4 rotate(const float &angle, glm::vec3 v);
    
    // View and projection matrices
    static glm::mat4 lookAt(glm::vec3 eye, glm::vec3 target, glm::vec3 worldUp);
    static glm::mat4 orthographic(const float left,   const float right,
                                  const float bottom, const float top,
                                  const float near,   const float far);
    static glm::mat4 perspective( const float fov,  const float aspect,
                                  const float near, const float far);
};

// Quaternion class
class Quaternion
{
public:
    float w, x, y, z;
    
    // Constructors
    Quaternion();
    Quaternion(const float w, const float x, const float y, const float z);
    
    // Methods
    glm::mat4 matrix();
    void eulerToQuat(const float yaw, const float pitch, const float roll);
};
