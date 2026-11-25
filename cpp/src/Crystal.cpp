#include "Crystal.h"

Crystal::Crystal(int amount)
    : Resource(amount, 5.0) {} 

std::string Crystal::getName() const {
    return "Crystal";
}

Resource* Crystal::clone() const {
    return new Crystal(amount);
}