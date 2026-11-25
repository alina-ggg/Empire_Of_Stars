// создание корпораций по имени типа
#include "CorporationFactory.h"
#include "LogisticsCompany.h"
#include "MinerCompany.h"
#include "TechTrader.h"

Corporation* CorporationFactory::create(const std::string& type, int level) {
    // Полиморфизм: возвращаем указатель на базовый класс,
    // но создаём конкретный объект
    if (type == "Logistics") {
        return new LogisticsCompany(level);
    } else if (type == "Miner") {
        return new MinerCompany(level);
    } else if (type == "Trader") {
        return new TechTrader(level);
    }
    return nullptr;  // Неизвестный тип
}