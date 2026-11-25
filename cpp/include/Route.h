#ifndef ROUTE_H
#define ROUTE_H

class Route {
private:
    int id;
    int fromId;
    int toId;
    double distance;
    int level;

public:
    Route(int id, int fromId, int toId, double distance);
    ~Route();

    int getId() const;
    int getFromId() const;
    int getToId() const;
    double getDistance() const;
    int getLevel() const;
    double getUpgradeCost() const;
    double getFuelCost() const;  // ← ДОБАВИТЬ
    void upgrade();
};

#endif // ROUTE_H