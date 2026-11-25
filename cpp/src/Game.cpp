#include "Game.h"
#include "GalaxyGenerator.h"
#include "CorporationFactory.h"
#include "LogisticsCompany.h"
#include "MinerCompany.h"
#include "TechTrader.h"
#include "ResourceFactory.h"
#include <iostream>
#include <limits>
#include <queue>
#include <set>

Game::Game(int numPlanets, int numAsteroids, int maxTurns, double targetMoney)
    : galaxy(nullptr), empire(nullptr), currentTurn(1),
      maxTurns(maxTurns), targetMoney(targetMoney),
      isRunning(true), isWon(false),
      builtCorporationThisTurn(false),
      upgradedCorporationThisTurn(false),
      builtRouteThisTurn(false) {
    GalaxyGenerator::generate(numPlanets, numAsteroids, galaxy, empire);
}

Game::~Game() {
    delete galaxy;
    delete empire;
}

void Game::printStatus() const {
    std::cout << "\n--- Ход " << currentTurn << " / " << maxTurns 
              << " | Казна: " << (int)empire->getTreasury() << " у.е. ---" << std::endl;
    std::cout << "Текущая планета: " << empire->getCurrentPlanet()->getName() << std::endl;
    
    std::cout << "\nДействия:" << std::endl;
    std::cout << "1. Построить корпорацию";
    if (builtCorporationThisTurn) std::cout << " [уже сделано]";
    std::cout << std::endl;
    
    std::cout << "2. Улучшить корпорацию";
    if (upgradedCorporationThisTurn) std::cout << " [уже сделано]";
    std::cout << std::endl;
    
    std::cout << "3. Построить маршрут";
    if (builtRouteThisTurn) std::cout << " [уже сделано]";
    std::cout << std::endl;
    
    std::cout << "4. Улучшить маршрут" << std::endl;
    std::cout << "5. Торговля (купить/продать)" << std::endl;
    std::cout << "6. Переключиться на другую планету" << std::endl;
    std::cout << "7. Показать статистику" << std::endl;
    std::cout << "0. Завершить ход (перейти к следующему)" << std::endl;
    std::cout << "Выбор: " << std::flush;
}

bool Game::checkWinCondition() {
    if (empire->getTreasury() >= targetMoney) {
        isWon = true;
        isRunning = false;
        std::cout << "\n=== ПОБЕДА! Вы набрали " << (int)empire->getTreasury() 
                  << " у.е. за " << currentTurn << " ходов! ===" << std::endl;
        return true;
    }
    if (currentTurn > maxTurns) {
        isRunning = false;
        std::cout << "\n=== ПОРАЖЕНИЕ. Ходы закончились. Казна: " 
                  << (int)empire->getTreasury() << " у.е. (нужно " << (int)targetMoney << ") ===" << std::endl;
        return true;
    }
    return false;
}

bool Game::playTurn() {
    if (!isRunning) return false;

    printStatus();

    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool turnEnded = false;

    switch (choice) {
        case 1: 
            if (builtCorporationThisTurn) {
                std::cout << "Вы уже построили корпорацию в этом ходу!" << std::endl;
            } else {
                buildCorporationAction();
            }
            break;
        case 2:
            if (upgradedCorporationThisTurn) {
                std::cout << "Вы уже улучшили корпорацию в этом ходу!" << std::endl;
            } else {
                upgradeCorporationAction();
            }
            break;
        case 3:
            if (builtRouteThisTurn) {
                std::cout << "Вы уже построили маршрут в этом ходу!" << std::endl;
            } else {
                buildRouteAction();
            }
            break;
        case 4: upgradeRouteAction(); break;
        case 5: tradeAction(); break;
        case 6: switchPlanetAction(); break;
        case 7: showStatistics(); break;
        case 0:
            processTurn();
            turnEnded = true;
            break;
        default:
            std::cout << "Неверный выбор!" << std::endl;
    }

    checkWinCondition();
    return turnEnded;
}

