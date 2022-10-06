#include "Wheel.h"

#include <stdexcept>

Wheel::Wheel(int diameter, const std::string& material) : material(material){
    if(diameter <= 0){
        throw std::invalid_argument("Diameter must be greater than 0");
    }
    this->diameter = diameter;
}

std::string Wheel::GetMaterial() const{
    return this->material;
}

void Wheel::SetMaterial(const std::string& material){
    this->material = material;
}

int Wheel::GetDiameter() const{
    return this->diameter;
}
