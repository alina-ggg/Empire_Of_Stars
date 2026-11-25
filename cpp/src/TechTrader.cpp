// покупка/продажа с бонусом от количества
#include "TechTrader.h"
#include "Empire.h"
#include "ResourceFactory.h"
#include "Resource.h"
#include <iostream>

TechTrader::TechTrader(int level)
    : Corporation(level, 300.0, {{"Crystal", 20}, {"Gem", 5}}, 200.0),
      priceBonus(1.0 + (level - 1) * 0.1) {}  // +10% к цене за уровень

std::string TechTrader::getName() const {
    return "TechTrader";
}

void TechTrader::applyEffect(Empire* empire, Galaxy* galaxy) {
    (void)empire;
    (void)galaxy;
    
    std::cout << "[TechTrader] Уровень " << level 
              << ": бонус к цене продажи x" << priceBonus << std::endl;
}

bool TechTrader::sellResource(Empire* empire, const std::string& resourceName, int amount) {

    if (empire->getResourceAmount(resourceName) < amount) {
        std::cout << "[TechTrader] Недостаточно ресурса " << resourceName << std::endl;
        return false;
    }
    
    Resource* tempResource = ResourceFactory::create(resourceName, 1);
    if (!tempResource) {
        std::cout << "[TechTrader] Неизвестный ресурс: " << resourceName << std::endl;
        return false;
    }
    
    double basePrice = tempResource->getBasePrice();
    double sellPrice = basePrice * amount * priceBonus;
    delete tempResource;
    
    // Списываем ресурс и добавляем деньги
    empire->spendResource(resourceName, amount);
    empire->addMoney(sellPrice);
    
    std::cout << "[TechTrader] Продано " << amount << " " << resourceName 
              << " за " << sellPrice << " у.е." << std::endl;
    return true;
}

bool TechTrader::buyResource(Empire* empire, const std::string& resourceName, int amount) {
    Resource* tempResource = ResourceFactory::create(resourceName, 1);
    if (!tempResource) {
        std::cout << "[TechTrader] Неизвестный ресурс: " << resourceName << std::endl;
        return false;
    }
    
    double basePrice = tempResource->getBasePrice();
    double buyPrice = basePrice * amount * 1.5;  // Покупка дороже на 50%
    delete tempResource;
    
    if (empire->getTreasury() < buyPrice) {
        std::cout << "[TechTrader] Недостаточно денег для покупки" << std::endl;
        return false;
    }
    
    empire->spendMoney(buyPrice);
    empire->addResource(resourceName, amount);
    
    std::cout << "[TechTrader] Куплено " << amount << " " << resourceName 
              << " за " << buyPrice << " у.е." << std::endl;
    return true;
}