#ifndef EMPIRE_H
#define EMPIRE_H

#include <string>
#include <map>
#include <vector>

// Forward declaration
class Planet;

class Empire {
private:
    double treasury;
    std::map<std::string, int> warehouse;
    std::vector<Planet*> ownedPlanets;
    Planet* currentPlanet;

public:
    Empire(double treasury = 500.0);
    ~Empire();

    // Деньги
    double getTreasury() const;
    void addMoney(double amount);
    bool spendMoney(double amount);

    // Ресурсы
    int getResourceAmount(const std::string& resourceName) const;
    void addResource(const std::string& resourceName, int amount);
    bool spendResource(const std::string& resourceName, int amount);

    // Планеты
    void addOwnedPlanet(Planet* planet);
    std::vector<Planet*> getOwnedPlanets() const;
    Planet* getCurrentPlanet() const;
    bool switchPlanet(int planetId);
};

#endif // EMPIRE_H