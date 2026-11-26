#ifndef EMPIRE_OF_STARS_EMPIRE_H
#define EMPIRE_OF_STARS_EMPIRE_H

#include <map>
#include <string>
#include <vector>
#include "Corporation.h"

// хранит общие ресурсы игрока, казну и список принадлежащих ему планет
class Planet;
class Empire {
private:
    double treasury;
    std::map<std::string,int> warehouse;
    std::vector<Planet*> planets;
    Planet* currentPlanet;
public:
// создаёт и настраивает новый объект
    explicit Empire(double money=700);
// текущий размер казны
    double getTreasury() const;
    bool spendMoney(double amount);
    void addMoney(double amount);
    int getResourceAmount(const std::string& type) const;
    void addResource(const std::string& type,int amount);
    bool spendResource(const std::string& type,int amount);
// проверяет достаточность денег и ресурсов
    bool canAfford(double money,const std::map<std::string,int>& resources) const;
// одновременно оплачивает деньги и ресурсы
    bool pay(double money,const std::map<std::string,int>& resources);
// подсчитывает торговые корпорации империи
    int countTraders() const;
    void addPlanet(Planet* planet);
// список планет империи
    const std::vector<Planet*>& getPlanets() const;
// текущая планета
    Planet* getCurrentPlanet() const;
// переключает игрока на другую доступную планету
    bool switchPlanet(int id);
};

#endif
