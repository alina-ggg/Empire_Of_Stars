// постройка корпораций, золотой запас
#include "Planet.h"
#include "Corporation.h"  // Теперь подключаем, т.к. используем методы

Planet::Planet(int id, const std::string& name, double x, double y, int goldReserve)
    : CelestialBody(id, name, x, y), goldReserve(goldReserve) {}

Planet::~Planet() {
    // Освобождаем корпорации
    for (Corporation* corp : corporations) {
        delete corp;
    }
    corporations.clear();
}

std::string Planet::getType() const {
    return "Planet";
}

bool Planet::canBuildCorporation() const {
    return true;  // На планетах можно строить корпорации
}

bool Planet::buildCorporation(Corporation* corporation) {
    // Проверка: можно ли построить только одну корпорацию каждого вида
    std::string corpType = corporation->getName();
    for (Corporation* existing : corporations) {
        if (existing->getName() == corpType) {
            return false;  // Такая корпорация уже есть
        }
    }
    corporations.push_back(corporation);
    return true;
}

std::vector<Corporation*> Planet::getCorporations() const {
    return corporations;
}

int Planet::getGoldReserve() const {
    return goldReserve;
}

void Planet::addGold(int amount) {
    goldReserve += amount;
}