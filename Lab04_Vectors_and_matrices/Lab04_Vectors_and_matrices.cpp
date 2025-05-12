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
    b[0] = 1.0f, b[1] = 2.0f, b[2] = 3.0f;

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
    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a - b = " << a - b << std::endl;

    std::cout << "2a    = " << 2.0f * a << std::endl;
    std::cout << "b / 3 = " << b / 3.0f << std::endl;

    std::cout << "a * b = " << a * b << std::endl;

    return 0;
}
