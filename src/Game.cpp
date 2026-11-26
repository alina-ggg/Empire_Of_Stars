#include "Game.h"
#include "Planet.h"
#include "Corporation.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>


// основной игровой процесс и обработка команд из консольного меню
namespace {
// ввод целого числа из консоли
int readInt(const std::string& prompt, int minValue, int maxValue) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) return minValue;

        std::stringstream input(line);
        int value;
        char extra;
        if (input >> value && !(input >> extra) &&
            value >= minValue && value <= maxValue) {
            return value;
        }
        std::cout << "Введите целое число от " << minValue
                  << " до " << maxValue << "\n";
    }
}
}

// создаём галактику и стартовую империю
Game::Game(int planets, int asteroids, int limit, double target, unsigned seed)
    : empire(GameSettings::STARTING_MONEY), turn(1), maxTurns(limit),
      targetMoney(target), running(true), won(false) {
    std::mt19937 generator(seed ? seed : std::random_device{}());
    std::uniform_real_distribution<double> coordinate(5.0, 95.0);
    std::uniform_int_distribution<int> stock(8, 30);
    std::uniform_int_distribution<int> resourceChance(0, 3);

    // генерируем планеты и случайные запасы полезных ископаемых
    for (int i = 1; i <= planets; ++i) {
        auto planet = std::make_unique<Planet>(
            i, "Планета-" + std::to_string(i), coordinate(generator), coordinate(generator));
        planet->addResource("Crystal", stock(generator));
        planet->addResource("Gem", stock(generator));
        planet->addResource("Ore", stock(generator));

// добавляет космический объект в галактику
        auto rawPlanet = static_cast<Planet*>(galaxy.addBody(std::move(planet)));
        if (i == 1) {
            rawPlanet->addCorporation(CorporationFactory::create("1"));
            rawPlanet->addCorporation(CorporationFactory::create("2"));
            rawPlanet->addCorporation(CorporationFactory::create("3"));
            empire.addPlanet(rawPlanet);
        }
    }

    // генерируем астероиды и их полезные ископаемые
    for (int i = 1; i <= asteroids; ++i) {
        auto asteroid = std::make_unique<Asteroid>(
            planets + i, "Астероид-" + std::to_string(i),
            coordinate(generator), coordinate(generator));

        for (const auto& type : {"Crystal", "Gem", "Ore", "Fuel"}) {
            if (resourceChance(generator) != 0) {
                asteroid->addResource(type, stock(generator));
            }
        }
// добавляет космический объект в галактику
        galaxy.addBody(std::move(asteroid));
    }

    std::cout << "\nИмперия звёзд создана: " << planets << " планет, "
              << asteroids << " астероидов\n";
    std::cout << "Стартовая планета: Планета-1 | казна: "
              << empire.getTreasury() << " у.е. | цель: " << targetMoney
              << " у.е. за " << maxTurns << " ходов\n";
}

// проверяет указанное состояние или условие
bool Game::hasLogistics(const Planet* planet) const {
    return planet && planet->hasCorporation("Логистика");
}

// показываем условную карту и список всех объектов
void Game::showMap() const {
    std::cout << "\n--- КАРТА ГАЛАКТИКИ ---\n";
    const int width = 42;
    const int height = 13;
    std::vector<std::string> grid(height, std::string(width, ' '));

    for (auto body : galaxy.getBodies()) {
        int x = 1 + static_cast<int>(body->getX() / 100.0 * (width - 3));
        int y = 1 + static_cast<int>(body->getY() / 100.0 * (height - 3));
        char mark = body->getType() == "Планета" ? 'P' : '*';
        if (body->getId() == empire.getCurrentPlanet()->getId()) mark = '@';
        grid[y][x] = mark;
    }

    for (const auto& line : grid) std::cout << '|' << line << "|\n";
    std::cout << "Объекты:\n";
    for (auto body : galaxy.getBodies()) {
        std::cout << std::setw(2) << body->getId() << "  " << std::left
// изменяет значение поля объекта
                  << std::setw(15) << body->getName() << std::setw(12) << body->getType()
                  << " ресурсы: C" << body->getResource("Crystal")
                  << " G" << body->getResource("Gem") << " O" << body->getResource("Ore");
        if (body->isExplored()) std::cout << " [освоен]";
        std::cout << "\n";
    }

    std::cout << "Маршруты:\n";
    for (auto route : galaxy.getRoutes()) {
        std::cout << "  #" << route->getId() << ": " << route->getFromId()
                  << " <-> " << route->getToId() << ", расстояние "
                  << route->getDistance() << ", ур. " << route->getLevel()
                  << ", перевозка " << route->getTransportCost() << " у.е.\n";
    }
}

