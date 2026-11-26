#include "Route.h"

// новый маршрут всегда начинается с первого уровня
Route::Route(int id, int from, int to, double distance)
    : id(id),
      fromId(from),
      toId(to),
      level(1),
      distance(distance) {
}

int Route::getId() const {
    return id;
}

int Route::getFromId() const {
    return fromId;
}

int Route::getToId() const {
    return toId;
}

int Route::getLevel() const {
    return level;
}

double Route::getDistance() const {
    return distance;
}

// чем выше уровень, тем дороже становится следующее улучшение
double Route::getUpgradeCost() const {
    return 50.0 * level;
}

// улучшение снижает цену перевозки по маршруту
double Route::getTransportCost() const {
    return distance * 0.5 / (1.0 + 0.5 * (level - 1));
}

void Route::upgrade() {
    ++level;
}
