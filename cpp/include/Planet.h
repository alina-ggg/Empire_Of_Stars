// планета
#ifndef PLANET_H
#define PLANET_H

#include "CelestialBody.h"
#include <vector>

class Corporation;

class Planet : public CelestialBody {
private:
    std::vector<Corporation*> corporations;
    int goldReserve;

public:
    Planet(int id, const std::string& name, double x, double y, int goldReserve = 100);
    ~Planet();

    std::string getType() const override;
    bool canBuildCorporation() const override;

    bool buildCorporation(Corporation* corporation);
    std::vector<Corporation*> getCorporations() const;
    int getGoldReserve() const;
    void addGold(int amount);
};

#endif 