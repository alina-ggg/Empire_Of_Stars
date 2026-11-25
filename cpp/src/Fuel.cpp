#include "Fuel.h"

Fuel::Fuel(int amount)
    : Resource(amount, 2.0) {} 

std::string Fuel::getName() const {
    return "Fuel";
}

Resource* Fuel::clone() const {
    return new Fuel(amount);
}