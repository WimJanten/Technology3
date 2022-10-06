#include "Car.h"
#include "Wheel.h"

#include <iostream>
#include <stdexcept>

#ifdef SHOW_CTORS
    #define TRACE(txt) std::cout << txt << std::endl
#else
    #define TRACE(txt)
#endif


Car::Car(const std::string& model, const std::string& material, int diameter,
         int nrWheels) : model(model)
{
    if(nrWheels <= 2){
        throw std::invalid_argument("nr wheels must be greater than 2");
    }
    if(diameter <= 0){
        throw std::invalid_argument("diameter must be greater than 0");
    }
    for(int i = 0; i < nrWheels; i++)
    {
        wheels.push_back(new Wheel(diameter, material));
    }
    TRACE("car constructor called!");
}

Car::Car(const Car& other)
{
    for (auto wheel : other.wheels)
    {
        wheels.push_back(new Wheel(wheel->GetDiameter(), wheel->GetMaterial()));
    }
    SetLicencePlate(other.GetLicencePlate());
    model = other.GetModel();
}

Car& Car::operator=(const Car& other){
    if (this != &other)
    {
        for (auto wheel : wheels)
        {
            delete wheel;
            wheel = nullptr;
        }
        wheels.clear();
        for (auto wheel : other.wheels)
        {
            wheels.push_back(new Wheel(wheel->GetDiameter(), wheel->GetMaterial()));
        }
    }
    return *this;
}

Car::~Car()
{
    for (auto wheel : wheels)
    {
        delete wheel;
        wheel = nullptr;
    }
    TRACE("car destructor called!");
}

const Wheel* Car::GetWheel(int index) const
/* pre : 0 <= index < nr wheels in <Car>
   post: getWheel(i) = Wheel nr index of <Car>
*/
{
    if (index >= 0 && index < GetNrWheels())
        return wheels[index];
    else {
        throw std::invalid_argument("index out of range");
    }
    return NULL;
}

void Car::RemoveWheel(int index){
    if (index >= 0 && index < GetNrWheels())
    {
        delete wheels[index];
        wheels.erase(wheels.begin() + index);
        wheels[index] = nullptr;
    }
    else {
        throw std::invalid_argument("index out of range");
    }
}



int Car::GetNrWheels() const{
    return wheels.size();
}

std::string Car::GetModel() const{
    return model;
}

void Car::SetLicencePlate(const std::string& licence){
    licencePlate = licence;
}

std::string Car::GetLicencePlate() const{
    return licencePlate;
}

void Car::AddWheel(int diameter, const std::string& material){
    wheels.push_back(new Wheel(diameter, material));
}


// /////////////////////////////////////////////////////////////////////////////
// TODO: implement all other methods