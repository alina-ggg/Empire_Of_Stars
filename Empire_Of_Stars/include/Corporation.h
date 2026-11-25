#ifndef EMPIRE_OF_STARS_CORPORATION_H
#define EMPIRE_OF_STARS_CORPORATION_H

#include <map>
#include <memory>
#include <string>

// здесь объявлены базовый класс корпорации, три конкретные корпорации и простая фабрика
class Empire;
// класс galaxy описывает отдельную сущность игровой модели
 class Galaxy;

// базовый класс корпораций
class Corporation {
protected:
    int level;
    std::string name;
    int homePlanetId;
    double buildMoney;
    std::map<std::string,int> buildResources;
    double upgradeBaseMoney;
    std::map<std::string,int> upgradeResources;
    Corporation(int level, const std::string& name, double buildMoney,
                const std::map<std::string,int>& buildResources,
                double upgradeBaseMoney, const std::map<std::string,int>& upgradeResources);
public:
// освобождает ресурсы объекта при удалении
    virtual ~Corporation() = default;
// возвращает тип объекта
    virtual std::string getType() const = 0;
// возвращает описание объекта
    virtual std::string getDescription() const = 0;
// выполняет действие корпорации при переходе хода
    virtual void applyTurn(Empire& empire, Galaxy& galaxy, int homePlanetId) = 0;
// возвращает текущий уровень
    int getLevel() const;
// возвращает название объекта
    const std::string& getName() const;
// возвращает значение поля объекта
    int getHomePlanetId() const;
// изменяет значение поля объекта
    void setHomePlanetId(int id);
// возвращает значение поля объекта
    double getBuildMoney() const;
// возвращает значение поля объекта
    std::map<std::string,int> getBuildResources() const;
// возвращает значение поля объекта
    double getUpgradeMoney() const;
// возвращает значение поля объекта
    std::map<std::string,int> getUpgradeResources() const;
// повышает уровень объекта на единицу
    void upgrade();
};
// класс logisticscompany описывает отдельную сущность игровой модели
class LogisticsCompany : public Corporation {
public:
// создаёт и настраивает новый объект
    explicit LogisticsCompany(int level=1);
// возвращает тип объекта
    std::string getType() const override;
// возвращает описание объекта
    std::string getDescription() const override;
// выполняет действие корпорации при переходе хода
    void applyTurn(Empire&,Galaxy&,int) override;
// создаёт маршрут к выбранному объекту
    bool buildRoute(Galaxy& galaxy, Empire& empire, int targetId);
// улучшает выбранный маршрут
    bool upgradeRoute(Galaxy& galaxy, Empire& empire, int routeId);
};
// класс minercompany описывает отдельную сущность игровой модели
class MinerCompany : public Corporation {
public:
// создаёт и настраивает новый объект
    explicit MinerCompany(int level=1);
// возвращает тип объекта
    std::string getType() const override;
// возвращает описание объекта
    std::string getDescription() const override;
// выполняет действие корпорации при переходе хода
    void applyTurn(Empire&,Galaxy&,int) override;
};
// класс techtrader описывает отдельную сущность игровой модели
class TechTrader : public Corporation {
public:
// создаёт и настраивает новый объект
    explicit TechTrader(int level=1);
// возвращает тип объекта
    std::string getType() const override;
// возвращает описание объекта
    std::string getDescription() const override;
// выполняет действие корпорации при переходе хода
    void applyTurn(Empire&,Galaxy&,int) override;
// рассчитывает цену покупки или продажи ресурса
    double getPrice(const std::string& resource, int traderCount, bool buying) const;
// покупает указанное количество ресурса
    bool buyResource(Empire& empire, const std::string& resource, int amount, int traderCount);
// продаёт указанное количество ресурса
    bool sellResource(Empire& empire, const std::string& resource, int amount, int traderCount);
};
// класс corporationfactory описывает отдельную сущность игровой модели
class CorporationFactory {
public:
// создаёт объект нужного типа через простую фабрику
    static std::unique_ptr<Corporation> create(const std::string& type);
};

#endif // empire_of_stars_corporation_h