// выводит состояние текущей планеты
void Game::showPlanet() const {
    auto planet = empire.getCurrentPlanet();
    std::cout << "\n" << planet->getName()
              << " | золото: " << planet->getResource("Gold")
              << " | кристаллы: " << planet->getResource("Crystal")
              << " | камни: " << planet->getResource("Gem")
              << " | руда: " << planet->getResource("Ore") << "\nКорпорации:\n";

    for (const auto& corporation : planet->getCorporations()) {
        std::cout << "  " << corporation->getType() << ", уровень "
                  << corporation->getLevel() << " — "
                  << corporation->getDescription() << "\n";
    }
}

// выводит состояние казны и склада
void Game::showWarehouse() const {
    std::cout << "\nКАЗНА: " << std::fixed << std::setprecision(1)
              << empire.getTreasury() << " у.е.\nСКЛАД: кристаллы "
              << empire.getResourceAmount("Crystal") << ", драгоценные камни "
              << empire.getResourceAmount("Gem") << ", руда "
              << empire.getResourceAmount("Ore") << ", топливо "
              << empire.getResourceAmount("Fuel") << "\nПланет во владении: "
              << empire.getPlanets().size() << " | торговых корпораций: "
              << empire.countTraders() << "\n";
}

// строительство или улучшение корпорации — одно действие на планету за ход
void Game::buildCorporation() {
    auto planet = empire.getCurrentPlanet();
    if (planet->actionUsed(turn)) {
        std::cout << "На этой планете уже строили или улучшали корпорацию в этом ходу\n";
        return;
    }

    std::cout << "1. Логистика (200 у.е., 2 кристалла)\n"
              << "2. Добыча (150 у.е., 2 руды)\n"
              << "3. Торговля (300 у.е., 2 камня)\n";
    int choice = readInt("Тип: ", 1, 3);
// создаёт объект нужного типа через простую фабрику
    auto corporation = CorporationFactory::create(std::to_string(choice));

    if (planet->hasCorporation(corporation->getType())) {
        std::cout << "Такая корпорация уже есть на планете\n";
        return;
    }
    if (!empire.pay(corporation->getBuildMoney(), corporation->getBuildResources())) {
        std::cout << "Недостаточно денег или ресурсов\n";
        return;
    }

// возвращает тип объекта
    std::string name = corporation->getType();
    planet->addCorporation(std::move(corporation));
    planet->markActionUsed(turn);
    std::cout << name << " построена\n";
}

// улучшает выбранную корпорацию
void Game::upgradeCorporation() {
    auto planet = empire.getCurrentPlanet();
    if (planet->actionUsed(turn)) {
        std::cout << "На этой планете уже выполняли действие с корпорацией в этом ходу\n";
        return;
    }

    const auto& corporations = planet->getCorporations();
    if (corporations.empty()) {
        std::cout << "Нет корпораций\n";
        return;
    }
    for (size_t i = 0; i < corporations.size(); ++i) {
        std::cout << i + 1 << ". " << corporations[i]->getType()
                  << " ур. " << corporations[i]->getLevel()
                  << " | улучшение: " << corporations[i]->getUpgradeMoney()
                  << " у.е. и ресурсы\n";
    }

    int choice = readInt("Номер: ", 1, static_cast<int>(corporations.size()));
    auto corporation = corporations[choice - 1].get();
    if (!empire.pay(corporation->getUpgradeMoney(), corporation->getUpgradeResources())) {
        std::cout << "Недостаточно денег или ресурсов\n";
        return;
    }

    corporation->upgrade();
    planet->markActionUsed(turn);
    std::cout << corporation->getType() << " улучшена до уровня "
              << corporation->getLevel() << "\n";
}

