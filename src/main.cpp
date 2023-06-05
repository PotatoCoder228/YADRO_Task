#include "../include/allheaders.h"
#include "../include/App.h"

/*
 * Что нужно прописать:
 * 1) Обработка аргумента из cmd :: Сделано
 * 2) Открытие и парсинг файла в какую-то структуру::в процессе
 * 3) Эффективный подсчёт значений ячеек
 * 4) Красивое форматирование и вывод
 * 5) Написание тестов
 * */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "You didn't input filename in program args." << std::endl;
        std::cout << "Program shut down..." << std::endl;
        return EXIT_FAILURE;
    }
    TestApp::App app(argv[1]);
    return app.start();
}
