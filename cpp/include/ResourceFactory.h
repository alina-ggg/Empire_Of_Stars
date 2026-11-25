// фабрика ресурсов
#ifndef RESOURCEFACTORY_H
#define RESOURCEFACTORY_H

#include "Resource.h"
#include <string>

class ResourceFactory {
public:
    static Resource* create(const std::string& type, int amount);
};

#endif // RESOURCEFACTORY_H