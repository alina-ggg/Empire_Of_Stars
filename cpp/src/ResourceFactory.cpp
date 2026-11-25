// создание ресурсов по имени типа
#include "ResourceFactory.h"
#include "Gold.h"
#include "Crystal.h"
#include "Gem.h"
#include "Ore.h"
#include "Fuel.h"

Resource* ResourceFactory::create(const std::string& type, int amount) {
    if (type == "Gold") {
        return new Gold(amount);
    } else if (type == "Crystal") {
        return new Crystal(amount);
    } else if (type == "Gem") {
        return new Gem(amount);
    } else if (type == "Ore") {
        return new Ore(amount);
    } else if (type == "Fuel") {
        return new Fuel(amount);
    }
    return nullptr;  // Неизвестный ресурс
}