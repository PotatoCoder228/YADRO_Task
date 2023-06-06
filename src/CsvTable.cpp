//
// Created by sasha on 03.06.2023.
//

#include "CsvTable.h"

namespace TestApp {

    static std::string formatDoubleToInt(const std::string& str) {
        return str.substr(0, str.find('.'));
    }

    bool CsvTable::parseCsvTable(std::fstream &file) {

        std::string curStr;
        size_t maxRowSize = 0;
        size_t rowsCounter = 0;
        for (size_t i = 0; !file.eof(); i++) {
            getline(file, curStr);
            if (i == 0) {
                hack = curStr;
                size_t prev = 1;
                size_t founded_i;
                std::string buf;
                for (size_t j = 0; true; j++) {
                    founded_i = curStr.find(',', prev);
                    if (founded_i == std::string::npos) {
                        buf = curStr.substr(prev);
                        columns[buf] = j;
                        maxRowSize++;
                        break;
                    }
                    buf = curStr.substr(prev, founded_i - prev);
                    columns[buf] = j;
                    maxRowSize++;
                    prev = founded_i + 1;
                }
            } else {
                size_t prev = 0;
                size_t founded_i;
                std::string buf;
                for (size_t j = 0; true; j++) {
                    if (j > maxRowSize) {
                        std::cout << "Размер одной из строк больше количества столбцов" << std::endl;
                        return false;
                    }
                    founded_i = curStr.find(',', prev);
                    if (founded_i == std::string::npos) {
                        buf = curStr.substr(prev, founded_i - prev);
                        if (buf[0] == '=') {
                            table[i - 1].push_back(buf);
                            //std::cout<<i<<" "<<j<<std::endl;
                            struct tableIndex index = {.column = table[i - 1].size() - 1, .row = i - 1};
                            calcCells.push_back(index);
                        } else {
                            table[i - 1].push_back(buf);
                        }
                        break;
                    }
                    buf = curStr.substr(prev, founded_i - prev);
                    if (j == 0) {
                        int64_t rowNum = std::stoll(buf);
                        rows[rowNum] = rowsCounter;
                        std::vector<std::string> new_vector;
                        table.push_back(new_vector);
                        rowsCounter++;
                        rowsNames.push_back(rowNum);
                    } else {
                        if (buf[0] == '=') {
                            table[i - 1].push_back(buf);
                            //std::cout<<i<<" "<<j<<std::endl;
                            struct tableIndex index = {.column = table[i - 1].size() - 1, .row = i - 1};
                            calcCells.push_back(index);
                        } else {
                            table[i - 1].push_back(buf);
                        }
                    }
                    prev = founded_i + 1;
                }
            }
        }
        return true;
    }

    void CsvTable::printAsCsv() {
        std::cout << hack << std::endl;
        for (size_t i = 0; i < table.size(); i++) {
            std::cout << rowsNames[i];
            for (const auto &j: table[i]) {
                std::cout << ",";
                std::cout << j;
            }
            std::cout << std::endl;
        }
    }

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

    static double cellOperation(double arg1, double arg2, std::string &op) {
        switch (op[0]) {
            case '+':
                return arg1 + arg2;
            case '-':
                return arg1 - arg2;
            case '/':
                return arg1 / arg2;
            case '*':
                return arg1 * arg2;
        }
        return 0;
    }

    double CsvTable::calculate(std::string &expr) {
        if (expr[0] != '=') {
            return std::stod(expr);
        }
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

        if (!firstRow.empty() && !op.empty() && !secondRow.empty()) {
            size_t firstColIndex = columns[firstColumn];
            size_t firstRowIndex = rows[std::stoll(firstRow)];
            size_t secondColIndex = columns[secondColumn];
            size_t secondRowIndex = rows[std::stoll(secondRow)];
            double arg1 = calculate(table[firstRowIndex][firstColIndex]);
            double arg2 = calculate(table[secondRowIndex][secondColIndex]);
            return cellOperation(arg1, arg2, op);
        } else {
            std::cout << "Incorrect formula in the cell: " << expr << std::endl;
            return 0;
        }
    }

    void CsvTable::calcAllCells() {
        while (!calcCells.empty()) {
            struct tableIndex cellCoordinates = calcCells.back();
            std::string expr = table[cellCoordinates.row][cellCoordinates.column];
            if (expr[0] == '=') {
                double value = calculate(expr);
                table[cellCoordinates.row][cellCoordinates.column] = formatDoubleToInt(std::to_string(value));
            }
            calcCells.pop_back();
        }
    }
} // TestApp