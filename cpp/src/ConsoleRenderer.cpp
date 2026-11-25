#include "ConsoleRenderer.h"
#include "CelestialBody.h"
#include "Planet.h"
#include "Asteroid.h"
#include "Route.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

ConsoleRenderer::ConsoleRenderer(int width, int height)
    : width(width), height(height) {}

int ConsoleRenderer::scaleX(double x) {
    // Масштабируем координаты (0..800) в (1..width-2)
    return (int)(x / 800.0 * (width - 2)) + 1;
}

int ConsoleRenderer::scaleY(double y) {
    // Масштабируем координаты (0..600) в (1..height-4)
    // -4 потому что верхняя панель занимает 2 строки, нижняя - 2
    return (int)(y / 600.0 * (height - 4)) + 1;
}

void ConsoleRenderer::drawBorder() {
    // Верхняя граница
    std::cout << "+";
    for (int i = 0; i < width - 2; ++i) std::cout << "-";
    std::cout << "+" << std::endl;
}

void ConsoleRenderer::drawHeader(Empire* empire, int currentTurn, 
                                  int maxTurns, double targetMoney) {
    std::cout << "| Ход: " << currentTurn << "/" << maxTurns
              << " | Казна: " << (int)empire->getTreasury() << "/" 
              << (int)targetMoney << " у.е."
              << " | Планета: " << empire->getCurrentPlanet()->getName()
              << std::string(width - 60, ' ') << "|" << std::endl;
    
    std::cout << "|";
    for (int i = 0; i < width - 2; ++i) std::cout << "-";
    std::cout << "|" << std::endl;
}

void ConsoleRenderer::drawRoutes(Galaxy* galaxy, char** grid) {
    for (Route* route : galaxy->getRoutes()) {
        CelestialBody* from = galaxy->findBody(route->getFromId());
        CelestialBody* to = galaxy->findBody(route->getToId());
        if (!from || !to) continue;

        int x1 = scaleX(from->getCoordinates().first);
        int y1 = scaleY(from->getCoordinates().second);
        int x2 = scaleX(to->getCoordinates().first);
        int y2 = scaleY(to->getCoordinates().second);

        // Рисуем линию Брезенхэма
        int dx = std::abs(x2 - x1);
        int dy = std::abs(y2 - y1);
        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;
        int err = dx - dy;

        while (true) {
            if (y1 >= 1 && y1 < height - 2 && x1 >= 1 && x1 < width - 1) {
                if (grid[y1][x1] == ' ') {
                    grid[y1][x1] = '.';
                }
            }
            if (x1 == x2 && y1 == y2) break;
            int e2 = 2 * err;
            if (e2 > -dy) { err -= dy; x1 += sx; }
            if (e2 < dx) { err += dx; y1 += sy; }
        }
    }
}

void ConsoleRenderer::drawMap(Galaxy* galaxy, Empire* empire) {
    // Создаём пустую сетку
    std::vector<std::vector<char>> grid(height, std::vector<char>(width, ' '));

    // Рисуем маршруты
    for (Route* route : galaxy->getRoutes()) {
        CelestialBody* from = galaxy->findBody(route->getFromId());
        CelestialBody* to = galaxy->findBody(route->getToId());
        if (!from || !to) continue;

        int x1 = scaleX(from->getCoordinates().first);
        int y1 = scaleY(from->getCoordinates().second);
        int x2 = scaleX(to->getCoordinates().first);
        int y2 = scaleY(to->getCoordinates().second);

        int dx = std::abs(x2 - x1);
        int dy = std::abs(y2 - y1);
        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;
        int err = dx - dy;

        while (true) {
            if (y1 >= 1 && y1 < height - 2 && x1 >= 1 && x1 < width - 1) {
                if (grid[y1][x1] == ' ') {
                    grid[y1][x1] = '.';
                }
            }
            if (x1 == x2 && y1 == y2) break;
            int e2 = 2 * err;
            if (e2 > -dy) { err -= dy; x1 += sx; }
            if (e2 < dx) { err += dx; y1 += sy; }
        }
    }

    // Рисуем объекты
    Planet* currentPlanet = empire->getCurrentPlanet();
    for (CelestialBody* body : galaxy->getBodies()) {
        int x = scaleX(body->getCoordinates().first);
        int y = scaleY(body->getCoordinates().second);
        
        if (y < 1 || y >= height - 2 || x < 1 || x >= width - 1) continue;

        if (body->getType() == "Planet") {
            bool owned = false;
            for (Planet* p : empire->getOwnedPlanets()) {
                if (p->getId() == body->getId()) { owned = true; break; }
            }
            
            if (body == currentPlanet) {
                grid[y][x] = '@';  // Текущая планета
            } else if (owned) {
                grid[y][x] = 'O';  // Своя планета
            } else {
                grid[y][x] = 'o';  // Чужая планета
            }
        } 
        else if (body->getType() == "Asteroid") {
            grid[y][x] = '*';  // Астероид
        }
    }

    // Выводим карту
    for (int y = 1; y < height - 2; ++y) {
        std::cout << "|";
        for (int x = 1; x < width - 1; ++x) {
            std::cout << grid[y][x];
        }
        std::cout << "|" << std::endl;
    }
}

void ConsoleRenderer::drawFooter(Empire* empire) {
    std::cout << "|";
    for (int i = 0; i < width - 2; ++i) std::cout << "-";
    std::cout << "|" << std::endl;
    
    std::cout << "| Crystal:" << empire->getResourceAmount("Crystal")
              << " Gem:" << empire->getResourceAmount("Gem")
              << " Ore:" << empire->getResourceAmount("Ore")
              << " Fuel:" << empire->getResourceAmount("Fuel")
              << std::string(width - 50, ' ') << "|" << std::endl;
    
    std::cout << "| Легенда: @ - текущая планета, O - своя, o - чужая, * - астероид, . - маршрут" 
              << std::string(width - 75, ' ') << "|" << std::endl;
}

void ConsoleRenderer::render(Galaxy* galaxy, Empire* empire,
                             int currentTurn, int maxTurns, double targetMoney) {
    drawBorder();
    drawHeader(empire, currentTurn, maxTurns, targetMoney);
    drawMap(galaxy, empire);
    drawFooter(empire);
    drawBorder();
}

void ConsoleRenderer::clear() {
    // Очистка экрана (ANSI escape)
    std::cout << "\033[2J\033[H";
}