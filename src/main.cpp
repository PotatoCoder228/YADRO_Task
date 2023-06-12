#include "../include/all_headers.h"
#include "../include/app.h"

#ifdef _WIN32

#include <io.h>
#include <fcntl.h>

#endif

/*
 * Что нужно прописать:
 * 1) Обработка аргумента из cmd::Сделано
 * 2) Открытие и парсинг файла в какую-то структуру::Сделано
 * 3) Эффективный подсчёт значений ячеек::Сделано
 * 4) Вывод::Сделано
 * 5) Рефакторинг::Сделано
 * 6) Написание тестов::Сделано
 * */

int main(int argc, char *argv[]) {
    char *checker = std::setlocale(LC_ALL, ".UTF-8");
    if (checker == nullptr) {
        checker = std::setlocale(LC_ALL, "C.UTF-8");
    }
    using std::cout;
    using std::endl;

#ifdef _WIN32
    _setmode(_fileno(stdout), _O_U16TEXT);
#endif

    if (argc < 2) {
        cout << "You didn't input filename in program args." << endl;
        cout << "Program shut down..." << endl;
        return EXIT_FAILURE;
    }
    test_app::app my_app;
    return my_app.start(argv[1]);
}
