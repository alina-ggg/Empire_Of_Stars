// общая реализация для планет и астероидов
#include "CelestialBody.h"

CelestialBody::CelestialBody(int id, const std::string& name, double x, double y)
    : id(id), name(name), x(x), y(y), isExplored(false) {}

CelestialBody::~CelestialBody() {
    // Освобождаем ресурсы
    for (Resource* res : resources) {
        delete res;
    }
    resources.clear();
}

int CelestialBody::getId() const {
    return id;
}

std::string CelestialBody::getName() const {
    return name;
}

std::pair<double, double> CelestialBody::getCoordinates() const {
    return {x, y};
}

bool CelestialBody::getIsExplored() const {
    return isExplored;
}

std::vector<Resource*> CelestialBody::getResources() const {
    return resources;
}

void CelestialBody::addResource(Resource* resource) {
    resources.push_back(resource);
}

std::vector<Resource*> CelestialBody::extractResources() {
    std::vector<Resource*> extracted = resources;
    resources.clear(); 
    return extracted;
}

void CelestialBody::setExplored(bool explored) {
    isExplored = explored;
}