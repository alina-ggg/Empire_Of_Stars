// торговля
#ifndef TECHTRADER_H
#define TECHTRADER_H

#include "Corporation.h"

class TechTrader : public Corporation {
private:
    double priceBonus; 

public:
    TechTrader(int level = 1);
    
    std::string getName() const override;
    void applyEffect(Empire* empire, Galaxy* galaxy) override;
    
    bool sellResource(Empire* empire, const std::string& resourceName, int amount);
    bool buyResource(Empire* empire, const std::string& resourceName, int amount);
};

#endif