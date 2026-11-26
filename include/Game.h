#ifndef EMPIRE_OF_STARS_GAME_H
#define EMPIRE_OF_STARS_GAME_H

#include "Galaxy.h"
#include "Planet.h"
#include "Empire.h"
#include <set>

// игровая логика, меню, галактика и империя
namespace GameSettings {
constexpr double STARTING_MONEY = 700.0;
constexpr int MAX_TURNS = 20;
constexpr double TARGET_MONEY = 3000.0;
}

class Game {
private:
    Galaxy galaxy;
    Empire empire;
    int turn, maxTurns;
    double targetMoney;
    bool running, won;
    std::set<int> upgradedRoutes;
    void showMap() const;
    void showPlanet() const;
    void showWarehouse() const;
    void buildCorporation();
    void upgradeCorporation();
    void buildRoute();
    void upgradeRoute();
    void trade(bool buy);
    void switchPlanet();
    void finishTurn();
    bool hasLogistics(const Planet* planet) const;
public:
    // создаёт галактику и начальную империю
    Game(
        int planets,
        int asteroids,
        int maxTurns = GameSettings::MAX_TURNS,
        double target = GameSettings::TARGET_MONEY,
        unsigned seed = 0
    );

    void run();
};

#endif
