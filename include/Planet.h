#ifndef EMPIRE_OF_STARS_PLANET_H
#define EMPIRE_OF_STARS_PLANET_H

#include "CelestialBody.h"
#include <map>
#include <memory>
#include <vector>

// расширяет космический объект: на планете можно размещать корпорации
class Corporation;
class Planet : public CelestialBody {
private:
    std::vector<std::unique_ptr<Corporation>> corporations;
    std::map<int,bool> corporationActionUsed;
public:
    Planet(int id,const std::string& name,double x,double y);
    std::string getType() const override;
    bool canBuildCorporation() const override;
// добывает доступные ресурсы объекта
    std::map<std::string,int> extractResources(int multiplier) override;
// проверяет указанное состояние или условие
    bool hasCorporation(const std::string& type) const;
    Corporation* getCorporation(const std::string& type) const;
    bool addCorporation(std::unique_ptr<Corporation> corporation);
    const std::vector<std::unique_ptr<Corporation>>& getCorporations() const;
    bool actionUsed(int turn) const;
    void markActionUsed(int turn);
};

#endif
