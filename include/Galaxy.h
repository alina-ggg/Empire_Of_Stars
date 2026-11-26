#ifndef EMPIRE_OF_STARS_GALAXY_H
#define EMPIRE_OF_STARS_GALAXY_H

#include <memory>
#include <vector>
#include "CelestialBody.h"
#include "Route.h"

// все космические объекты и маршруты между ними
class Galaxy {
private:
    std::vector<std::unique_ptr<CelestialBody>> bodies;
    std::vector<std::unique_ptr<Route>> routes;
    int nextRouteId;
public:
// создаёт и настраивает новый объект
    Galaxy();
    CelestialBody* addBody(std::unique_ptr<CelestialBody> body);
    bool addRoute(int from,int to,double distance);
// ищет космический объект по идентификатору
    CelestialBody* findBody(int id) const;
    Route* findRoute(int id) const;
// ищет маршрут между двумя объектами
    Route* findRouteBetween(int a,int b) const;
// возвращает список космических объектов
    std::vector<CelestialBody*> getBodies() const;
    std::vector<Route*> getRoutes() const;
// возвращает маршруты, связанные с указанным объектом
    std::vector<Route*> routesFrom(int bodyId) const;
    bool hasPath(int from,int to) const;
};

#endif
