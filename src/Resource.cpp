#include "Resource.h"

#include <algorithm>

// при создании ресурса не допускаем отрицательное количество
Resource::Resource(int value)
    : amount(std::max(0, value)) {
}

// текущее количество ресурса
int Resource::getAmount() const {
    return amount;
}

void Resource::setAmount(int value) {
    amount = std::max(0, value);
}

std::string Crystal::getName() const {
    return "Crystal";
}

std::string Gem::getName() const {
    return "Gem";
}

std::string Ore::getName() const {
    return "Ore";
}

std::string Fuel::getName() const {
    return "Fuel";
}

std::string Gold::getName() const {
    return "Gold";
}
