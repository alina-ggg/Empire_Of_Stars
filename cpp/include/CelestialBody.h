// базовый класс объектов
#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include <string>
#include <vector>
#include <utility>
#include "Resource.h"

class CelestialBody {
protected:
    int id;
    std::string name;
    double x;
    double y;
    std::vector<Resource*> resources;
    bool isExplored;

public:
    CelestialBody(int id, const std::string& name, double x, double y);
    virtual ~CelestialBody();
    
    virtual std::string getType() const = 0;
    virtual bool canBuildCorporation() const = 0;

    int getId() const;
    std::string getName() const;
    std::pair<double, double> getCoordinates() const;
    bool getIsExplored() const;
    std::vector<Resource*> getResources() const;

    // методы
    void addResource(Resource* resource);
    std::vector<Resource*> extractResources();
    void setExplored(bool explored);
};

#endif 