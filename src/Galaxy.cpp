#include "Galaxy.h"
#include <queue>
#include <set>


// реализация хранения объектов галактики и поиска маршрутов между ними
Galaxy::Galaxy() : nextRouteId(1) {}

// добавляет космический объект в галактику
CelestialBody* Galaxy::addBody(std::unique_ptr<CelestialBody> body) {
    auto result = body.get();
    bodies.push_back(std::move(body));
    return result;
}

// добавляет новый маршрут в галактику
bool Galaxy::addRoute(int from, int to, double distance) {
    if (from == to || distance <= 0 || !findBody(from) || !findBody(to) ||
        findRouteBetween(from, to)) {
        return false;
    }
    routes.push_back(std::make_unique<Route>(nextRouteId++, from, to, distance));
    findBody(from)->setExplored(true);
    findBody(to)->setExplored(true);
    return true;
}

// ищет космический объект по идентификатору
CelestialBody* Galaxy::findBody(int id) const {
    for (const auto& body : bodies) {
        if (body->getId() == id) return body.get();
    }
    return nullptr;
}

Route* Galaxy::findRoute(int id) const {
    for (const auto& route : routes) {
        if (route->getId() == id) return route.get();
    }
    return nullptr;
}

Route* Galaxy::findRouteBetween(int first, int second) const {
    for (const auto& route : routes) {
        bool direct = route->getFromId() == first && route->getToId() == second;
        bool reverse = route->getFromId() == second && route->getToId() == first;
        if (direct || reverse) return route.get();
    }
    return nullptr;
}

std::vector<CelestialBody*> Galaxy::getBodies() const {
    std::vector<CelestialBody*> result;
    for (const auto& body : bodies) result.push_back(body.get());
    return result;
}

std::vector<Route*> Galaxy::getRoutes() const {
    std::vector<Route*> result;
    for (const auto& route : routes) result.push_back(route.get());
    return result;
}

// возвращает маршруты, связанные с указанным объектом
std::vector<Route*> Galaxy::routesFrom(int bodyId) const {
    std::vector<Route*> result;
    for (const auto& route : routes) {
        if (route->getFromId() == bodyId || route->getToId() == bodyId) {
            result.push_back(route.get());
        }
    }
    return result;
}

// поиск пути в графе методом обхода в ширину
// bfs проверяет, существует ли цепочка маршрутов между двумя объектами
bool Galaxy::hasPath(int from, int to) const {
    // в очереди хранятся объекты, соседей которых ещё нужно проверить
    std::queue<int> pending;
    std::set<int> visited;
    pending.push(from);
    visited.insert(from);

    while (!pending.empty()) {
        int current = pending.front();
        pending.pop();
        if (current == to) return true;

        for (auto route : routesFrom(current)) {
            int next = route->getFromId() == current
                           ? route->getToId() : route->getFromId();
            if (visited.insert(next).second) pending.push(next);
        }
    }
    return false;
}
