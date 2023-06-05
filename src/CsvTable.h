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
    private:
        //сама таблица
        std::vector<std::vector<std::string>> table;
        //мапы для быстрого поиска индексов по имени/номеру столбца
        std::map<std::string, size_t> columns;
        std::map<size_t, size_t> rows;
        //ссылки на невычисленные ячейки, после вычисления просто разыменовываем указатель
        //и пишем по ссылке
        std::vector<size_t> rowsNames;
        std::vector<std::shared_ptr<std::string>> calcCells;
        std::string hack;
    };

} // TestApp

#endif //YADRO_TASK_CSVTABLE_H
