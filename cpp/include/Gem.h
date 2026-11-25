// драгоценные камни
#ifndef GEM_H
#define GEM_H

#include "Resource.h"

class Gem : public Resource {
public:
    Gem(int amount = 0);
    std::string getName() const override;
    Resource* clone() const override;
};

#endif 