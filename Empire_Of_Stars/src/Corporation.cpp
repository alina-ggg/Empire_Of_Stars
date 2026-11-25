#include "Corporation.h"
#include "Empire.h"
#include "Galaxy.h"
#include "CelestialBody.h"
#include "Route.h"
#include <algorithm>
#include <cmath>
#include <iostream>


// реализация корпораций: строительство маршрутов, добыча, торговля и создание через фабрику
Corporation::Corporation(int value,const std::string& title,double buildCost,
                         const std::map<std::string,int>& buildItems,double upgradeCost,
                         const std::map<std::string,int>& upgradeItems)
    :level(value),name(title),homePlanetId(-1),buildMoney(buildCost),
     buildResources(buildItems),upgradeBaseMoney(upgradeCost),upgradeResources(upgradeItems){}
// возвращает текущий уровень
int Corporation::getLevel()const{return level;
}
// возвращает название объекта
const std::string& Corporation::getName()const{return name;
}
// возвращает значение поля объекта
int Corporation::getHomePlanetId()const{return homePlanetId;
}
// изменяет значение поля объекта
void Corporation::setHomePlanetId(int id){homePlanetId=id;
}
// возвращает значение поля объекта
double Corporation::getBuildMoney()const{return buildMoney;
}
// возвращает значение поля объекта
std::map<std::string,int> Corporation::getBuildResources()const{return buildResources;
}
// возвращает значение поля объекта
double Corporation::getUpgradeMoney()const{return upgradeBaseMoney*level;
}
// возвращает значение поля объекта
std::map<std::string,int> Corporation::getUpgradeResources()const{auto result=upgradeResources;
for(auto& item:result)item.second*=level;
return result;
}
// повышает уровень объекта на единицу
void Corporation::upgrade(){++level;
}

// создаёт и настраивает новый объект
LogisticsCompany::LogisticsCompany(int l):Corporation(l,"Логистика",200,{{"Crystal",2}},100,{{"Crystal",1}}){}
// возвращает тип объекта
std::string LogisticsCompany::getType()const{return "Логистика";
}
// возвращает описание объекта
std::string LogisticsCompany::getDescription()const{return "создаёт и улучшает маршруты";
}
// выполняет действие корпорации при переходе хода
void LogisticsCompany::applyTurn(Empire&,Galaxy&,int) {}

// создаёт маршрут к выбранному объекту
bool LogisticsCompany::buildRoute(Galaxy& galaxy, Empire& empire, int targetId) {
    auto start = galaxy.findBody(homePlanetId);
    auto target = galaxy.findBody(targetId);
    if (!start || !target || targetId == homePlanetId ||
        galaxy.findRouteBetween(homePlanetId, targetId)) return false;

    double dx = start->getX() - target->getX();
    double dy = start->getY() - target->getY();
    double distance = std::sqrt(dx * dx + dy * dy);
    double cost = distance * 2.0;
    if (!empire.spendMoney(cost)) return false;
    return galaxy.addRoute(homePlanetId, targetId, distance);
}

// улучшает выбранный маршрут
bool LogisticsCompany::upgradeRoute(Galaxy& galaxy, Empire& empire, int routeId) {
    auto route = galaxy.findRoute(routeId);
    if (!route || (route->getFromId() != homePlanetId &&
                   route->getToId() != homePlanetId)) return false;
    if (!empire.spendMoney(route->getUpgradeCost())) return false;
    route->upgrade();
    return true;
}

// создаёт и настраивает новый объект
MinerCompany::MinerCompany(int l):Corporation(l,"Добыча",150,{{"Ore",2}},100,{{"Ore",1}}){}
// возвращает тип объекта
std::string MinerCompany::getType()const{return "Добыча";
}
// возвращает описание объекта
std::string MinerCompany::getDescription()const{return "добывает ресурсы планеты и связанных астероидов";
}
// выполняет действие корпорации при переходе хода
void MinerCompany::applyTurn(Empire& empire,Galaxy& galaxy,int homeId) {
    auto home=galaxy.findBody(homeId);
    if(!home)return;
    auto local=home->extractResources(level);
    for(const auto& item:local) {
        if(item.first=="Gold")empire.addMoney(item.second);
        else empire.addResource(item.first,item.second);
    }
    // сначала оплачиваем перевозку, только потом извлекаем ресурсы астероида
    for(Route* route:galaxy.routesFrom(homeId)) {
        int otherId=route->getFromId()==homeId?route->getToId():route->getFromId();
        auto body=galaxy.findBody(otherId);
        if(!body||body->getType()!="Астероид")continue;
        bool hasResources=body->getResource("Crystal")>0||body->getResource("Gem")>0||
                          body->getResource("Ore")>0||body->getResource("Fuel")>0;
        if(!hasResources)continue;
        double cost=route->getTransportCost();
        if(!empire.spendMoney(cost)) {
            std::cout<<"  маршрут "<<route->getId()<<": не хватает денег на перевозку, добыча пропущена\n";
            continue;
        }
        auto cargo=body->extractResources(level);
        for(const auto& item:cargo)empire.addResource(item.first,item.second);
        if(!cargo.empty())std::cout<<"  астероид "<<body->getName()<<": перевозка "<<cost<<" у.е., ресурсы доставлены\n";
    }
}

// создаёт и настраивает новый объект
TechTrader::TechTrader(int l):Corporation(l,"Торговля",300,{{"Gem",2}},150,{{"Gem",1}}){}
// возвращает тип объекта
std::string TechTrader::getType()const{return "Торговля";
}
// возвращает описание объекта
std::string TechTrader::getDescription()const{return "покупает и продаёт ресурсы";
}
// выполняет действие корпорации при переходе хода
void TechTrader::applyTurn(Empire&,Galaxy&,int) {}

// рассчитывает цену покупки или продажи ресурса
double TechTrader::getPrice(const std::string& resource, int traderCount, bool buying) const {
    double basePrice = 0;
    if (resource == "Crystal") basePrice = 20;
    else if (resource == "Gem") basePrice = 35;
    else if (resource == "Ore") basePrice = 12;
    else if (resource == "Fuel") basePrice = 8;
    if (basePrice == 0 || traderCount <= 0) return 0;

    double factor = 1.0 + 0.1 * (traderCount - 1);
    return buying ? basePrice / factor : basePrice * factor;
}

// покупает указанное количество ресурса
bool TechTrader::buyResource(Empire& empire, const std::string& resource,
                             int amount, int traderCount) {
    if (amount <= 0) return false;
    double total = getPrice(resource, traderCount, true) * amount;
    if (total <= 0 || !empire.spendMoney(total)) return false;
    empire.addResource(resource, amount);
    return true;
}

// продаёт указанное количество ресурса
bool TechTrader::sellResource(Empire& empire, const std::string& resource,
                              int amount, int traderCount) {
    if (amount <= 0) return false;
    double total = getPrice(resource, traderCount, false) * amount;
    if (total <= 0 || !empire.spendResource(resource, amount)) return false;
    empire.addMoney(total);
    return true;
}

// простая фабрика скрывает от игрового цикла детали создания конкретных корпораций
std::unique_ptr<Corporation> CorporationFactory::create(const std::string& type) {
    if(type=="1"||type=="Logistics"||type=="Логистика")return std::make_unique<LogisticsCompany>();
    if(type=="2"||type=="Miner"||type=="Добыча")return std::make_unique<MinerCompany>();
    if(type=="3"||type=="Trader"||type=="Торговля")return std::make_unique<TechTrader>();
    return nullptr;
}
