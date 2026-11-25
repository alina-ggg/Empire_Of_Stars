#include "Corporation.h"
#include "Empire.h"

Corporation::Corporation(int level, double buildCostMoney,
                         const std::map<std::string, int>& buildCostResources,
                         double upgradeCostMoney)
    : level(level), buildCostMoney(buildCostMoney),
      buildCostResources(buildCostResources), upgradeCostMoney(upgradeCostMoney) {}

Corporation::~Corporation() {}

int Corporation::getLevel() const {
    return level;
}

double Corporation::getBuildCostMoney() const {
    return buildCostMoney;
}

std::map<std::string, int> Corporation::getBuildCostResources() const {
    return buildCostResources;
}

double Corporation::getUpgradeCostMoney() const {
    return upgradeCostMoney;
}

void Corporation::upgrade() {
    level++;
}

bool Corporation::canUpgrade(Empire* empire) const {
    // проверка: хватает ли денег и ресурсов
    double cost = getUpgradeCostWithLevel();
    if (empire->getTreasury() < cost) {
        return false;
    }
    // Проверка ресурсов
    for (const auto& pair : buildCostResources) {
        if (empire->getResourceAmount(pair.first) < pair.second) {
            return false;
        }
    }
    return true;
}

double Corporation::getUpgradeCostWithLevel() const {
    // стоимость улучшения растёт с уровнем: base * level
    return upgradeCostMoney * level;
}