// логистическая корпорация прокладывает маршрут от текущей планеты
void Game::buildRoute() {
    auto planet = empire.getCurrentPlanet();
    auto logistics = dynamic_cast<LogisticsCompany*>(planet->getCorporation("Логистика"));
    if (!logistics) {
        std::cout << "Для создания маршрута нужна логистическая корпорация на текущей планете\n";
        return;
    }

    showMap();
    int targetId = readInt("ID объекта назначения: ", 1,
                           static_cast<int>(galaxy.getBodies().size()));
    auto target = galaxy.findBody(targetId);
    if (!target || targetId == planet->getId()) {
        std::cout << "Неверный объект\n";
        return;
    }
    if (galaxy.findRouteBetween(planet->getId(), targetId)) {
        std::cout << "Маршрут уже существует\n";
        return;
    }

    if (!logistics->buildRoute(galaxy, empire, targetId)) {
        std::cout << "Не удалось создать маршрут: проверьте казну\n";
        return;
    }
    if (target->getType() == "Планета") {
        empire.addPlanet(static_cast<Planet*>(target));
    }
    std::cout << "Маршрут создан\n";
}

// улучшает выбранный маршрут
void Game::upgradeRoute() {
    auto routes = galaxy.getRoutes();
    if (routes.empty()) {
        std::cout << "Маршрутов пока нет\n";
        return;
    }
    for (auto route : routes) {
        std::cout << "#" << route->getId() << " " << route->getFromId()
                  << "-" << route->getToId() << " ур." << route->getLevel()
                  << " стоимость улучшения " << route->getUpgradeCost();
        if (upgradedRoutes.count(route->getId())) std::cout << " [уже улучшен в этом ходу]";
        std::cout << "\n";
    }

    int id = readInt("ID маршрута: ", 1, 100000);
    auto route = galaxy.findRoute(id);
    if (!route) {
        std::cout << "Маршрут не найден\n";
        return;
    }
    if (upgradedRoutes.count(id)) {
        std::cout << "Этот маршрут уже улучшали в текущем ходу\n";
        return;
    }

    auto planet = empire.getCurrentPlanet();
    auto logistics = dynamic_cast<LogisticsCompany*>(planet->getCorporation("Логистика"));
    if (!logistics || !logistics->upgradeRoute(galaxy, empire, id)) {
        std::cout << "Нужно иметь логистику на одном из концов маршрута и достаточно денег\n";
        return;
    }

    upgradedRoutes.insert(id);
    std::cout << "Маршрут улучшен. Новая стоимость перевозки: "
              << route->getTransportCost() << " у.е.\n";
}

void Game::trade(bool buy) {
    int traderCount = empire.countTraders();
    TechTrader* trader = nullptr;
    for (auto planet : empire.getPlanets()) {
        trader = dynamic_cast<TechTrader*>(planet->getCorporation("Торговля"));
        if (trader) break;
    }
    if (!trader || traderCount == 0) {
        std::cout << "Нужна хотя бы одна торговая корпорация в империи\n";
        return;
    }

    std::cout << "1. Кристаллы  2. Драгоценные камни  3. Руда  4. Топливо\n";
    int choice = readInt("Ресурс: ", 1, 4);
    const std::string names[] = {"Crystal", "Gem", "Ore", "Fuel"};
    std::string type = names[choice - 1];
    int amount = readInt("Количество: ", 1, 100000);
    double price = trader->getPrice(type, traderCount, buy);
    bool success = buy
        ? trader->buyResource(empire, type, amount, traderCount)
        : trader->sellResource(empire, type, amount, traderCount);

    if (!success) {
        std::cout << (buy ? "Недостаточно денег для покупки\n"
                          : "На складе недостаточно ресурса для продажи\n");
        return;
    }
    std::cout << (buy ? "Куплено " : "Продано ") << amount
              << " ед. по " << price << " у.е. за единицу\n";
}

