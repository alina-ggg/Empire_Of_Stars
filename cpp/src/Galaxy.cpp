// граф: добавление объектов,поиск маршрутов, связность
#include "Galaxy.h"
#include "Route.h"
#include <iostream>

Galaxy::Galaxy() {}

Galaxy::~Galaxy() {
    for (CelestialBody* body : bodies) {
        delete body;
    }
    bodies.clear();
    
    for (Route* route : routes) {
        delete route;
    }
    routes.clear();
}

void Galaxy::addBody(CelestialBody* body) {
    bodies.push_back(body);
}

void Galaxy::addRoute(Route* route) {
    routes.push_back(route);
}

std::vector<CelestialBody*> Galaxy::getBodies() const {
    return bodies;
}

std::vector<Route*> Galaxy::getRoutes() const {
    return routes;
}

CelestialBody* Galaxy::findBody(int id) const {
    for (CelestialBody* body : bodies) {
        if (body->getId() == id) {
            return body;
        }
    }
    return nullptr;
}

Route* Galaxy::findRoute(int id) const {
    for (Route* route : routes) {
        if (route->getId() == id) {
            return route;
        }
    }
    return nullptr;
}