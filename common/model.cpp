#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "model.hpp"
#include "stb_image.hpp"

Model::Model(const char *path)
{

    bool res = loadObj(path, vertices, uvs, normals);
  
    calculateTangents();

    setupBuffers();
}

void Model::draw(unsigned int &shaderID)
{
    glUniform1f(glGetUniformLocation(shaderID, "ka"), ka);
    glUniform1f(glGetUniformLocation(shaderID, "kd"), kd);
    glUniform1f(glGetUniformLocation(shaderID, "ks"), ks);
    glUniform1f(glGetUniformLocation(shaderID, "Ns"), Ns);
    
  
    unsigned int diffuseNum = 0;
    unsigned int normalNum = 0;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
     
        std::string name = textures[i].type;
        glActiveTexture(GL_TEXTURE0 + i);
        glUniform1i(glGetUniformLocation(shaderID, (name + "Map").c_str()), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<unsigned int>(vertices.size()));
    glBindVertexArray(0);
}

void Model::setupBuffers()
{
  
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    

    unsigned int vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    unsigned int uvBuffer;
    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

    unsigned int normalBuffer;
    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
    
    
    GLuint tangentBuffer;
    glGenBuffers(1, &tangentBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, tangentBuffer);
    glBufferData(GL_ARRAY_BUFFER, tangents.size() * sizeof(glm::vec3), &tangents[0], GL_STATIC_DRAW);

    
    GLuint bitangentBuffer;
    glGenBuffers(1, &bitangentBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, bitangentBuffer);
    glBufferData(GL_ARRAY_BUFFER, bitangents.size() * sizeof(glm::vec3), &bitangents[0], GL_STATIC_DRAW);


    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, tangentBuffer);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(4);
    glBindBuffer(GL_ARRAY_BUFFER, bitangentBuffer);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
  
    glBindVertexArray(0);
}

void Model::deleteBuffers()
{
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &uvBuffer);
    glDeleteBuffers(1, &normalBuffer);
    glDeleteVertexArrays(1, &VAO);
}
void Model::calculateTangents()
{
    for (unsigned int i = 0; i < vertices.size(); i += 3)
    {
   
        glm::vec3 E1 = vertices[i + 1] - vertices[i];
        glm::vec3 E2 = vertices[i + 2] - vertices[i + 1];
        float deltaU1 = uvs[i + 1].x - uvs[i].x;
        float deltaV1 = uvs[i + 1].y - uvs[i].y;
        float deltaU2 = uvs[i + 2].x - uvs[i + 1].x;
        float deltaV2 = uvs[i + 2].y - uvs[i + 1].y;

       
        float denom = 1.0f / (deltaU1 * deltaV2 - deltaU2 * deltaV1);
        glm::vec3 tangent = (deltaV2 * E1 - deltaV1 * E2) * denom;
        glm::vec3 bitangent = (deltaU1 * E2 - deltaU2 * E1) * denom;

       
        tangents.push_back(tangent);
        tangents.push_back(tangent);
        tangents.push_back(tangent);
        bitangents.push_back(bitangent);
        bitangents.push_back(bitangent);
        bitangents.push_back(bitangent);
    }
}

bool Model::loadObj(const char *path,
                    std::vector<glm::vec3> &outVertices,
                    std::vector<glm::vec2> &outUVs,
                    std::vector<glm::vec3> &outNormals)
{
    
    printf("Loading file %s\n", path);
    
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> tempVertices;
    std::vector<glm::vec2> tempUVs;
    std::vector<glm::vec3> tempNormals;
    
    FILE *file = fopen(path, "r");
    if (file==NULL)
    {
        printf("Impossible to open the file. Check paths and directories.");
        getchar();
        return false;
    }
    
    while (true)
    {
       
        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
        {
         
            break;
        }
        
        if (strcmp(lineHeader, "v") == 0)
        {
        
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            tempVertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt") == 0)
        {
           
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            tempUVs.push_back(uv);
        }
        else if (strcmp(lineHeader, "vn") == 0)
        {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            tempNormals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0)
        {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                                 &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                 &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                                 &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            
            if (matches != 9)
            {
                printf("File can't be read by loadObj().\n");
                fclose(file);
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices    .push_back(uvIndex[0]);
            uvIndices    .push_back(uvIndex[1]);
            uvIndices    .push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
        else
        {
            char commentBuffer[1000];
            fgets(commentBuffer, 1000, file);
        }
    }
    
    for (unsigned int i = 0; i < vertexIndices.size(); i++)
    {
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];
        
        glm::vec3 vertex = tempVertices[vertexIndex - 1];
        glm::vec2 uv = tempUVs[uvIndex - 1];
        glm::vec3 normal = tempNormals[normalIndex - 1];
        
        outVertices.push_back(vertex);
        outUVs.push_back(uv);
        outNormals.push_back(normal);
    }
    
    fclose(file);
    
    return true;
}

void Model::addTexture(const char *path, const std::string type)
{
    Texture texture;
    texture.id = loadTexture(path);
    texture.type = type;
    textures.push_back(texture);
}

unsigned int Model::loadTexture(const char *path)
{

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, numComponents;
    unsigned char *data = stbi_load(path, &width, &height, &numComponents, 0);
    if (data)
    {
        GLenum format;
        if (numComponents == 1)
            format = GL_RED;
        else if (numComponents == 3)
            format = GL_RGB;
        else if (numComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture " << path << " failed to load." << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
