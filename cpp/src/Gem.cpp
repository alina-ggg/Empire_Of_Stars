#include "Gem.h"

Gem::Gem(int amount)
    : Resource(amount, 10.0) {} 

std::string Gem::getName() const {
    return "Gem";
}

Resource* Gem::clone() const {
    return new Gem(amount);
}