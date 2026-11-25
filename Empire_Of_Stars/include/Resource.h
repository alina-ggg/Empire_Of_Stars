#ifndef EMPIRE_OF_STARS_RESOURCE_H
#define EMPIRE_OF_STARS_RESOURCE_H

#include <string>

// базовый класс для всех ресурсов в игре
// конкретные виды ресурсов отличаются названием, но хранят количество одинаково
class Resource {
protected:
    int amount;

public:
// создаёт и настраивает новый объект
    explicit Resource(int amount = 0);
// освобождает ресурсы объекта при удалении
    virtual ~Resource() = default;

    // виртуальный метод позволяет получить название через указатель resource*
    virtual std::string getName() const = 0;

// возвращает количество ресурса
    int getAmount() const;
// устанавливает количество ресурса
    void setAmount(int value);
};

// конкретные типы ресурсов. конструктор базового класса используется повторно
class Crystal : public Resource {
public:
    using Resource::Resource;
// возвращает название объекта
    std::string getName() const override;
};

// класс gem описывает отдельную сущность игровой модели
class Gem : public Resource {
public:
    using Resource::Resource;
// возвращает название объекта
    std::string getName() const override;
};

// класс ore описывает отдельную сущность игровой модели
class Ore : public Resource {
public:
    using Resource::Resource;
// возвращает название объекта
    std::string getName() const override;
};

// класс fuel описывает отдельную сущность игровой модели
class Fuel : public Resource {
public:
    using Resource::Resource;
// возвращает название объекта
    std::string getName() const override;
};

// класс gold описывает отдельную сущность игровой модели
class Gold : public Resource {
public:
    using Resource::Resource;
// возвращает название объекта
    std::string getName() const override;
};

#endif // empire_of_stars_resource_h
