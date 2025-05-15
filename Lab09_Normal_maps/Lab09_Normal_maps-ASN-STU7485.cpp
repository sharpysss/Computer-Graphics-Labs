#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/maths.hpp>
#include <common/camera.hpp>
#include <common/model.hpp>
#include <common/light.hpp>


void keyboardInput(GLFWwindow *window);
void mouseInput(GLFWwindow *window);

float previousTime = 0.0f;  
float deltaTime    = 0.0f;  


Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f));


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

    GLFWwindow* window;
    window = glfwCreateWindow(1024, 768, "Lab09 Normal Maps", NULL, NULL);
    
    if( window == NULL ){
        fprintf(stderr, "Failed to open GLFW window.\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

  
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    

    glEnable(GL_DEPTH_TEST);
    
    
    glEnable(GL_CULL_FACE);
    
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
  
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwPollEvents();
    glfwSetCursorPos(window, 1024 / 2, 768 / 2);

    unsigned int shaderID, lightShaderID;
    shaderID      = LoadShaders("vertexShader.glsl", "fragmentShader.glsl");
    lightShaderID = LoadShaders("lightVertexShader.glsl", "lightFragmentShader.glsl");
    
  
    glUseProgram(shaderID);
    
 
    Model basketball("../assets/basketball.obj");
    Model sphere("../assets/sphere.obj");


    

    basketball.ka = 0.2f;
    basketball.kd = 0.7f;
    basketball.ks = 1.0f;
    basketball.Ns = 20.0f;
    
 
    Light lightSources;
    lightSources.addPointLight(glm::vec3(2.0f, 2.0f, 2.0f),         
                               glm::vec3(1.0f, 1.0f, 1.0f),       
                               1.0f, 0.1f, 0.02f);                  
    
    lightSources.addPointLight(glm::vec3(1.0f, 1.0f, -8.0f),       
                               glm::vec3(1.0f, 1.0f, 1.0f),         
                               1.0f, 0.1f, 0.02f);                  
    
    lightSources.addSpotLight(glm::vec3(0.0f, 3.0f, 0.0f),         
                              glm::vec3(0.0f, -1.0f, 0.0f),      
                              glm::vec3(1.0f, 1.0f, 1.0f),         
                              1.0f, 0.1f, 0.02f,                    
                              std::cos(Maths::radians(45.0f)));     
    
    lightSources.addDirectionalLight(glm::vec3(1.0f, -1.0f, 0.0f), 
                                     glm::vec3(1.0f, 1.0f, 0.0f));  

    

    glm::vec3 basketballPositions[] = {
        glm::vec3(-3.0f, 1.0f, -2.0f),
        glm::vec3(-2.0f, 1.0f, -5.0f),
        glm::vec3(-3.0f, 1.0f, -6.0f),
        
      
    };

    std::vector<Object> objects;
    Object object;
    object.name = "basketball";
    for (unsigned int i = 0 ; i < 10 ; i++)
    {
        object.position = basketballPositions[i];
        object.rotation = glm::vec3(1.0f, 1.0f, 1.0f);
        object.scale    = glm::vec3(0.75f, 0.75f, 0.75f);
        object.angle    = Maths::radians(20.0f * i);
        objects.push_back(object);
    }

  
   
    Model wall("../assets/objfence.obj");
    wall.addTexture("../assets/Fence007A_2K-PNG_Displacement.png", "specular");
    wall.addTexture("../assets/Fence_color.png", "specular");
    wall.ka = 1.2f;
    wall.kd = 1.0f;
    wall.ks = 1.0f;
    wall.Ns = 20.0f;

    object.position = glm::vec3(-2.0f,0.5f, -5.0f);
    object.scale = glm::vec3(2.0f, 1.0f, 2.0f);
    object.rotation = glm::vec3(90.0f, 1.0f, 90.0f);
    object.angle = 0.0f;
    object.name = "wall";
    objects.push_back(object);

    while (!glfwWindowShouldClose(window))
    {
    
        float time   = glfwGetTime();
        deltaTime    = time - previousTime;
        previousTime = time;
     
        keyboardInput(window);
        mouseInput(window);
        
     
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        camera.target = camera.eye + camera.front;
        camera.calculateMatrices();
        
        
        glUseProgram(shaderID);
        
       
        lightSources.toShader(shaderID, camera.view);
      
        for (unsigned int i = 0; i < static_cast<unsigned int>(objects.size()); i++)
        {
            glm::mat4 translate = Maths::translate(objects[i].position);
            glm::mat4 scale     = Maths::scale(objects[i].scale);
            glm::mat4 rotate    = Maths::rotate(objects[i].angle, objects[i].rotation);
            glm::mat4 model     = translate * rotate * scale;
            
          
            glm::mat4 MV  = camera.view * model;
            glm::mat4 MVP = camera.projection * MV;
            glUniformMatrix4fv(glGetUniformLocation(shaderID, "MVP"), 1, GL_FALSE, &MVP[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(shaderID, "MV"), 1, GL_FALSE, &MV[0][0]);
  
            if (objects[i].name == "basketball")
                basketball.draw(shaderID);
            

            if (objects[i].name == "wall")
                wall.draw(shaderID);
        }
        
  
        lightSources.draw(lightShaderID, camera.view, camera.projection, sphere);
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    
    basketball.deleteBuffers();
    glDeleteProgram(shaderID);
    
  
    glfwTerminate();
    return 0;
}

void keyboardInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.eye += 5.0f * deltaTime * camera.front;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.eye -= 5.0f * deltaTime * camera.front;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.eye -= 5.0f * deltaTime * camera.right;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.eye += 5.0f * deltaTime * camera.right;
}

void mouseInput(GLFWwindow *window)
{
   
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    glfwSetCursorPos(window, 1024 / 2, 768 / 2);
 
    camera.yaw   += 0.005f * float(xPos - 1024 / 2);
    camera.pitch += 0.005f * float(768 / 2 - yPos);
    
  
    camera.calculateCameraVectors();
}

