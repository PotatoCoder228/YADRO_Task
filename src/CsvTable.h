//
// Created by sasha on 03.06.2023.
//

#ifndef YADRO_TASK_CSVTABLE_H
#define YADRO_TASK_CSVTABLE_H

#include <cstdint>
#include "../include/allheaders.h"

namespace TestApp {

    class CsvTable {
    public:
        bool parseCsvTable(std::fstream &file);

        void printAsCsv();

        void calcAllCells();

        double calculate(std::string &expr);

    private:
        struct tableIndex {
        public:
            size_t column;
            size_t row;
        };
        std::vector<std::vector<std::string>> table;
        std::map<std::string, size_t> columns;
        std::map<size_t, size_t> rows;
        std::vector<size_t> rowsNames;
        std::vector<tableIndex> calcCells;
        std::string hack;
    };

} // TestApp

#endif //YADRO_TASK_CSVTABLE_H