void Game::buildCorporationAction() {
    Planet* planet = empire->getCurrentPlanet();
    
    if (!planet->getIsExplored()) {
        std::cout << "Планета не освоена! Сначала проложите к ней маршрут." << std::endl;
        return;
    }

    std::cout << "\nДоступные корпорации:" << std::endl;
    std::cout << "1. LogisticsCompany (200 у.е.)" << std::endl;
    std::cout << "2. MinerCompany (150 у.е.)" << std::endl;
    std::cout << "3. TechTrader (300 у.е.)" << std::endl;
    std::cout << "Выбор: " << std::flush;

    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string type;
    if (choice == 1) type = "Logistics";
    else if (choice == 2) type = "Miner";
    else if (choice == 3) type = "Trader";
    else { std::cout << "Неверный выбор\n"; return; }

    for (Corporation* c : planet->getCorporations()) {
        if (c->getName().find(type) != std::string::npos) {
            std::cout << "Такая корпорация уже есть на этой планете!\n";
            return;
        }
    }

    Corporation* corp = CorporationFactory::create(type, 1);
    if (empire->getTreasury() < corp->getBuildCostMoney()) {
        std::cout << "Недостаточно денег! Нужно " << corp->getBuildCostMoney() << " у.е.\n";
        delete corp;
        return;
    }

    if (planet->buildCorporation(corp)) {
        empire->spendMoney(corp->getBuildCostMoney());
        builtCorporationThisTurn = true;
        std::cout << "Корпорация " << corp->getName() 
                  << " построена на планете " << planet->getName() << "!\n";
    } else {
        std::cout << "Не удалось построить\n";
        delete corp;
    }
}

void Game::upgradeCorporationAction() {
    Planet* planet = empire->getCurrentPlanet();
    auto corps = planet->getCorporations();
    if (corps.empty()) {
        std::cout << "Нет корпораций для улучшения\n";
        return;
    }

    std::cout << "\nКорпорации на планете:" << std::endl;
    for (size_t i = 0; i < corps.size(); ++i) {
        std::cout << "  " << (i+1) << ". " << corps[i]->getName() 
                  << " (ур. " << corps[i]->getLevel() 
                  << ", улучшение: " << corps[i]->getUpgradeCostWithLevel() << " у.е.)\n";
    }
    std::cout << "Выбор: " << std::flush;

    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice < 1 || choice > (int)corps.size()) {
        std::cout << "Неверный выбор\n";
        return;
    }

    Corporation* corp = corps[choice - 1];
    double cost = corp->getUpgradeCostWithLevel();
    if (empire->getTreasury() < cost) {
        std::cout << "Недостаточно денег! Нужно " << cost << " у.е.\n";
        return;
    }

    corp->upgrade();
    empire->spendMoney(cost);
    upgradedCorporationThisTurn = true;
    std::cout << corp->getName() << " улучшена до уровня " << corp->getLevel() << "\n";
}

