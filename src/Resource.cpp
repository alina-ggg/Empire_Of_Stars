#include "Resource.h"

#include <algorithm>

// при создании ресурса не допускаем отрицательное количество
Resource::Resource(int value)
    : amount(std::max(0, value)) {
}

// возвращаем текущее количество ресурса
int Resource::getAmount() const {
    return amount;
}

// устанавливаем новое количество и защищаем объект от отрицательного значения
void Resource::setAmount(int value) {
    amount = std::max(0, value);
}

// каждый производный класс возвращает собственное название ресурса
std::string Crystal::getName() const {
    return "Crystal";
}

// возвращает название объекта
std::string Gem::getName() const {
    return "Gem";
}

// возвращает название объекта
std::string Ore::getName() const {
    return "Ore";
}

// возвращает название объекта
std::string Fuel::getName() const {
    return "Fuel";
}

// возвращает название объекта
std::string Gold::getName() const {
    return "Gold";
}
