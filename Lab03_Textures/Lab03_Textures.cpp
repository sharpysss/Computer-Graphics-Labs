#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <common/shader.hpp>
#include <common/texture.hpp>

// Function prototypes
void keyboardInput(GLFWwindow *window);

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
    window = glfwCreateWindow(1024, 768, "Lab03 Textures", NULL, NULL);
    
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
    
	// Ensure we can capture keyboard inputs
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
//    // Define vertex positions
//    static const float vertices[] = {
//        // x     y     z
//        -0.5f, -0.5f, 0.0f, // triangle 1
//         0.5f, -0.5f, 0.0f,
//         0.5f,  0.5f, 0.0f,
//        -0.5f, -0.5f, 0.0f, // triangle 2
//         0.5f,  0.5f, 0.0f,
//        -0.5f,  0.5f, 0.0f
//    };
    
    // Define vertex positions
    static const float vertices[] = {
        // x     y     z      index
        -0.5f, -0.5f, 0.0f,  // 0
         0.5f, -0.5f, 0.0f,  // 1
         0.5f,  0.5f, 0.0f,  // 2
        -0.5f,  0.5f, 0.0f   // 3
    };

    // Define texture co-ordinates
    static const float uv[] = {
        // u    v      index
        0.0f,  0.0f,  // 0
        1.0f,  0.0f,  // 1
        1.0f,  1.0f,  // 2
        0.0f,  1.0f,  // 3
    };
    
//    // Exercise 1 -- 6x4 grid of Marios
//    // Define texture co-ordinates
//    static const float uv[] = {
//        // u    v      index
//        0.0f,  0.0f,  // 0
//        6.0f,  0.0f,  // 1
//        6.0f,  4.0f,  // 2
//        0.0f,  4.0f,  // 3
//    };
    
//    // Exercise 4 -- Mario's eye
//    // Define texture co-ordinates
//    static const float uv[] = {
//        // u    v      index
//        0.39f,  0.35f,  // 0
//        0.56f,  0.35f,  // 1
//        0.56f,  0.56f,  // 2
//        0.39f,  0.56f,  // 3
//    };
    
    
    // Define indices
    static const unsigned int indices[] = {
        0, 1, 2,  // lower right triangle
        0, 2, 3   // upper left triangle
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
    
//    // Create a texture
//    unsigned int texture;
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//    
//    // Load texture image from file
//    const char *path = "../assets/mario.png";
//    int width, height, nChannels;
//    stbi_set_flip_vertically_on_load(true);
//    unsigned char *data = stbi_load(path, &width, &height, &nChannels, 0);
//
//    // Specify 2D texture
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
//                 GL_UNSIGNED_BYTE, data);
//    glGenerateMipmap(GL_TEXTURE_2D);
//    
//    // Free the image from the memory
//    stbi_image_free(data);
//    
//    // Set texture wrapping options
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
//                    GL_LINEAR_MIPMAP_LINEAR);
    
    // Load the textures
    unsigned int texture1, texture2, texture3;
    texture1 = loadTexture("../assets/crate.jpg");
    texture2 = loadTexture("../assets/mario.png");
    texture3 = loadTexture("../assets/kratos.png");
    
    // Send the texture uniforms to the fragment shader
    glUseProgram(shaderID);
    unsigned int texture1ID, texture2ID, texture3ID;
    texture1ID = glGetUniformLocation(shaderID, "texture1");
    texture2ID = glGetUniformLocation(shaderID, "texture2");
    texture3ID = glGetUniformLocation(shaderID, "texture3");
    glUniform1i(texture1ID, 0);
    glUniform1i(texture2ID, 1);
    glUniform1i(texture3ID, 2);
    
    // Bind the textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, texture3);
    
    // Render loop
	while (!glfwWindowShouldClose(window))
    {
        // Get inputs
        keyboardInput(window);
        
        // Clear the window
        glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Send the VBO to the GPU
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
        // Send the UV buffer to the GPU
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
        // Draw the triangle
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), 
                       GL_UNSIGNED_INT, 0);
        
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
}
