// топливо
#ifndef FUEL_H
#define FUEL_H

#include "Resource.h"

class Fuel : public Resource {
public:
    Fuel(int amount = 0);
    std::string getName() const override;
    Resource* clone() const override;
};

#endif