#ifndef CORPORATION_H
#define CORPORATION_H

#include <string>
#include <map>

class Empire;
class Galaxy;

class Corporation {
protected:
    int level;
    double buildCostMoney;
    std::map<std::string, int> buildCostResources;
    double upgradeCostMoney;

public:
    Corporation(int level, double buildCostMoney, 
                const std::map<std::string, int>& buildCostResources,
                double upgradeCostMoney);
    virtual ~Corporation();

    virtual std::string getName() const = 0;
    virtual void applyEffect(Empire* empire, Galaxy* galaxy) = 0;

    int getLevel() const;
    double getBuildCostMoney() const;
    std::map<std::string, int> getBuildCostResources() const;
    double getUpgradeCostMoney() const;

    virtual void upgrade();
    bool canUpgrade(Empire* empire) const;
    double getUpgradeCostWithLevel() const;  // стоимость улучшения растёт с уровнем
};

#endif 