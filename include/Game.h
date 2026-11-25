#ifndef EMPIRE_OF_STARS_GAME_H
#define EMPIRE_OF_STARS_GAME_H

#include "Galaxy.h"
#include "Planet.h"
#include "Empire.h"
#include <set>

// класс game связывает игровую логику, меню, галактику и империю
namespace GameSettings {
constexpr double STARTING_MONEY = 700.0;
constexpr int MAX_TURNS = 20;
constexpr double TARGET_MONEY = 3000.0;
}
// класс game описывает отдельную сущность игровой модели
class Game {
private:
    Galaxy galaxy;
    Empire empire;
    int turn, maxTurns;
    double targetMoney;
    bool running, won;
    std::set<int> upgradedRoutes;
// выводит карту галактики и сведения об объектах
    void showMap() const;
// выводит состояние текущей планеты
    void showPlanet() const;
// выводит состояние казны и склада
    void showWarehouse() const;
// строит корпорацию на текущей планете
    void buildCorporation();
// улучшает выбранную корпорацию
    void upgradeCorporation();
// создаёт маршрут к выбранному объекту
    void buildRoute();
// улучшает выбранный маршрут
    void upgradeRoute();
// выполняет покупку или продажу ресурсов
    void trade(bool buy);
// переключает игрока на другую доступную планету
    void switchPlanet();
// выполняет расчёты и завершает текущий ход
    void finishTurn();
// проверяет указанное состояние или условие
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
    // запускает цикл: показывает меню и выполняет выбранные игроком действия
    void run();
};

#endif // empire_of_stars_game_h
