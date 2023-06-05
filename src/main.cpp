#include "../include/allheaders.h"
#include "../include/App.h"

/*
 * Что нужно прописать:
 * 1) Обработка аргумента из cmd::Сделано
 * 2) Открытие и парсинг файла в какую-то структуру::Сделано
 * 3) Эффективный подсчёт значений ячеек::В процессе
 * 4) Вывод::Сделано
 * 5) Написание тестов
 * */

static std::string giveColumn(std::string &expression, size_t startIndex) {
    for (size_t i = startIndex; i < expression.size(); i++) {
        if (expression[i] < 'A') {
            return expression.substr(startIndex, i - startIndex);
        }
    }
    return "";
}

static std::string giveRow(std::string &expression, size_t startIndex) {
    for (size_t i = startIndex; i < expression.size(); i++) {
        if (expression[i] < '0') {
            return expression.substr(startIndex, i - startIndex);
        }
    }
    return "";
}

int main(int argc, char *argv[]) {
    /*
    if (argc < 2) {
        std::cerr << "You didn't input filename in program args." << std::endl;
        std::cout << "Program shut down..." << std::endl;
        return EXIT_FAILURE;
    }
    TestApp::App app(argv[1]);
    return app.start();
    */
    std::string expr("=A1+B1");
    size_t offset = 1;
    std::string firstColumn = giveColumn(expr, offset);
    offset += firstColumn.size();
    std::string firstRow = giveRow(expr, offset);
    offset += firstRow.size();
    std::string op;
    op = expr[offset];
    offset++;
    std::string secondColumn = giveColumn(expr, offset);
    offset += secondColumn.size();
    std::string secondRow = expr.substr(offset);
    std::cout << firstColumn << std::endl;
    std::cout << firstRow << std::endl;
    std::cout << op << std::endl;
    std::cout << secondColumn << std::endl;
    std::cout << secondRow << std::endl;
    return 0;
}
