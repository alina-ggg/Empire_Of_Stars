#ifndef GAME_H
#define GAME_H

#include "Galaxy.h"
#include "Empire.h"
#include "Planet.h"
#include "Corporation.h"
#include "Route.h"
#include "CelestialBody.h"
#include <string>
#include <set>

class Game {
private:
    Galaxy* galaxy;
    Empire* empire;
    int currentTurn;
    int maxTurns;
    double targetMoney;
    bool isRunning;
    bool isWon;

    // Флаги действий за ход (сбрасываются при завершении хода)
    bool builtCorporationThisTurn;
    bool upgradedCorporationThisTurn;
    bool builtRouteThisTurn;
    std::set<int> upgradedRoutesThisTurn;

    void buildCorporationAction();
    void upgradeCorporationAction();
    void buildRouteAction();
    void upgradeRouteAction();
    void tradeAction();
    void switchPlanetAction();
    void showStatistics();
    void processTurn();
    void printStatus() const;
    bool checkWinCondition();
    void exploreConnectedBodies(int fromPlanetId);

public:
    Game(int numPlanets, int numAsteroids,
         int maxTurns = 20, double targetMoney = 10000.0);
    ~Game();

    // Выполняет одно действие игрока. Возвращает true, если ход был завершён (выбор 0)
    bool playTurn();
    
    bool isGameRunning() const;
    bool hasWon() const;

    Galaxy* getGalaxy() const;
    Empire* getEmpire() const;
    int getCurrentTurn() const;
    int getMaxTurns() const;
    double getTargetMoney() const;
};

#endif // GAME_H