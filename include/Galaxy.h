#ifndef EMPIRE_OF_STARS_GALAXY_H
#define EMPIRE_OF_STARS_GALAXY_H

#include <memory>
#include <vector>
#include "CelestialBody.h"
#include "Route.h"

// класс galaxy владеет всеми космическими объектами и маршрутами между ними
class Galaxy {
private:
    std::vector<std::unique_ptr<CelestialBody>> bodies;
    std::vector<std::unique_ptr<Route>> routes;
    int nextRouteId;
public:
// создаёт и настраивает новый объект
    Galaxy();
// добавляет космический объект в галактику
    CelestialBody* addBody(std::unique_ptr<CelestialBody> body);
// добавляет новый маршрут в галактику
    bool addRoute(int from,int to,double distance);
// ищет космический объект по идентификатору
    CelestialBody* findBody(int id) const;
// выполняет часть логики игрового процесса
    Route* findRoute(int id) const;
// ищет маршрут между двумя объектами
    Route* findRouteBetween(int a,int b) const;
// возвращает список космических объектов
    std::vector<CelestialBody*> getBodies() const;
// возвращает список маршрутов
    std::vector<Route*> getRoutes() const;
// возвращает маршруты, связанные с указанным объектом
    std::vector<Route*> routesFrom(int bodyId) const;
// проверяет наличие пути между объектами
    bool hasPath(int from,int to) const;
};

#endif // empire_of_stars_galaxy_h
