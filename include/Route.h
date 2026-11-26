#ifndef EMPIRE_OF_STARS_ROUTE_H
#define EMPIRE_OF_STARS_ROUTE_H


// параметры одного транспортного маршрута между двумя объектами
class Route {
private:
    int id, fromId, toId, level;
    double distance;
public:
    Route(int id,int from,int to,double distance);
    int getId() const;
 int getFromId() const;
 int getToId() const;
    int getLevel() const;
 double getDistance() const;
    double getUpgradeCost() const;
 double getTransportCost() const;
    void upgrade();
};

#endif
