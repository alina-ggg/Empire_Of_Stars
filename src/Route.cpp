#include "Route.h"

// новый маршрут всегда начинается с первого уровня
Route::Route(int id, int from, int to, double distance)
    : id(id),
      fromId(from),
      toId(to),
      level(1),
      distance(distance) {
}

// методы ниже возвращают сохранённые характеристики маршрута
int Route::getId() const {
    return id;
}

// возвращает значение поля объекта
int Route::getFromId() const {
    return fromId;
}

// возвращает значение поля объекта
int Route::getToId() const {
    return toId;
}

// возвращает текущий уровень
int Route::getLevel() const {
    return level;
}

// возвращает расстояние
double Route::getDistance() const {
    return distance;
}

// чем выше уровень, тем дороже становится следующее улучшение
double Route::getUpgradeCost() const {
    return 50.0 * level;
}

// улучшение снижает цену перевозки по маршруту
// уровень учитывается в знаменателе, поэтому цена постепенно уменьшается
double Route::getTransportCost() const {
    return distance * 0.5 / (1.0 + 0.5 * (level - 1));
}

// увеличиваем уровень маршрута на единицу
void Route::upgrade() {
    ++level;
}
