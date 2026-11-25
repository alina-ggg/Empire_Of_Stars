// астероид
#ifndef ASTEROID_H
#define ASTEROID_H

#include "CelestialBody.h"

class Asteroid : public CelestialBody {
public:
    Asteroid(int id, const std::string& name, double x, double y);
    
    std::string getType() const override;
    bool canBuildCorporation() const override;
};

#endif