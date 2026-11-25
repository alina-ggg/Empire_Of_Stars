#include "Planet.h"
#include "Corporation.h"
#include <algorithm>


// реализация поведения планеты и правил размещения корпораций
Planet::Planet(int id, const std::string& name, double x, double y)
    : CelestialBody(id, name, x, y) {
    addResource("Gold", 100);
}

// возвращает тип объекта
std::string Planet::getType() const { return "Планета"; }
// проверяет возможность размещения корпорации
bool Planet::canBuildCorporation() const { return true; }

// планета добывает ограниченное количество каждого основного ресурса
std::map<std::string, int> Planet::extractResources(int multiplier) {
    std::map<std::string, int> extracted;
    for (const auto& type : {"Crystal", "Gem", "Ore"}) {
        int amount = std::min(getResource(type), 2 * multiplier);
        if (amount > 0) {
            extracted[type] = amount;
            addResource(type, -amount);
        }
    }

    int gold = std::min(getResource("Gold"), 10 * multiplier);
    if (gold > 0) {
        extracted["Gold"] = gold;
        addResource("Gold", -gold);
    }
    return extracted;
}

// проверяет указанное состояние или условие
bool Planet::hasCorporation(const std::string& type) const {
    return getCorporation(type) != nullptr;
}

// ищет корпорацию по её типу
Corporation* Planet::getCorporation(const std::string& type) const {
    for (const auto& corporation : corporations) {
        if (corporation->getType() == type) return corporation.get();
    }
    return nullptr;
}

bool Planet::addCorporation(std::unique_ptr<Corporation> corporation) {
    if (!corporation || hasCorporation(corporation->getType())) return false;
    corporation->setHomePlanetId(getId());
    corporations.push_back(std::move(corporation));
    return true;
}

// возвращает список корпораций планеты
const std::vector<std::unique_ptr<Corporation>>& Planet::getCorporations() const {
    return corporations;
}

// проверяем, выполнялось ли на этой планете строительство или улучшение в указанном ходу
bool Planet::actionUsed(int turn) const {
    auto it = corporationActionUsed.find(turn);
    return it != corporationActionUsed.end() && it->second;
}

// отмечает выполнение действия в текущем ходу
void Planet::markActionUsed(int turn) {
    corporationActionUsed[turn] = true;
}
