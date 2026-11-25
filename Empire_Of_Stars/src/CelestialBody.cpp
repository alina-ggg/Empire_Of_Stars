#include "CelestialBody.h"
#include <algorithm>


// реализация общих операций для планет и астероидов
CelestialBody::CelestialBody(int id, const std::string& name, double x, double y)
    : id(id), name(name), x(x), y(y), explored(false) {}

// возвращает идентификатор объекта
int CelestialBody::getId() const { return id; }
// возвращает название объекта
const std::string& CelestialBody::getName() const { return name; }
// возвращает координату объекта по оси x
double CelestialBody::getX() const { return x; }
// возвращает координату объекта по оси y
double CelestialBody::getY() const { return y; }
// проверяет, исследован ли объект
bool CelestialBody::isExplored() const { return explored; }
// изменяет признак исследования объекта
void CelestialBody::setExplored(bool value) { explored = value; }

// создаём объект конкретного ресурса и храним его через базовый класс
// если ресурс уже есть, увеличиваем его запас; иначе создаём объект нужного типа
void CelestialBody::addResource(const std::string& type, int value) {
    auto it = resources.find(type);
    if (it == resources.end()) {
        std::unique_ptr<Resource> resource;
        if (type == "Crystal") resource = std::make_unique<Crystal>();
        else if (type == "Gem") resource = std::make_unique<Gem>();
        else if (type == "Ore") resource = std::make_unique<Ore>();
        else if (type == "Fuel") resource = std::make_unique<Fuel>();
        else if (type == "Gold") resource = std::make_unique<Gold>();
        else return;
        it = resources.emplace(type, std::move(resource)).first;
    }
    it->second->setAmount(it->second->getAmount() + value);
}

// если объект не содержит запрошенный ресурс, возвращаем ноль
int CelestialBody::getResource(const std::string& type) const {
    auto it = resources.find(type);
    return it == resources.end() ? 0 : it->second->getAmount();
}

// создаёт и настраивает новый объект
Asteroid::Asteroid(int id, const std::string& name, double x, double y)
    : CelestialBody(id, name, x, y) {}

// возвращает тип объекта
std::string Asteroid::getType() const { return "Астероид"; }
// проверяет возможность размещения корпорации
bool Asteroid::canBuildCorporation() const { return false; }

// добывает доступные ресурсы объекта
std::map<std::string, int> Asteroid::extractResources(int multiplier) {
    std::map<std::string, int> extracted;
    for (const auto& type : {"Crystal", "Gem", "Ore", "Fuel"}) {
        int amount = std::min(getResource(type), 3 * multiplier);
        if (amount > 0) {
            extracted[type] = amount;
            addResource(type, -amount);
        }
    }
    return extracted;
}
