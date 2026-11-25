// граф галактики
#ifndef GALAXY_H
#define GALAXY_H

#include <vector>
#include "CelestialBody.h"

// Forward declarations
class Route;

class Galaxy {
private:
    std::vector<CelestialBody*> bodies;
    std::vector<Route*> routes;

public:
    Galaxy();
    ~Galaxy();

    void addBody(CelestialBody* body);
    void addRoute(Route* route);
    
    std::vector<CelestialBody*> getBodies() const;
    std::vector<Route*> getRoutes() const;
    
    CelestialBody* findBody(int id) const;
    Route* findRoute(int id) const;
};

#endif // GALAXY_H