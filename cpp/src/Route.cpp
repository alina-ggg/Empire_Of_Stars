#include "Route.h"

Route::Route(int id, int fromId, int toId, double distance)
    : id(id), fromId(fromId), toId(toId), distance(distance), level(1) {}

Route::~Route() {}

int Route::getId() const { return id; }
int Route::getFromId() const { return fromId; }
int Route::getToId() const { return toId; }
double Route::getDistance() const { return distance; }
int Route::getLevel() const { return level; }

double Route::getUpgradeCost() const {
    return 100.0 * level;
}

// Стоимость топлива = расстояние / уровень маршрута
double Route::getFuelCost() const {
    return distance / level;
}

void Route::upgrade() {
    level++;
}