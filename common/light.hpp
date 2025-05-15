#pragma once

#include <external/glm-0.9.7.1/glm/gtc/matrix_transform.hpp>
#include <common/model.hpp>

struct LightSource
{
    glm::vec3 position;
    glm::vec3 colour;
    glm::vec3 direction;
    float constant;
    float linear;
    float quadratic;
    float cosPhi;
    unsigned int type;
};

class Light
{
public:
    std::vector<LightSource> lightSources;
    unsigned int lightShaderID;
    
   
    void addPointLight      (const glm::vec3 position,  const glm::vec3 colour,
                             const float constant,      const float linear,
                             const float quadratic);
    void addSpotLight       (const glm::vec3 position,  const glm::vec3 direction,
                             const glm::vec3 colour,    const float constant,
                             const float linear,        const float quadratic,
                             const float cosPhi);
    void addDirectionalLight(const glm::vec3 direction, const glm::vec3 colour);
    
  
    void toShader(unsigned int shaderID, glm::mat4 view);
    

    void draw(unsigned int shaderID, glm::mat4 view, glm::mat4 projection, Model lightModel);
};
