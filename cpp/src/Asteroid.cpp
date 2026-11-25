// только добыча ресурсов
#include "Asteroid.h"

Asteroid::Asteroid(int id, const std::string& name, double x, double y)
    : CelestialBody(id, name, x, y) {}

std::string Asteroid::getType() const {
    return "Asteroid";
}

bool Asteroid::canBuildCorporation() const {
    return false;  // на астероидах нельзя строить корпорации
}