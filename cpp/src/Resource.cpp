// базовая реализация ресурсов
#include "Resource.h"

Resource::Resource(int amount, double basePrice)
    : amount(amount), basePrice(basePrice) {}

Resource::~Resource() {}

int Resource::getAmount() const {
    return amount;
}

void Resource::setAmount(int amount) {
    this->amount = amount;
}

double Resource::getBasePrice() const {
    return basePrice;
}

double Resource::getValue() const {
    return amount * basePrice;
}