#ifndef EMPIRE_OF_STARS_PLANET_H
#define EMPIRE_OF_STARS_PLANET_H

#include "CelestialBody.h"
#include <map>
#include <memory>
#include <vector>

// класс planet расширяет космический объект: на планете можно размещать корпорации
class Corporation;
// класс planet описывает отдельную сущность игровой модели
class Planet : public CelestialBody {
private:
    std::vector<std::unique_ptr<Corporation>> corporations;
    std::map<int,bool> corporationActionUsed;
public:
// создаёт и настраивает новый объект
    Planet(int id,const std::string& name,double x,double y);
// возвращает тип объекта
    std::string getType() const override;
// проверяет возможность размещения корпорации
    bool canBuildCorporation() const override;
// добывает доступные ресурсы объекта
    std::map<std::string,int> extractResources(int multiplier) override;
// проверяет указанное состояние или условие
    bool hasCorporation(const std::string& type) const;
// ищет корпорацию по её типу
    Corporation* getCorporation(const std::string& type) const;
// выполняет часть логики игрового процесса
    bool addCorporation(std::unique_ptr<Corporation> corporation);
// возвращает список корпораций планеты
    const std::vector<std::unique_ptr<Corporation>>& getCorporations() const;
// проверяет, выполнялось ли действие в указанном ходу
    bool actionUsed(int turn) const;
// отмечает выполнение действия в текущем ходу
    void markActionUsed(int turn);
};

#endif // empire_of_stars_planet_h
