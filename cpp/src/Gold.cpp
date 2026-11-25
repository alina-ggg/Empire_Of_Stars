// при добыче сразу идет в казну
#include "Gold.h"

Gold::Gold(int amount)
    : Resource(amount, 1.0) {}  // золото = 1 у.е. за единицу

std::string Gold::getName() const {
    return "Gold";
}

Resource* Gold::clone() const {
    return new Gold(amount);
}