// кристаллы
#ifndef CRYSTAL_H
#define CRYSTAL_H

#include "Resource.h"

class Crystal : public Resource {
public:
    Crystal(int amount = 0);
    std::string getName() const override;
    Resource* clone() const override;
};

#endif