// перемещение разрешено только по существующей цепочке маршрутов
void Game::switchPlanet() {
    auto current = empire.getCurrentPlanet();
    std::cout << "Доступные планеты (нужна цепочка маршрутов от текущей):\n";
    for (auto planet : empire.getPlanets()) {
        std::cout << planet->getId() << ". " << planet->getName()
                  << (galaxy.hasPath(current->getId(), planet->getId())
                          ? " [доступна]" : " [нет пути]") << "\n";
    }

    int id = readInt("ID планеты: ", 1, static_cast<int>(galaxy.getBodies().size()));
    auto body = galaxy.findBody(id);
    if (!body || body->getType() != "Планета" ||
        !galaxy.hasPath(current->getId(), id) || !empire.switchPlanet(id)) {
        std::cout << "Перемещение невозможно: нет цепочки маршрутов или планета не принадлежит империи\n";
        return;
    }
    std::cout << "Текущая планета: " << empire.getCurrentPlanet()->getName() << "\n";
}

// выполняем добычу и оплату перевозок при переходе к следующему ходу
void Game::finishTurn() {
    std::cout << "\n=== Итоги хода " << turn << " ===\n";
    for (auto planet : empire.getPlanets()) {
        for (const auto& corporation : planet->getCorporations()) {
            corporation->applyTurn(empire, galaxy, planet->getId());
        }
    }

    ++turn;
    upgradedRoutes.clear();
    std::cout << "Ход завершён. Казна: " << empire.getTreasury() << " у.е.\n";
    if (empire.getTreasury() >= targetMoney) {
        won = true;
        running = false;
    } else if (turn > maxTurns) {
        running = false;
    }
}

// запускает основной цикл игры
void Game::run() {
    while (running) {
        std::cout << "\n==================================================\n"
                  << "ИМПЕРИЯ ЗВЁЗД | Ход " << turn << "/" << maxTurns
                  << " | " << empire.getCurrentPlanet()->getName() << "\n"
                  << "Казна: " << empire.getTreasury() << " / " << targetMoney << " у.е.\n"
                  << "1. Карта галактики\n2. Информация о планете\n"
                  << "3. Казна и склад\n4. Построить корпорацию\n"
                  << "5. Улучшить корпорацию\n6. Построить маршрут\n"
                  << "7. Улучшить маршрут\n8. Купить ресурсы\n"
                  << "9. Продать ресурсы\n10. Переместиться на планету\n"
                  << "0. Завершить ход\n";

        int choice = readInt("Выбор: ", 0, 10);
        switch (choice) {
            case 1: showMap(); break;
            case 2: showPlanet(); break;
            case 3: showWarehouse(); break;
            case 4: buildCorporation(); break;
            case 5: upgradeCorporation(); break;
            case 6: buildRoute(); break;
            case 7: upgradeRoute(); break;
            case 8: trade(true); break;
            case 9: trade(false); break;
            case 10: switchPlanet(); break;
            case 0: finishTurn(); break;
        }

        // победа проверяется сразу после продажи ресурсов и завершения хода
        if (running && empire.getTreasury() >= targetMoney) {
            won = true;
            running = false;
        }
    }

    std::cout << "\n================ ИГРА ЗАВЕРШЕНА ================\n"
              << (won ? "ПОБЕДА" : "ПОРАЖЕНИЕ") << "\n"
              << "Использовано ходов: " << std::min(turn, maxTurns) << "\n"
              << "Итоговая казна: " << empire.getTreasury() << " у.е.\n"
              << "Склад: кристаллы " << empire.getResourceAmount("Crystal")
              << ", камни " << empire.getResourceAmount("Gem")
              << ", руда " << empire.getResourceAmount("Ore")
              << ", топливо " << empire.getResourceAmount("Fuel") << "\n"
              << "Причина: " << (won ? "достигнута цель по казне" : "закончился лимит ходов")
              << "\n";
}
