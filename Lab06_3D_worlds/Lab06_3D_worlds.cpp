#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/maths.hpp>
#include <common/camera.hpp>

// Function prototypes
void keyboardInput(GLFWwindow *window);

// Create camera object
Camera camera(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -2.0f));
//Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f));

// Object struct
struct Object
{
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 scale    = glm::vec3(1.0f, 1.0f, 1.0f);
    float angle = 0.0f;
    std::string name;
};

int main( void )
{
    // =========================================================================
    // Window creation - you shouldn't need to change this code
    // -------------------------------------------------------------------------
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    GLFWwindow* window;
    window = glfwCreateWindow(1024, 768, "Lab06 3D Worlds", NULL, NULL);
    
    if( window == NULL ){
        fprintf(stderr, "Failed to open GLFW window.\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    // -------------------------------------------------------------------------
    // End of window creation
    // =========================================================================
    
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    
    // Ensure we can capture keyboard inputs
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // Define cube object
    // Define vertices
    const float vertices[] = {
        // front
        -1.0f, -1.0f,  1.0f,    //              + ------ +
         1.0f, -1.0f,  1.0f,    //             /|       /|
         1.0f,  1.0f,  1.0f,    //   y        / |      / |
        -1.0f, -1.0f,  1.0f,    //   |       + ------ +  |
         1.0f,  1.0f,  1.0f,    //   + - x   |  + ----|- +
        -1.0f,  1.0f,  1.0f,    //  /        | /      | /
        // right                // z         |/       |/
         1.0f, -1.0f,  1.0f,    //           + ------ +
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
        // back
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        // left
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        // bottom
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        // top
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
    };

    // Define texture coordinates
    const float uv[] = {
        // front
        0.0f, 0.0f,     // vertex co-ordinates are the same for each side
        1.0f, 0.0f,     // of the cube so repeat every six vertices
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // right
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // back
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // left
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // bottom
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // top
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
    };

    // Define indices
    unsigned int indices[] = {
        0,   1,  2,  3,  4,  5,     // front
        6,   7,  8,  9, 10, 11,     // right
        12, 13, 14, 15, 16, 17,     // back
        18, 19, 20, 21, 22, 23,     // left
        24, 25, 26, 27, 28, 29,     // bottom
        30, 31, 32, 33, 34, 35      // top
    };
    
    // Create the Vertex Array Object (VAO)
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    // Create Vertex Buffer Object (VBO)
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Create texture buffer
    unsigned int uvBuffer;
    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);
    
    // Create Element Buffer Object (EBO)
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);
    
    // Compile shader program
    unsigned int shaderID;
    shaderID = LoadShaders("vertexShader.glsl", "fragmentShader.glsl");
    
    // Load the textures
    unsigned int texture;
    texture = loadTexture("../assets/crate.jpg");
    
    // Send the texture uniforms to the fragment shader
    glUseProgram(shaderID);
    unsigned int textureID;
    textureID = glGetUniformLocation(shaderID, "texture");
    glUniform1i(textureID, 0);
    
    // Cube positions
    glm::vec3 positions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -10.0f),
        glm::vec3(-3.0f, -2.0f, -3.0f),
        glm::vec3(-4.0f, -2.0f, -8.0f),
        glm::vec3( 2.0f,  2.0f, -6.0f),
        glm::vec3(-4.0f,  3.0f, -8.0f),
        glm::vec3( 0.0f, -2.0f, -5.0f),
        glm::vec3( 4.0f,  2.0f, -4.0f),
        glm::vec3( 2.0f,  0.0f, -2.0f),
        glm::vec3(-1.0f,  1.0f, -2.0f)
    };

    // Add cubes to objects vector
    std::vector<Object> objects;
    Object object;
    object.name = "cube";
    for (unsigned int i = 0 ; i < 10 ; i++)
    {
        object.position = positions[i];
        object.rotation = glm::vec3(1.0f, 1.0f, 1.0f);
        object.scale    = glm::vec3(0.5f, 0.5f, 0.5f);
        object.angle    = Maths::radians(20.0f * i);
        objects.push_back(object);
    }
    
    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Get inputs
        keyboardInput(window);
        
        // Clear the window
        glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Send the VBO to the GPU
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
        // Send the UV buffer to the GPU
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
//        // Calculate the model matrix
//        float angle         = Maths::radians(glfwGetTime() * 360.0f / 3.0f);
//        glm::mat4 translate = Maths::translate(glm::vec3(0.0f, 0.0f, -2.0f));
//        glm::mat4 scale     = Maths::scale(glm::vec3(0.5f, 0.5f, 0.5f));
//        glm::mat4 rotate    = Maths::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f));
//        glm::mat4 model     = translate * rotate * scale;

