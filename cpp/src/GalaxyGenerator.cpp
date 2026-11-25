#include "GalaxyGenerator.h"
#include "Planet.h"
#include "Asteroid.h"
#include "Crystal.h"
#include "Gem.h"
#include "Ore.h"
#include "Fuel.h"
#include "Gold.h"
#include "CorporationFactory.h"
#include <random>
#include <iostream>

const double MAP_WIDTH = 800.0;
const double MAP_HEIGHT = 600.0;

double GalaxyGenerator::randomDistance() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dist(50.0, MAP_WIDTH - 50.0);
    return dist(gen);
}

int GalaxyGenerator::randomResourceAmount() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(10, 50);
    return dist(gen);
}

void GalaxyGenerator::generate(int numPlanets, int numAsteroids,
                               Galaxy*& galaxy, Empire*& empire) {
    // Создаём объекты
    galaxy = new Galaxy();
    empire = new Empire(500.0);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> xDist(50.0, MAP_WIDTH - 50.0);
    std::uniform_real_distribution<double> yDist(50.0, MAP_HEIGHT - 50.0);

    int idCounter = 1;

    // Генерация планет
    for (int i = 0; i < numPlanets; ++i) {
    std::string name = "Planet-" + std::to_string(i + 1);
    double x = xDist(gen);
    double y = yDist(gen);

    Planet* planet = new Planet(idCounter++, name, x, y, 100);
    
    // ❌ УДАЛИТЬ эту строку: planet->setExplored(true);
    // ✅ Осваиваем только стартовую планету (i == 0)
    if (i == 0) {
        planet->setExplored(true);
    }
    // Все остальные планеты — неосвоенные (isExplored = false по умолчанию)

    // На каждой планете всегда есть золото + случайные ресурсы
    planet->addResource(new Gold(randomResourceAmount()));
    if (gen() % 2 == 0) planet->addResource(new Crystal(randomResourceAmount()));
    if (gen() % 3 == 0) planet->addResource(new Ore(randomResourceAmount()));

    galaxy->addBody(planet);

    // Первая планета — стартовая, принадлежит империи
    if (i == 0) {
        empire->addOwnedPlanet(planet);

        // Строим все 3 корпорации на стартовой планете
        planet->buildCorporation(CorporationFactory::create("Logistics", 1));
        planet->buildCorporation(CorporationFactory::create("Miner", 1));
        planet->buildCorporation(CorporationFactory::create("Trader", 1));

        std::cout << "[GalaxyGenerator] Стартовая планета: " << name << std::endl;
        std::cout << "[GalaxyGenerator] На ней построены 3 корпорации" << std::endl;
    }
}

    // Генерация астероидов
    for (int i = 0; i < numAsteroids; ++i) {
        std::string name = "Asteroid-" + std::to_string(i + 1);
        double x = xDist(gen);
        double y = yDist(gen);

        Asteroid* asteroid = new Asteroid(idCounter++, name, x, y);

        if (gen() % 2 == 0) asteroid->addResource(new Crystal(randomResourceAmount()));
        if (gen() % 3 == 0) asteroid->addResource(new Gem(randomResourceAmount()));
        if (gen() % 2 == 1) asteroid->addResource(new Ore(randomResourceAmount()));
        if (gen() % 3 == 1) asteroid->addResource(new Fuel(randomResourceAmount()));

        galaxy->addBody(asteroid);
    }

    std::cout << "[GalaxyGenerator] Галактика сгенерирована: "
              << numPlanets << " планет, " << numAsteroids << " астероидов" << std::endl;
}