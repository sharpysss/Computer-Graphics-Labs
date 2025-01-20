#include "Car.hpp"

void Car::outputDetails()
{
    std::cout << "\nMake: " << make
              << "\nModel: " << model
              << "\nYear: " << year << std::endl;
}

void Car::accelerate(const float increment)
{
    speed = +increment;
    std::cout << "\nThe car has accelerated to " << speed << " mph." << std::endl;
}

Car::Car()
{
    std::cout << "\nCar object created" << std::endl;
}

Car::Car(const std::string makeInput, const std::string modelInput, const int yearInput)
{
    make = makeInput;
    model = modelInput;
    year = yearInput;
    std::cout << "\nCar object created" << std::endl;
}

float Car::mph2kph(const float speed)
{
    return speed * 1.60934f;
}
