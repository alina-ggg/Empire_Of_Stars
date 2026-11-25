#ifndef GALAXYGENERATOR_H
#define GALAXYGENERATOR_H

#include "Galaxy.h"
#include "Empire.h"

class GalaxyGenerator {
public:
    // Передаём указатели по ссылке, чтобы функция могла их создать
    static void generate(int numPlanets, int numAsteroids,
                         Galaxy*& galaxy, Empire*& empire);

private:
    static double randomDistance();
    static int randomResourceAmount();
};

#endif // GALAXYGENERATOR_H