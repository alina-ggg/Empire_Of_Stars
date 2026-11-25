#ifndef EMPIRE_OF_STARS_EMPIRE_H
#define EMPIRE_OF_STARS_EMPIRE_H

#include <map>
#include <string>
#include <vector>
#include "Corporation.h"

// класс empire хранит общие ресурсы игрока, казну и список принадлежащих ему планет
class Planet;
// класс empire описывает отдельную сущность игровой модели
class Empire {
private:
    double treasury;
    std::map<std::string,int> warehouse;
    std::vector<Planet*> planets;
    Planet* currentPlanet;
public:
// создаёт и настраивает новый объект
    explicit Empire(double money=700);
// возвращает текущий размер казны
    double getTreasury() const;
// пытается списать деньги из казны
    bool spendMoney(double amount);
// добавляет деньги в казну
    void addMoney(double amount);
// возвращает значение поля объекта
    int getResourceAmount(const std::string& type) const;
// добавляет ресурс на склад или объект
    void addResource(const std::string& type,int amount);
// списывает ресурс при наличии нужного количества
    bool spendResource(const std::string& type,int amount);
// проверяет достаточность денег и ресурсов
    bool canAfford(double money,const std::map<std::string,int>& resources) const;
// одновременно оплачивает деньги и ресурсы
    bool pay(double money,const std::map<std::string,int>& resources);
// подсчитывает торговые корпорации империи
    int countTraders() const;
// добавляет планету во владения империи
    void addPlanet(Planet* planet);
// возвращает список планет империи
    const std::vector<Planet*>& getPlanets() const;
// возвращает текущую планету
    Planet* getCurrentPlanet() const;
// переключает игрока на другую доступную планету
    bool switchPlanet(int id);
};

#endif // empire_of_stars_empire_h
