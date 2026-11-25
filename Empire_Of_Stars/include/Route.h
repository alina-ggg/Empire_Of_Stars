#ifndef EMPIRE_OF_STARS_ROUTE_H
#define EMPIRE_OF_STARS_ROUTE_H


// класс route хранит параметры одного транспортного маршрута между двумя объектами
class Route {
private:
    int id, fromId, toId, level;
    double distance;
public:
// создаёт и настраивает новый объект
    Route(int id,int from,int to,double distance);
// возвращает идентификатор объекта
    int getId() const;
// возвращает значение поля объекта
 int getFromId() const;
// возвращает значение поля объекта
 int getToId() const;
// возвращает текущий уровень
    int getLevel() const;
// возвращает расстояние
 double getDistance() const;
// рассчитывает стоимость улучшения маршрута
    double getUpgradeCost() const;
// рассчитывает стоимость перевозки по маршруту
 double getTransportCost() const;
// повышает уровень объекта на единицу
    void upgrade();
};

#endif // empire_of_stars_route_h
