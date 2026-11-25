// добыча ресурсов с учётом уровня
#include "MinerCompany.h"
#include "Galaxy.h"
#include "Empire.h"
#include "CelestialBody.h"
#include "Planet.h"
#include "Asteroid.h"
#include "Resource.h"
#include <iostream>

MinerCompany::MinerCompany(int level)
    : Corporation(level, 150.0, {{"Ore", 15}, {"Fuel", 10}}, 100.0),
      extractionRate(1.0 + (level - 1) * 0.2) {}  // +20% за уровень

std::string MinerCompany::getName() const {
    return "MinerCompany";
}

void MinerCompany::applyEffect(Empire* empire, Galaxy* galaxy) {
    (void)empire;
    (void)galaxy;
    
    std::cout << "[MinerCompany] Уровень " << level 
              << ": множитель добычи x" << extractionRate << std::endl;
}

void MinerCompany::extractFromPlanet(int planetId, Galaxy* galaxy, Empire* empire) {
    CelestialBody* body = galaxy->findBody(planetId);
    if (!body || body->getType() != "Planet") {
        std::cout << "[MinerCompany] Планета не найдена" << std::endl;
        return;
    }
    
    Planet* planet = dynamic_cast<Planet*>(body);
    std::vector<Resource*> resources = planet->extractResources();
    
    for (Resource* res : resources) {
        int amount = static_cast<int>(res->getAmount() * extractionRate);
        empire->addResource(res->getName(), amount);
        std::cout << "[MinerCompany] Добыто " << amount << " " << res->getName() 
                  << " с планеты " << planet->getName() << std::endl;
        delete res;
    }
}

void MinerCompany::extractFromAsteroid(int asteroidId, Galaxy* galaxy, Empire* empire) {
    CelestialBody* body = galaxy->findBody(asteroidId);
    if (!body || body->getType() != "Asteroid") {
        std::cout << "[MinerCompany] Астероид не найден" << std::endl;
        return;
    }
    
    Asteroid* asteroid = dynamic_cast<Asteroid*>(body);
    std::vector<Resource*> resources = asteroid->extractResources();
    
    for (Resource* res : resources) {
        int amount = static_cast<int>(res->getAmount() * extractionRate);
        empire->addResource(res->getName(), amount);
        std::cout << "[MinerCompany] Добыто " << amount << " " << res->getName() 
                  << " с астероида " << asteroid->getName() << std::endl;
        delete res;
    }
}