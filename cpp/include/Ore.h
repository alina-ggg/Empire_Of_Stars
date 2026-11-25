// руда
#ifndef ORE_H
#define ORE_H

#include "Resource.h"

class Ore : public Resource {
public:
    Ore(int amount = 0);
    std::string getName() const override;
    Resource* clone() const override;
};

#endif