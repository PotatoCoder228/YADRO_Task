#include "../include/all_headers.h"
#include "../include/app.h"

/*
 * Что нужно прописать:
 * 1) Обработка аргумента из cmd::Сделано
 * 2) Открытие и парсинг файла в какую-то структуру::Сделано
 * 3) Эффективный подсчёт значений ячеек::Сделано
 * 4) Вывод::Сделано
 * 5) Рефакторинг::В процессе
 * 6) Написание тестов::В процессе
 * */

int main(int argc, char *argv[]) {
    using std::cout;
    using std::endl;

    if (argc < 2) {
        cout << "You didn't input filename in program args." << endl;
        cout << "Program shut down..." << endl;
        return EXIT_FAILURE;
    }
    test_app::app app(argv[1]);
    return app.start();
}