void Game::exploreConnectedBodies(int fromPlanetId) {
    std::queue<int> q;
    std::set<int> visited;
    q.push(fromPlanetId);
    visited.insert(fromPlanetId);

    while (!q.empty()) {
        int current = q.front(); q.pop();
        CelestialBody* body = galaxy->findBody(current);
        if (body) body->setExplored(true);

        for (Route* r : galaxy->getRoutes()) {
            int neighbor = -1;
            if (r->getFromId() == current) neighbor = r->getToId();
            else if (r->getToId() == current) neighbor = r->getFromId();
            
            if (neighbor != -1 && visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }
}

void Game::buildRouteAction() {
    Planet* planet = empire->getCurrentPlanet();
    auto corps = planet->getCorporations();
    bool hasLogistics = false;
    for (Corporation* c : corps) {
        if (c->getName() == "LogisticsCompany") { hasLogistics = true; break; }
    }
    if (!hasLogistics) {
        std::cout << "Нужна LogisticsCompany на текущей планете!\n";
        return;
    }

    std::cout << "\nДоступные объекты для маршрута:" << std::endl;
    auto bodies = galaxy->getBodies();
    for (CelestialBody* b : bodies) {
        if (b->getId() != planet->getId()) {
            std::cout << "  " << b->getId() << ". " << b->getName() 
                      << " (" << b->getType() << ")"
                      << (b->getIsExplored() ? " [освоена]" : " [не освоена]") << "\n";
        }
    }
    std::cout << "ID объекта: " << std::flush;

    int targetId;
    std::cin >> targetId;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    LogisticsCompany* logistics = nullptr;
    for (Corporation* c : corps) {
        if (c->getName() == "LogisticsCompany") {
            logistics = dynamic_cast<LogisticsCompany*>(c);
            break;
        }
    }
    if (logistics) {
        if (logistics->buildRoute(planet->getId(), targetId, galaxy, empire)) {
            builtRouteThisTurn = true;
            exploreConnectedBodies(planet->getId());
            std::cout << "Маршрут построен! Связанные объекты освоены." << std::endl;
        }
    }
}

void Game::upgradeRouteAction() {
    auto routes = galaxy->getRoutes();
    if (routes.empty()) {
        std::cout << "Нет маршрутов для улучшения\n";
        return;
    }
    std::cout << "\nМаршруты:" << std::endl;
    for (Route* r : routes) {
        std::cout << "  " << r->getId() << ". " << r->getFromId() << " -> " << r->getToId()
                  << " (ур. " << r->getLevel() 
                  << ", улучшение: " << r->getUpgradeCost() << " у.е.)"
                  << (upgradedRoutesThisTurn.count(r->getId()) ? " [уже улучшен]" : "") << "\n";
    }
    std::cout << "ID маршрута: " << std::flush;

    int id;
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (upgradedRoutesThisTurn.find(id) != upgradedRoutesThisTurn.end()) {
        std::cout << "Этот маршрут уже улучшен в этом ходу!" << std::endl;
        return;
    }

    Planet* planet = empire->getCurrentPlanet();
    LogisticsCompany* logistics = nullptr;
    for (Corporation* c : planet->getCorporations()) {
        if (c->getName() == "LogisticsCompany") {
            logistics = dynamic_cast<LogisticsCompany*>(c);
            break;
        }
    }
    if (logistics) {
        if (logistics->upgradeRoute(id, galaxy, empire)) {
            upgradedRoutesThisTurn.insert(id);
        }
    }
}

void Game::tradeAction() {
    Planet* planet = empire->getCurrentPlanet();
    bool hasTrader = false;
    for (Corporation* c : planet->getCorporations()) {
        if (c->getName() == "TechTrader") { hasTrader = true; break; }
    }
    if (!hasTrader) {
        std::cout << "Нужна TechTrader на текущей планете!\n";
        return;
    }

    TechTrader* trader = nullptr;
    for (Corporation* c : planet->getCorporations()) {
        if (c->getName() == "TechTrader") {
            trader = dynamic_cast<TechTrader*>(c);
            break;
        }
    }
    if (!trader) return;

    std::cout << "\nТорговля:" << std::endl;
    std::cout << "1. Продать ресурс" << std::endl;
    std::cout << "2. Купить ресурс" << std::endl;
    std::cout << "Выбор: " << std::flush;
    
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Ресурс (Crystal/Gem/Ore/Fuel): " << std::flush;
    std::string resName;
    std::cin >> resName;

    std::cout << "Количество: " << std::flush;
    int amount;
    std::cin >> amount;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 1) trader->sellResource(empire, resName, amount);
    else if (choice == 2) trader->buyResource(empire, resName, amount);
    else std::cout << "Неверный выбор\n";
}

void Game::switchPlanetAction() {
    auto planets = empire->getOwnedPlanets();
    if (planets.empty()) {
        std::cout << "У вас нет планет!\n";
        return;
    }
    std::cout << "\nВаши планеты:" << std::endl;
    for (Planet* p : planets) {
        std::cout << "  " << p->getId() << ". " << p->getName() 
                  << (p->getIsExplored() ? " [освоена]" : "") << "\n";
    }
    std::cout << "ID планеты: " << std::flush;

    int id;
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    empire->switchPlanet(id);
}

void Game::showStatistics() {
    std::cout << "\n========== Статистика империи ==========" << std::endl;
    std::cout << "Ход: " << currentTurn << " / " << maxTurns << std::endl;
    std::cout << "Казна: " << (int)empire->getTreasury() << " / " 
              << (int)targetMoney << " у.е." << std::endl;
    std::cout << "Прогресс: " << (int)(empire->getTreasury() / targetMoney * 100) << "%" << std::endl;
    std::cout << "Планет во владении: " << empire->getOwnedPlanets().size() << std::endl;
    std::cout << "Склад ресурсов:" << std::endl;
    std::cout << "  Crystal: " << empire->getResourceAmount("Crystal") << std::endl;
    std::cout << "  Gem: " << empire->getResourceAmount("Gem") << std::endl;
    std::cout << "  Ore: " << empire->getResourceAmount("Ore") << std::endl;
    std::cout << "  Fuel: " << empire->getResourceAmount("Fuel") << std::endl;
    std::cout << "Маршрутов построено: " << galaxy->getRoutes().size() << std::endl;
    std::cout << "========================================\n" << std::endl;
}

void Game::processTurn() {
    std::cout << "\n--- Переход к ходу " << (currentTurn + 1) << " ---" << std::endl;

    double totalExpenses = 0;

    for (Planet* planet : empire->getOwnedPlanets()) {
        for (Corporation* corp : planet->getCorporations()) {
            corp->applyEffect(empire, galaxy);

            MinerCompany* miner = dynamic_cast<MinerCompany*>(corp);
            if (miner) {
                // MinerCompany сама добавляет ресурсы в empire и выводит сообщения
                miner->extractFromPlanet(planet->getId(), galaxy, empire);
                
                // Добыча на связанных астероидах
                for (Route* route : galaxy->getRoutes()) {
                    if (route->getFromId() == planet->getId() || route->getToId() == planet->getId()) {
                        int otherId = (route->getFromId() == planet->getId()) 
                                      ? route->getToId() : route->getFromId();
                        CelestialBody* other = galaxy->findBody(otherId);
                        if (other && other->getType() == "Asteroid") {
                            miner->extractFromAsteroid(otherId, galaxy, empire);
                        }
                    }
                }
            }
        }
    }

    // Трата денег на топливо для маршрутов
    for (Route* route : galaxy->getRoutes()) {
        double fuelCost = route->getFuelCost();
        if (empire->getTreasury() >= fuelCost) {
            empire->spendMoney(fuelCost);
            totalExpenses += fuelCost;
        } else {
            std::cout << "Недостаточно денег на топливо для маршрута " 
                      << route->getFromId() << " -> " << route->getToId() << "!" << std::endl;
        }
    }

    // Увеличиваем счётчик хода
    currentTurn++;
    
    // Сбрасываем флаги для нового хода
    builtCorporationThisTurn = false;
    upgradedCorporationThisTurn = false;
    builtRouteThisTurn = false;
    upgradedRoutesThisTurn.clear();

    std::cout << "\nИтоги хода:" << std::endl;
    std::cout << "  Расходы на топливо: -" << (int)totalExpenses << " у.е." << std::endl;
    std::cout << "  Казна: " << (int)empire->getTreasury() << " у.е." << std::endl;
    std::cout << "  Следующий ход: " << currentTurn << " / " << maxTurns << std::endl;
}

bool Game::isGameRunning() const { return isRunning; }
bool Game::hasWon() const { return isWon; }
Galaxy* Game::getGalaxy() const { return galaxy; }
Empire* Game::getEmpire() const { return empire; }
int Game::getCurrentTurn() const { return currentTurn; }
int Game::getMaxTurns() const { return maxTurns; }
double Game::getTargetMoney() const { return targetMoney; }