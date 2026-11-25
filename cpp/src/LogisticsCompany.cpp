#include "LogisticsCompany.h"
#include "Galaxy.h"
#include "Empire.h"
#include "Route.h"
#include "CelestialBody.h"
#include <iostream>
#include <cmath>

LogisticsCompany::LogisticsCompany(int level)
    : Corporation(level, 200.0, {{"Crystal", 10}, {"Ore", 20}}, 150.0) {}

std::string LogisticsCompany::getName() const {
    return "LogisticsCompany";
}

void LogisticsCompany::applyEffect(Empire* empire, Galaxy* galaxy) {
    // Подавляем warning о неиспользуемых параметрах
    (void)empire;
    (void)galaxy;
    
    // Логистическая корпорация снижает стоимость топлива на маршрутах
    double discount = 1.0 - (level * 0.05);  // -5% за уровень
    if (discount < 0.5) discount = 0.5;  // Минимум 50%
    
    std::cout << "[LogisticsCompany] Уровень " << level 
              << ": скидка на топливо " << (discount * 100) << "%" << std::endl;
}

bool LogisticsCompany::buildRoute(int fromId, int toId, Galaxy* galaxy, Empire* empire) {
    // Проверка: хватает ли денег
    if (empire->getTreasury() < buildCostMoney) {
        std::cout << "[LogisticsCompany] Недостаточно денег для постройки маршрута" << std::endl;
        return false;
    }
    
    // Получаем объекты из галактики
    CelestialBody* fromBody = galaxy->findBody(fromId);
    CelestialBody* toBody = galaxy->findBody(toId);
    
    if (!fromBody || !toBody) {
        std::cout << "[LogisticsCompany] Один из объектов не найден" << std::endl;
        return false;
    }
    
    // Вычисляем расстояние между объектами
    auto [x1, y1] = fromBody->getCoordinates();
    auto [x2, y2] = toBody->getCoordinates();
    double distance = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    
    // Генерируем ID маршрута (количество существующих маршрутов + 1)
    int routeId = galaxy->getRoutes().size() + 1;
    
    // Создаём маршрут
    Route* route = new Route(routeId, fromId, toId, distance);
    galaxy->addRoute(route);
    
    // Списываем деньги
    empire->spendMoney(buildCostMoney);
    
    std::cout << "[LogisticsCompany] Маршрут построен: " << fromBody->getName() 
              << " -> " << toBody->getName() 
              << " (расстояние: " << distance << ")" << std::endl;
    return true;
}

bool LogisticsCompany::upgradeRoute(int routeId, Galaxy* galaxy, Empire* empire) {
    Route* route = galaxy->findRoute(routeId);
    if (!route) {
        std::cout << "[LogisticsCompany] Маршрут не найден" << std::endl;
        return false;
    }
    
    double cost = route->getUpgradeCost();
    if (empire->getTreasury() < cost) {
        std::cout << "[LogisticsCompany] Недостаточно денег для улучшения маршрута" << std::endl;
        return false;
    }
    
    route->upgrade();
    empire->spendMoney(cost);
    
    std::cout << "[LogisticsCompany] Маршрут " << routeId << " улучшен" << std::endl;
    return true;
}