//        // Calculate the view matrix
//        glm::vec3 eye     = glm::vec3(1.0f, 1.0f, 0.0f);
//        glm::vec3 target  = glm::vec3(0.0f, 0.0f, -2.0f);
//        glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
//        glm::vec3 front   = glm::normalize(target - eye);
//        glm::vec3 right   = glm::normalize(glm::cross(front, worldUp));
//        glm::vec3 up      = glm::cross(right, front);
//        
//        glm::mat4 view;
//        view[0][0] = right.x, view[0][1] = up.x, view[0][2] = -front.x;
//        view[1][0] = right.y, view[1][1] = up.y, view[1][2] = -front.y;
//        view[2][0] = right.z, view[2][1] = up.z, view[2][2] = -front.z;
//        view[3][0] = -glm::dot(eye, right);
//        view[3][1] = -glm::dot(eye, up);
//        view[3][2] =  glm::dot(eye, front);
        
//        // Calculate orthographic projection matrix
//        float left   = -2.0f, right_ = 2.0f;
//        float bottom = -2.0f, top    = 2.0f;
//        float near   =  0.0f, far    = 10.0f;
//        
//        glm::mat4 projection;
//        projection[0][0] = 2.0f / (right_ - left);
//        projection[1][1] = 2.0f / (top - bottom);
//        projection[2][2] = 2.0f / (near - far);
//        projection[3][0] = -(right_ + left) / (right_ - left);
//        projection[3][1] = -(top + bottom) / (top - bottom);
//        projection[3][2] =  (near + far) / (near - far);
        
//        // Calculate perspective projection matrix
//        float fov    = Maths::radians(45.0f);
//        float aspect = 1024.0f / 768.0f;
//        float near   = 0.2f;
//        float far    = 100.0f;
//        float top    = near * tan(fov / 2.0f);
//        float right_ = aspect * top;
//        
//        glm::mat4 projection;
//        projection[0][0] = near / right_;
//        projection[1][1] = near / top;
//        projection[2][2] = -(far + near) / (far - near);
//        projection[2][3] = -1.0f;
//        projection[3][2] = -2.0f * far * near / (far - near);
        
        // Calculate view and projection matrices
        camera.eye    = glm::vec3(0.0f, 0.0f, 5.0f);
        camera.target = objects[0].position;
        camera.calculateMatrices();
        
        // Calculate the MVP matrix and send it to the vertex shader
//        glm::mat4 mvp = projection * view * model;
//        glm::mat4 mvp = camera.projection * camera.view * model;
//        unsigned int mvpID = glGetUniformLocation(shaderID, "mvp");
//        glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);
//        
//        // Draw the triangles
//        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int),
//                       GL_UNSIGNED_INT, 0);
        
        
//        // Exercise 1 - orbit the camera
//        float angle = Maths::radians(glfwGetTime() * 360.0f / 5.0f);
//        camera.eye = glm::vec3(10 * cos(angle), 0.0f, 10 * sin(angle));
//        camera.target = positions[0];
//        camera.calculateMatrices();
        
        // Loop through objects and draw each one
        for (int i = 0; i < static_cast<unsigned int>(objects.size()); i++)
        {
            // Calculate the model matrix
            glm::mat4 translate = Maths::translate(objects[i].position);
            glm::mat4 scale     = Maths::scale(objects[i].scale);
            glm::mat4 rotate    = Maths::rotate(objects[i].angle, objects[i].rotation);
            
//            // Exericse 2
//            if (i % 2 == 1)
//            {
//                float angle = Maths::radians(glfwGetTime() * 360.0f / 2.0f);
//                rotate = Maths::rotate(angle, glm::vec3(1.0f, 1.0f, 1.0f));
//            }
            
            glm::mat4 model     = translate * rotate * scale;

            // Calculate the MVP matrix
            glm::mat4 mvp = camera.projection * camera.view * model;

            // Send MVP matrix to the vertex shader
            unsigned int mvpID = glGetUniformLocation(shaderID, "mvp");
            glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

            // Draw the triangles
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        }
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &uvBuffer);
    glDeleteProgram(shaderID);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    return 0;
}

void keyboardInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    // Exercise 4 - change fov angle using arrow keys
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.fov -= 0.01f;
    
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.fov += 0.01f;
    
    if (camera.fov < Maths::radians(10.0f))
        camera.fov = Maths::radians(10.0f);
    
    if (camera.fov > Maths::radians(90.0f))
        camera.fov = Maths::radians(90.0f);
}
