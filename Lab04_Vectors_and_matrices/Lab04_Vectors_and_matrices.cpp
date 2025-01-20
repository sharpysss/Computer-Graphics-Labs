#include <iostream>

// Include the glm library
#include <glm/glm.hpp>
#include <glm/gtx/io.hpp>

int main() {

    // Vectors
    printf("Vectors and Matrices\n");
    printf("--------------------------------------------------\n");

    // Defining vectors
    glm::vec3 a, b;
    a = glm::vec3(3.0f, 0.0f, 4.0f);
    b[0] =  1.0f, b[1] = 2.0f, b[2] = 3.0f;
    
    printf("Defining vectors:\n");
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    
    // Vector length
    printf("\nVector length:\n");
    printf("length(a) = %0.3f\n", glm::length(a));
    printf("length(b) = %0.3f\n", glm::length(b));
    
    // Normalising vectors
    glm::vec3 aHat, bHat;
    aHat = glm::normalize(a);
    bHat = b / glm::length(b);
    
    printf("\nNormalising vectors:\n");
    std::cout << "aHat = " << aHat << std::endl;
    std::cout << "bHat = " << bHat << std::endl;
    printf("length(aHat) = %0.3f\n", glm::length(aHat));
    printf("length(bHat) = %0.3f\n", glm::length(bHat));
    
    // Arithmetic operations on vectors
    printf("\nArithmetic operations on vectors:\n");
    std::cout << "2a    = " << 2.0f * a << std::endl;
    std::cout << "b / 3 = " << b / 3.0f << std::endl;
    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a - b = " << a - b << std::endl;
    std::cout << "a * b = " << a * b << std::endl;
    
    // Dot and Cross products
    printf("\nDot and cross products:\n");
    printf("a . b = %0.3f\n", glm::dot(a, b));
    std::cout << "a x b = " << glm::cross(a, b) << std::endl;
    printf("a . (a x b) = %0.3f\n", glm::dot(a, glm::cross(a, b)));
    printf("b . (a x b) = %0.3f\n", glm::dot(b, glm::cross(a, b)));
    
    // Defining matrices
    glm::mat2 A, B;
    
    A[0][0] = 1.0f, A[0][1] = 2.0f;
    A[1][0] = 3.0f, A[1][1] = 4.0f;
    
    B = glm::mat2(5.0f, 6.0f, 7.0f, 8.0f);
    
    printf("\nDefining matrices:\n");
    std::cout << "A = " << glm::transpose(A) << "\n" << std::endl;
    std::cout << "B = " << glm::transpose(B) << std::endl;
    
    // Aritmetic operations on matrices
    printf("\nAritmetic operations on matrices:\n");
    std::cout << "A + B = " << glm::transpose(A + B) << "\n" << std::endl;
    std::cout << "A - B = " << glm::transpose(A - B) << "\n" << std::endl;
    std::cout << "2A    = " << glm::transpose(2.0f * A) << "\n" << std::endl;
    std::cout << "A / 3 = " << glm::transpose(A / 3.0f) << "\n" << std::endl;
    std::cout << "A * B = " << glm::transpose(B * A) << "\n" << std::endl;
    std::cout << "B * A = " << glm::transpose(A * B) << "\n" << std::endl;
    
    // The identity matrix
    printf("\nThe identity matrix:\n");
    glm::mat4 I;
    std::cout << "I = " << glm::transpose(I) << "\n" << std::endl;
    
    // Inverse matrices
    printf("\nInverse matrices:\n");
    glm::mat2 invA = glm::inverse(A);
    glm::mat2 invB = glm::inverse(B);
    std::cout << "invA = " << glm::transpose(invA) << "\n" << std::endl;
    std::cout << "invB = " << glm::transpose(invB) << "\n" << std::endl;
    std::cout << "invA * A = " << glm::transpose(A * invA) << "\n" << std::endl;
    std::cout << "invB * B = " << glm::transpose(B * invB) << "\n" << std::endl;
    
    return 0;
}
