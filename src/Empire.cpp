#include "Empire.h"
#include "Planet.h"


// реализация казны, склада и списка планет, которыми управляет игрок
Empire::Empire(double money) : treasury(money), currentPlanet(nullptr) {
    warehouse = {{"Crystal", 8}, {"Gem", 8}, {"Ore", 8}, {"Fuel", 0}};
}

// возвращает текущий размер казны
double Empire::getTreasury() const {
    return treasury;
}

// пытается списать деньги из казны
bool Empire::spendMoney(double value) {
    if (value < 0 || treasury + 1e-9 < value) return false;
    treasury -= value;
    return true;
}

// добавляет деньги в казну
void Empire::addMoney(double value) {
    if (value > 0) treasury += value;
}

// возвращает значение поля объекта
int Empire::getResourceAmount(const std::string& type) const {
    auto it = warehouse.find(type);
    return it == warehouse.end() ? 0 : it->second;
}

// добавляет ресурс на склад или объект
void Empire::addResource(const std::string& type, int amount) {
    if (amount > 0) warehouse[type] += amount;
}

// списывает ресурс при наличии нужного количества
bool Empire::spendResource(const std::string& type, int amount) {
    if (amount < 0 || getResourceAmount(type) < amount) return false;
    warehouse[type] -= amount;
    return true;
}

// проверяем все затраты до изменения казны и склада
bool Empire::canAfford(double money, const std::map<std::string, int>& resources) const {
    if (money < 0 || treasury + 1e-9 < money) return false;
    for (const auto& item : resources) {
        if (getResourceAmount(item.first) < item.second) return false;
    }
    return true;
}

// одновременно оплачивает деньги и ресурсы
bool Empire::pay(double money, const std::map<std::string, int>& resources) {
    if (!canAfford(money, resources)) return false;
    spendMoney(money);
    for (const auto& item : resources) spendResource(item.first, item.second);
    return true;
}

// подсчитывает торговые корпорации империи
int Empire::countTraders() const {
    int count = 0;
    for (auto planet : planets) {
        for (const auto& corporation : planet->getCorporations()) {
            if (corporation->getType() == "Торговля") ++count;
        }
    }
    return count;
}

// добавляем планету только один раз и назначаем первую планету текущей
void Empire::addPlanet(Planet* planet) {
    if (!planet) return;
    for (auto owned : planets) {
        if (owned == planet) return;
    }
    planets.push_back(planet);
    if (!currentPlanet) currentPlanet = planet;
}

// возвращает список планет империи
const std::vector<Planet*>& Empire::getPlanets() const {
    return planets;
}

// возвращает текущую планету
Planet* Empire::getCurrentPlanet() const {
    return currentPlanet;
}

// переключает игрока на другую доступную планету
bool Empire::switchPlanet(int id) {
    for (auto planet : planets) {
        if (planet->getId() == id) {
            currentPlanet = planet;
            return true;
        }
    }
    return false;
}
