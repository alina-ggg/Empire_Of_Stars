#include "Empire.h"
#include "Planet.h"
#include <iostream>

Empire::Empire(double treasury)
    : treasury(treasury), currentPlanet(nullptr) {
    warehouse["Crystal"] = 10;
    warehouse["Gem"] = 10;
    warehouse["Ore"] = 10;
    warehouse["Fuel"] = 10;
    warehouse["Gold"] = 10;
}

Empire::~Empire() {
    // Не удаляем планеты — они принадлежат Galaxy
    ownedPlanets.clear();
    currentPlanet = nullptr;
}

double Empire::getTreasury() const {
    return treasury;
}

void Empire::addMoney(double amount) {
    treasury += amount;
}

bool Empire::spendMoney(double amount) {
    if (treasury < amount) {
        std::cout << "[Empire] Недостаточно денег" << std::endl;
        return false;
    }
    treasury -= amount;
    return true;
}

int Empire::getResourceAmount(const std::string& resourceName) const {
    auto it = warehouse.find(resourceName);
    if (it != warehouse.end()) {
        return it->second;
    }
    return 0;
}

void Empire::addResource(const std::string& resourceName, int amount) {
    warehouse[resourceName] += amount;
}

bool Empire::spendResource(const std::string& resourceName, int amount) {
    if (warehouse[resourceName] < amount) {
        std::cout << "[Empire] Недостаточно ресурса " << resourceName << std::endl;
        return false;
    }
    warehouse[resourceName] -= amount;
    return true;
}

void Empire::addOwnedPlanet(Planet* planet) {
    ownedPlanets.push_back(planet);
    if (!currentPlanet) {
        currentPlanet = planet;  // Первая планета — стартовая
    }
}

std::vector<Planet*> Empire::getOwnedPlanets() const {
    return ownedPlanets;
}

Planet* Empire::getCurrentPlanet() const {
    return currentPlanet;
}

bool Empire::switchPlanet(int planetId) {
    for (Planet* p : ownedPlanets) {
        if (p->getId() == planetId) {
            currentPlanet = p;
            std::cout << "[Empire] Переключились на планету: " 
                      << p->getName() << std::endl;
            return true;
        }
    }
    std::cout << "[Empire] Планета с ID " << planetId << " не найдена" << std::endl;
    return false;
}