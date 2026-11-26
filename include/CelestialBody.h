#ifndef EMPIRE_OF_STARS_CELESTIALBODY_H
#define EMPIRE_OF_STARS_CELESTIALBODY_H

#include <map>
#include <memory>
#include <string>
#include "Resource.h"

// общий базовый класс планет и астероидов
class CelestialBody {
private:
    int id;
    std::string name;
    double x, y;
    bool explored;
    std::map<std::string, std::unique_ptr<Resource>> resources;
public:
// создаёт и настраивает новый объект
    CelestialBody(int id, const std::string& name, double x, double y);
// освобождает ресурсы объекта при удалении
    virtual ~CelestialBody() = default;
    virtual std::string getType() const = 0;
// проверяет возможность размещения корпорации
    virtual bool canBuildCorporation() const = 0;
// добывает доступные ресурсы объекта
    virtual std::map<std::string, int> extractResources(int multiplier) = 0;
    int getId() const;
    const std::string& getName() const;
    double getX() const;
    double getY() const;
// проверяет, исследован ли объект
    bool isExplored() const;
// изменяет признак исследования объекта
    void setExplored(bool value);
// добавляет ресурс на склад или объект
    void addResource(const std::string& type, int amount);
    int getResource(const std::string& type) const;
};

class Asteroid : public CelestialBody {
public:
// создаёт и настраивает новый объект
    Asteroid(int id, const std::string& name, double x, double y);
    std::string getType() const override;
// проверяет возможность размещения корпорации
    bool canBuildCorporation() const override;
// добывает доступные ресурсы объекта
    std::map<std::string, int> extractResources(int multiplier) override;
};

#endif
