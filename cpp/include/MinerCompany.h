// добыча
#ifndef MINERCOMPANY_H
#define MINERCOMPANY_H

#include "Corporation.h"

class MinerCompany : public Corporation {
private:
    double extractionRate; 

public:
    MinerCompany(int level = 1);
    
    std::string getName() const override;
    void applyEffect(Empire* empire, Galaxy* galaxy) override;
    
    void extractFromPlanet(int planetId, Galaxy* galaxy, Empire* empire);
    void extractFromAsteroid(int asteroidId, Galaxy* galaxy, Empire* empire);
};

#endif