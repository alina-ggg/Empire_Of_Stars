// золото
#ifndef GOLD_H
#define GOLD_H

#include "Resource.h"

class Gold : public Resource {
public:
    Gold(int amount = 0);
    std::string getName() const override;
    Resource* clone() const override;
};

#endif