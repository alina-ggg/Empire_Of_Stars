#include "Game.h"

#include <iostream>
#include <string>

// запрашивает целое число и повторяет вопрос, пока пользователь не введёт значение из разрешённого диапазона
int readNumber(const std::string& prompt, int minimum, int maximum) {
    while (true) {
        std::cout << prompt;

        std::string line;
        if (!std::getline(std::cin, line)) {
            // если ввод закончился, возвращаем минимальное допустимое значение
            return minimum;
        }

        try {
            std::size_t position = 0;
            int value = std::stoi(line, &position);

            // проверяем, что после числа не осталось лишних символов
            bool containsOnlyNumber = (position == line.size());
            bool isInRange = (value >= minimum && value <= maximum);

            if (containsOnlyNumber && isInRange) {
                return value;
            }
        } catch (const std::exception&) {
            // выбрасывает исключение, если строка не является числом
        }

        std::cout << "Введите целое число от " << minimum
                  << " до " << maximum << "\n";
    }
}

// создаёт игру и запускает её
int main() {
    std::cout << "==============================================\n";
    std::cout << "       ГАЛАКТИЧЕСКАЯ ЭКОНОМИКА\n";
    std::cout << "              ИМПЕРИЯ ЗВЁЗД\n";
    std::cout << "==============================================\n";

    // сначала пользователь задаёт размер генерируемой галактики
    int planets = readNumber("Количество планет (2-10): ", 2, 10);
    int asteroids = readNumber("Количество астероидов (1-20): ", 1, 20);

    // seed позволяет повторять одну и ту же генерацию при тестировании
    // значение 0 означает, что генератор выберет случайное начальное число
    int seed = readNumber("Seed генератора (0 — случайный): ", 0, 1000000000);

    // создаём игру с настройками и запускаем игровой цикл
    Game game(
        planets,
        asteroids,
        GameSettings::MAX_TURNS,
        GameSettings::TARGET_MONEY,
        static_cast<unsigned>(seed)
    );

    game.run();

    return 0;
}
