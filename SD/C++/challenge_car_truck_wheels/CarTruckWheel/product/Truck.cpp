#include "Truck.h"
#include <iostream>

Truck::Truck(const std::string& model, const std::string& material, int diameter, int nrWheels, int power) : Car(model, material, diameter, nrWheels)
{
    this->power = new int(power);
}

Truck::~Truck()
{
    delete power;
    power = nullptr;
}

Truck::Truck(const Truck& other) : Car(other)
{
    power = new int(*other.power);
}

Truck& Truck::operator=(const Truck& other)
{
    if (this != &other)
    {
        Car::operator=(other);
        delete power;
        power = new int(*other.power);
    }
    return *this;
}

int Truck::GetPower() const
{
    return *power;
}
