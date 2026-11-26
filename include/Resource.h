#ifndef EMPIRE_OF_STARS_RESOURCE_H
#define EMPIRE_OF_STARS_RESOURCE_H

#include <string>

// базовый класс для всех ресурсов в игре
// конкретные виды ресурсов отличаются названием, но хранят количество одинаково
class Resource {
protected:
    int amount;

public:
    explicit Resource(int amount = 0);
    virtual ~Resource() = default;

    // виртуальный метод позволяет получить название через указатель resource*
    virtual std::string getName() const = 0;

// количество ресурса
    int getAmount() const;
    void setAmount(int value);
};

// конкретные типы ресурсов
class Crystal : public Resource {
public:
    using Resource::Resource;
    std::string getName() const override;
};

class Gem : public Resource {
public:
    using Resource::Resource;
    std::string getName() const override;
};

class Ore : public Resource {
public:
    using Resource::Resource;
    std::string getName() const override;
};

class Fuel : public Resource {
public:
    using Resource::Resource;
    std::string getName() const override;
};

class Gold : public Resource {
public:
    using Resource::Resource;
    std::string getName() const override;
};

#endif
