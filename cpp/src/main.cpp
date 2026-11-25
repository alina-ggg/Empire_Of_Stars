#include <iostream>
#include <limits>
#include "Game.h"
#include "ConsoleRenderer.h"

int main() {
    std::cout << "╔══════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║         ИМПЕРИЯ ЗВЁЗД — Настройка игры         ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════╝" << std::endl;

    std::cout << "Количество планет (рекомендуется 5-7): ";
    int numPlanets;
    std::cin >> numPlanets;

    std::cout << "Количество астероидов (рекомендуется 8-12): ";
    int numAsteroids;
    std::cin >> numAsteroids;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Game game(numPlanets, numAsteroids, 20, 10000.0);
    ConsoleRenderer renderer(80, 20);

    std::cout << "\n🚀 Игра запущена!\n" << std::endl;

    // Показываем начальную карту
    std::cout << "\n=== КАРТА ГАЛАКТИКИ (ход 1) ===" << std::endl;
    renderer.render(game.getGalaxy(), game.getEmpire(),
                    game.getCurrentTurn(), game.getMaxTurns(), 
                    game.getTargetMoney());

    // Главный игровой цикл
    while (game.isGameRunning()) {
        // Игрок делает одно действие
        bool turnEnded = game.playTurn();
        
        // Если ход был завершён (выбор 0) — показываем обновлённую карту
        if (turnEnded && game.isGameRunning()) {
            std::cout << "\n=== КАРТА ГАЛАКТИКИ (ход " << game.getCurrentTurn() << ") ===" << std::endl;
            renderer.render(game.getGalaxy(), game.getEmpire(),
                            game.getCurrentTurn(), game.getMaxTurns(), 
                            game.getTargetMoney());
        }
    }

    std::cout << "\n🏁 Игра завершена. Спасибо за игру!" << std::endl;
    return 0;
}