// базовый класс ресурсов
#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

class Resource {
protected:
    int amount;
    double basePrice;

public:
    Resource(int amount, double basePrice);
    virtual ~Resource();

    // виртуальные функции
    virtual std::string getName() const = 0;
    virtual Resource* clone() const = 0;

    // Геттеры и сеттеры
    int getAmount() const;
    void setAmount(int amount);
    double getBasePrice() const;
    double getValue() const;  // amount * basePrice
};

#endif // RESOURCE_H