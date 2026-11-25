#ifndef CONSOLE_RENDERER_H
#define CONSOLE_RENDERER_H

#include "Galaxy.h"
#include "Empire.h"
#include <string>

class ConsoleRenderer {
private:
    int width;
    int height;
    
    // Масштабирование координат в символы карты
    int scaleX(double x);
    int scaleY(double y);
    
    void drawBorder();
    void drawHeader(Empire* empire, int currentTurn, int maxTurns, double targetMoney);
    void drawMap(Galaxy* galaxy, Empire* empire);
    void drawFooter(Empire* empire);
    void drawRoutes(Galaxy* galaxy, char** grid);

public:
    ConsoleRenderer(int width = 80, int height = 24);
    
    void render(Galaxy* galaxy, Empire* empire, 
                int currentTurn, int maxTurns, double targetMoney);
    void clear();
};

#endif // CONSOLE_RENDERER_H