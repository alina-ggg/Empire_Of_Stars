#include "Ore.h"

Ore::Ore(int amount)
    : Resource(amount, 3.0) {}

std::string Ore::getName() const {
    return "Ore";
}

Resource* Ore::clone() const {
    return new Ore(amount);
}