// фабрика корпораций
#ifndef CORPORATIONFACTORY_H
#define CORPORATIONFACTORY_H

#include "Corporation.h"
#include <string>

// Паттерн Factory Method — создаёт корпорацию по строке-типу
class CorporationFactory {
public:
    static Corporation* create(const std::string& type, int level = 1);
};

#endif // CORPORATIONFACTORY_H